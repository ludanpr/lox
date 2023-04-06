; Generate AST
;

(define ast '(("Expr" ("Assign"   (("Token" "name")
                                   ("Expr" "value")))
                      ("Binary"   (("Expr" "left")
                                   ("Token" "operator")
                                   ("Expr" "right")))
                      ("Call"     (("Expr" "callee")
                                   ("Token" "paren")
                                   ("std::vector<Expr>" "args")))
                      ("Get"      (("Expr" "object")
                                   ("Token" "name")))
                      ("Grouping" (("Expr" "expression")))
                      ("Literal"  (("Literal" "value")))
                      ("Logical"  (("Expr" "left")
                                   ("Token" "operator")
                                   ("Expr" "right")))
                      ("Set"      (("Expr" "object")
                                   ("Token" "name")
                                   ("Expr" "value")))
                      ("Super"    (("Token" "keyword")
                                   ("Token" "method")))
                      ("This"     (("Token" "keyword")))
                      ("Unary"    (("Token" "operator")
                                   ("Expr" "right")))
                      ("Variable" (("Token" "name"))))

              ("Stmt" ("Block"      (("std::vector<Stmt>" "statements")))
                      ("Class"      (("Token" "name")
                                     ("Expr::Variable" "superclass")
                                     ("std::vector<Function>" "methods")))
                      ("Expression" (("Expr" "expression")))
                      ("Function"   (("Token" "name")
                                     ("std::vector<Token>" "params")
                                     ("std::vector<Stmt>" "body")))
                      ("If"         (("Expr" "condition")
                                     ("Stmt" "thenbranch")
                                     ("Stmt" "elsebranch")))
                      ("Print"      (("Expr" "expression")))
                      ("Return"     (("Token" "keyword")
                                     ("Expr" "value")))
                      ("Var"        (("Token" "name")
                                     ("Expr" "initializer")))
                      ("While"      (("Expr" "condition")
                                     ("Stmt" "body"))))))

(define nl "\n")

(define (get-branches root ast)
  (cdr (assoc root ast)))

(define (generate-all-visitors root)
  (let ((str (make-string 0)))
    (for-each (lambda (visitor)
                (set! str (string-append str
                                         "        T visit" visitor root "(" visitor root ") = 0;" nl)))
              (map car (get-branches root ast)))
    str))

(define (generate-root root)
  (apply string-append
         (list
          "class " root " {" nl
          "    template<typename T>" nl
          "    class Visitor<T> {"   nl
          (generate-all-visitors root)
          "    }"                    nl
          "    template<typename T>" nl
          "    virtual T accept(Visitor<T>) = 0;" nl
          "};"                                   nl)))


(define (%type-var-list-str lst sep identation with-underscore with-newline reference)
  (let ((str (make-string 0)))
    (for-each (lambda (x)
                (set! str (apply string-append
                                 str
                                 (list identation (car x) reference
                                       with-underscore (cadr x) sep with-newline))))
              lst)
    str))

(define (parameter-list-str lst)
  (%type-var-list-str lst ", " "" " " "" "&"))

(define (member-declaration-str lst)
  (%type-var-list-str lst ";" "    "  " _" nl ""))

(define (member-assignment-str lst)
  (let ((str (make-string 0)))
    (for-each (lambda (x)
                (let ((name (cadr x)))
                  (set! str (apply string-append
                             str
                             (list "        _" name " = " name ";" nl)))))
              lst)
    str))

;;; Takes a branch like:
;;;  `("Assign" (("Token" "name") ("Expr" "value")))'
;;; and generates its correspondent C++ derived class.
;;;
(define (generate-branch-class root branch)
  (let ((node (car branch))
        (vars (cadr branch)))
    (apply string-append
           (list
            "class " node root " : public " root " {" nl
            "public:" nl
            "    " node root "(" (parameter-list-str vars) ")" nl
            "    {" nl
            (member-assignment-str vars)
            "    }" nl
            "    template<typename T>" nl
            "    T accept(Visitor<T> visitor) override" nl
            "    {" nl
            "        return visitor.visit" node root "(this);" nl
            "    }" nl
            "private:" nl
            (member-declaration-str vars)
            "};"                                   nl))))

(define (generate-source-file root namespace filename)
  (call-with-output-file filename
    (lambda (output-port)
      (let ((intro (string-append
                    "// File generated by script/ast.scm" nl nl
                    "#include <scanner/Token.h>"          nl nl
                    "namespace " namespace " {"           nl nl))
            (outro (string-append "}" nl)))
        (display intro output-port)
        (display (generate-root root) output-port)
        (display nl output-port)
        (let ((branches (get-branches root ast)))
          (for-each (lambda (branch)
                      (display (generate-branch-class root branch) output-port)
                      (display nl output-port))
                    branches))
        (display outro output-port)))))
