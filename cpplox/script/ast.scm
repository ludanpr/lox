; Generate AST
;

(define ast '(("Expr" ("Assign"   (("std::shared_ptr<Token>" "name")
                                   ("std::shared_ptr<Expr>" "value")))
                      ("Binary"   (("std::shared_ptr<Expr>" "left")
                                   ("std::shared_ptr<Token>" "op")
                                   ("std::shared_ptr<Expr>" "right")))
                      ("Call"     (("std::shared_ptr<Expr>" "callee")
                                   ("std::shared_ptr<Token>" "paren")
                                   ("std::vector<std::shared_ptr<Expr>>" "args")))
                      ("Get"      (("std::shared_ptr<Expr>" "object")
                                   ("std::shared_ptr<Token>" "name")))
                      ("Grouping" (("std::shared_ptr<Expr>" "expression")))
                      ("Literal"  (("std::shared_ptr<Literal>" "value")))
                      ("Logical"  (("std::shared_ptr<Expr>" "left")
                                   ("std::shared_ptr<Token>" "op")
                                   ("std::shared_ptr<Expr>" "right")))
                      ("Set"      (("std::shared_ptr<Expr>" "object")
                                   ("std::shared_ptr<Token>" "name")
                                   ("std::shared_ptr<Expr>" "value")))
                      ("Super"    (("std::shared_ptr<Token>" "keyword")
                                   ("std::shared_ptr<Token>" "method")))
                      ("This"     (("std::shared_ptr<Token>" "keyword")))
                      ("Unary"    (("std::shared_ptr<Token>" "op")
                                   ("std::shared_ptr<Expr>" "right")))
                      ("Variable" (("std::shared_ptr<Token>" "name"))))

              ("Stmt" ("Block"      (("std::vector<std::shared_ptr<Stmt>>" "statements")))
                      ("Class"      (("std::shared_ptr<Token>" "name")
                                     ("std::shared_ptr<VariableExpr>" "superclass")
                                     ("std::vector<std::shared_ptr<FunctionStmt>>" "methods")))
                      ("Expression" (("std::shared_ptr<Expr>" "expression")))
                      ("Function"   (("std::shared_ptr<Token>" "name")
                                     ("std::vector<std::shared_ptr<Token>>" "params")
                                     ("std::vector<std::shared_ptr<Stmt>>" "body")))
                      ("If"         (("std::shared_ptr<Expr>" "condition")
                                     ("std::shared_ptr<Stmt>" "thenbranch")
                                     ("std::shared_ptr<Stmt>" "elsebranch")))
                      ("Print"      (("std::shared_ptr<Expr>" "expression")))
                      ("Return"     (("std::shared_ptr<Token>" "keyword")
                                     ("std::shared_ptr<Expr>" "value")))
                      ("Var"        (("std::shared_ptr<Token>" "name")
                                     ("std::shared_ptr<Expr>" "initializer")))
                      ("While"      (("std::shared_ptr<Expr>" "condition")
                                     ("std::shared_ptr<Stmt>" "body"))))))

(define nl "\n")

(define (get-branches root ast)
  (cdr (assoc root ast)))

(define (generate-all-visitors root)
  (let ((str (make-string 0)))
    (for-each (lambda (visitor)
                (set! str (string-append str
                                         "        virtual void visit" visitor root "(" visitor root "&) = 0;" nl)))
              (map car (get-branches root ast)))
    str))

(define (generate-root root)
  (apply string-append
         (list
          "class " root " {" nl
          "public:"          nl
          "    class Visitor {"   nl
          "    public:"           nl
          (generate-all-visitors root)
          "    };"                    nl
          "    virtual void accept(Visitor &) = 0;" nl
          "};"                                   nl)))


(define (remove-first-char-if-char=? str c)
  (let ((str-as-list (string->list str)))
    (if (char=? (car str-as-list) c)
        (substring str 1)
        str)))

(define (%type-var-list-str lst sep sep-at-end? identation with-underscore with-newline reference?)
  (let* ((var-ref-or-not (if reference?
                             (lambda (name) name)
                             (lambda (name)
                               (remove-first-char-if-char=? name #\&))))
         (%sep (if sep-at-end?
                   sep
                   ""))
        (str (make-string 0)))
    (for-each (lambda (x)
                (set! str (apply string-append
                                 str
                                 (if sep-at-end?
                                     (list identation (car x) " "
                                           (var-ref-or-not (cadr x)) with-underscore sep with-newline)
                                     (list identation %sep (car x) " "
                                            (var-ref-or-not (cadr x)) with-underscore with-newline))))
                (set! %sep sep))
              lst)
    str))

(define (parameter-list-str lst)
  (%type-var-list-str lst ", " #f "" "" "" #t))

(define (member-declaration-str lst)
  (%type-var-list-str lst ";" #t "    "  "_" nl #f))

(define (%member-list-str lst fmtfn)
  (let ((str (make-string 0)))
    (for-each (lambda (x)
                (let ((type (car x))
                      (name (remove-first-char-if-char=? (cadr x) #\&)))
                  (set! str (apply string-append
                                   str
                                   (fmtfn type name)))))
              lst)
    str))

(define (member-functions-get-str lst)
  (%member-list-str lst (lambda (type name)
                          (list "    " type " " name "() const" nl
                                "    {"                          nl
                                "        return " name "_;"      nl
                                "    }" nl))))

(define (member-assignment-str lst)
  (%member-list-str lst (lambda (type name)
                          (list "        " name "_ = " name ";" nl))))

(define (forward-class-declarations root)
  (let ((nodes (map car (get-branches root ast)))
        (str (make-string 0)))
    (for-each (lambda (node)
                (set! str (apply string-append
                                 str
                                 (list "class " node root ";" nl))))
              nodes)
    str))

;;; Takes a branch like:
;;;  `("Assign" (("std::shared_ptr<Token>" "name") ("std::shared_ptr<Expr>" "value")))'
;;; and generates its correspondent C++ derived class.
;;;
(define (generate-branch-class root branch)
  (let ((node (car branch))
        (vars (cadr branch)))
    (apply string-append
           (list
            "class " node root " : public " root " {" nl
            "public:" nl
            "    " node root "() = default;" nl nl
            "    ~" node root "() {}"        nl nl
            "    " node root "(" (parameter-list-str vars) ")" nl
            "    {" nl
            (member-assignment-str vars)
            "    }" nl
            "    void accept(Visitor &visitor) override" nl
            "    {" nl
            "        visitor.visit" node root "(*this);" nl
            "    }" nl nl
            (member-functions-get-str vars)
            "private:" nl
            (member-declaration-str vars)
            "};"                                   nl))))

(define (generate-source-file root namespace filename)
  (if (not (assoc root ast))
      (error (string-append "node " root " not in AST")))
  (call-with-output-file filename
    (lambda (output-port)
      (let ((intro (string-append
                    "// File generated by script/ast.scm" nl nl
                    "#ifndef LOX_" root "_H_"             nl
                    "#define LOX_" root "_H_"             nl nl
                    "#include <scanner/Token.h>"          nl nl
                    "namespace " namespace " {"           nl nl
                    (forward-class-declarations root)     nl nl))
            (outro (string-append "}" nl nl
                                  "#endif" nl)))
        (display intro output-port)
        (display (generate-root root) output-port)
        (display nl output-port)
        (let ((branches (get-branches root ast)))
          (for-each (lambda (branch)
                      (display (generate-branch-class root branch) output-port)
                      (display nl output-port))
                    branches))
        (display outro output-port)))))
