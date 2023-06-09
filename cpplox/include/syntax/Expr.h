// File generated by script/ast.scm

#ifndef LOX_Expr_H_
#define LOX_Expr_H_

#include <scanner/Token.h>

namespace Lox {

class AssignExpr;
class BinaryExpr;
class CallExpr;
class GetExpr;
class GroupingExpr;
class LiteralExpr;
class LogicalExpr;
class SetExpr;
class SuperExpr;
class ThisExpr;
class UnaryExpr;
class VariableExpr;


class Expr {
public:
    class Visitor {
    public:
        virtual void visitAssignExpr(AssignExpr&) = 0;
        virtual void visitBinaryExpr(BinaryExpr&) = 0;
        virtual void visitCallExpr(CallExpr&) = 0;
        virtual void visitGetExpr(GetExpr&) = 0;
        virtual void visitGroupingExpr(GroupingExpr&) = 0;
        virtual void visitLiteralExpr(LiteralExpr&) = 0;
        virtual void visitLogicalExpr(LogicalExpr&) = 0;
        virtual void visitSetExpr(SetExpr&) = 0;
        virtual void visitSuperExpr(SuperExpr&) = 0;
        virtual void visitThisExpr(ThisExpr&) = 0;
        virtual void visitUnaryExpr(UnaryExpr&) = 0;
        virtual void visitVariableExpr(VariableExpr&) = 0;
    };
    virtual void accept(Visitor &) = 0;
};

class AssignExpr : public Expr {
public:
    AssignExpr() = default;

    ~AssignExpr() {}

    AssignExpr(std::shared_ptr<Token> name, std::shared_ptr<Expr> value)
    {
        name_ = name;
        value_ = value;
    }
    void accept(Visitor &visitor) override
    {
        visitor.visitAssignExpr(*this);
    }

    std::shared_ptr<Token> name() const
    {
        return name_;
    }
    std::shared_ptr<Expr> value() const
    {
        return value_;
    }
private:
    std::shared_ptr<Token> name_;
    std::shared_ptr<Expr> value_;
};

class BinaryExpr : public Expr {
public:
    BinaryExpr() = default;

    ~BinaryExpr() {}

    BinaryExpr(std::shared_ptr<Expr> left, std::shared_ptr<Token> op, std::shared_ptr<Expr> right)
    {
        left_ = left;
        op_ = op;
        right_ = right;
    }
    void accept(Visitor &visitor) override
    {
        visitor.visitBinaryExpr(*this);
    }

    std::shared_ptr<Expr> left() const
    {
        return left_;
    }
    std::shared_ptr<Token> op() const
    {
        return op_;
    }
    std::shared_ptr<Expr> right() const
    {
        return right_;
    }
private:
    std::shared_ptr<Expr> left_;
    std::shared_ptr<Token> op_;
    std::shared_ptr<Expr> right_;
};

class CallExpr : public Expr {
public:
    CallExpr() = default;

    ~CallExpr() {}

    CallExpr(std::shared_ptr<Expr> callee, std::shared_ptr<Token> paren, std::vector<std::shared_ptr<Expr>> args)
    {
        callee_ = callee;
        paren_ = paren;
        args_ = args;
    }
    void accept(Visitor &visitor) override
    {
        visitor.visitCallExpr(*this);
    }

    std::shared_ptr<Expr> callee() const
    {
        return callee_;
    }
    std::shared_ptr<Token> paren() const
    {
        return paren_;
    }
    std::vector<std::shared_ptr<Expr>> args() const
    {
        return args_;
    }
private:
    std::shared_ptr<Expr> callee_;
    std::shared_ptr<Token> paren_;
    std::vector<std::shared_ptr<Expr>> args_;
};

class GetExpr : public Expr {
public:
    GetExpr() = default;

    ~GetExpr() {}

    GetExpr(std::shared_ptr<Expr> object, std::shared_ptr<Token> name)
    {
        object_ = object;
        name_ = name;
    }
    void accept(Visitor &visitor) override
    {
        visitor.visitGetExpr(*this);
    }

    std::shared_ptr<Expr> object() const
    {
        return object_;
    }
    std::shared_ptr<Token> name() const
    {
        return name_;
    }
private:
    std::shared_ptr<Expr> object_;
    std::shared_ptr<Token> name_;
};

class GroupingExpr : public Expr {
public:
    GroupingExpr() = default;

    ~GroupingExpr() {}

    GroupingExpr(std::shared_ptr<Expr> expression)
    {
        expression_ = expression;
    }
    void accept(Visitor &visitor) override
    {
        visitor.visitGroupingExpr(*this);
    }

    std::shared_ptr<Expr> expression() const
    {
        return expression_;
    }
private:
    std::shared_ptr<Expr> expression_;
};

class LiteralExpr : public Expr {
public:
    LiteralExpr() = default;

    ~LiteralExpr() {}

    LiteralExpr(std::shared_ptr<Literal> value)
    {
        value_ = value;
    }
    void accept(Visitor &visitor) override
    {
        visitor.visitLiteralExpr(*this);
    }

    std::shared_ptr<Literal> value() const
    {
        return value_;
    }
private:
    std::shared_ptr<Literal> value_;
};

class LogicalExpr : public Expr {
public:
    LogicalExpr() = default;

    ~LogicalExpr() {}

    LogicalExpr(std::shared_ptr<Expr> left, std::shared_ptr<Token> op, std::shared_ptr<Expr> right)
    {
        left_ = left;
        op_ = op;
        right_ = right;
    }
    void accept(Visitor &visitor) override
    {
        visitor.visitLogicalExpr(*this);
    }

    std::shared_ptr<Expr> left() const
    {
        return left_;
    }
    std::shared_ptr<Token> op() const
    {
        return op_;
    }
    std::shared_ptr<Expr> right() const
    {
        return right_;
    }
private:
    std::shared_ptr<Expr> left_;
    std::shared_ptr<Token> op_;
    std::shared_ptr<Expr> right_;
};

class SetExpr : public Expr {
public:
    SetExpr() = default;

    ~SetExpr() {}

    SetExpr(std::shared_ptr<Expr> object, std::shared_ptr<Token> name, std::shared_ptr<Expr> value)
    {
        object_ = object;
        name_ = name;
        value_ = value;
    }
    void accept(Visitor &visitor) override
    {
        visitor.visitSetExpr(*this);
    }

    std::shared_ptr<Expr> object() const
    {
        return object_;
    }
    std::shared_ptr<Token> name() const
    {
        return name_;
    }
    std::shared_ptr<Expr> value() const
    {
        return value_;
    }
private:
    std::shared_ptr<Expr> object_;
    std::shared_ptr<Token> name_;
    std::shared_ptr<Expr> value_;
};

class SuperExpr : public Expr {
public:
    SuperExpr() = default;

    ~SuperExpr() {}

    SuperExpr(std::shared_ptr<Token> keyword, std::shared_ptr<Token> method)
    {
        keyword_ = keyword;
        method_ = method;
    }
    void accept(Visitor &visitor) override
    {
        visitor.visitSuperExpr(*this);
    }

    std::shared_ptr<Token> keyword() const
    {
        return keyword_;
    }
    std::shared_ptr<Token> method() const
    {
        return method_;
    }
private:
    std::shared_ptr<Token> keyword_;
    std::shared_ptr<Token> method_;
};

class ThisExpr : public Expr {
public:
    ThisExpr() = default;

    ~ThisExpr() {}

    ThisExpr(std::shared_ptr<Token> keyword)
    {
        keyword_ = keyword;
    }
    void accept(Visitor &visitor) override
    {
        visitor.visitThisExpr(*this);
    }

    std::shared_ptr<Token> keyword() const
    {
        return keyword_;
    }
private:
    std::shared_ptr<Token> keyword_;
};

class UnaryExpr : public Expr {
public:
    UnaryExpr() = default;

    ~UnaryExpr() {}

    UnaryExpr(std::shared_ptr<Token> op, std::shared_ptr<Expr> right)
    {
        op_ = op;
        right_ = right;
    }
    void accept(Visitor &visitor) override
    {
        visitor.visitUnaryExpr(*this);
    }

    std::shared_ptr<Token> op() const
    {
        return op_;
    }
    std::shared_ptr<Expr> right() const
    {
        return right_;
    }
private:
    std::shared_ptr<Token> op_;
    std::shared_ptr<Expr> right_;
};

class VariableExpr : public Expr {
public:
    VariableExpr() = default;

    ~VariableExpr() {}

    VariableExpr(std::shared_ptr<Token> name)
    {
        name_ = name;
    }
    void accept(Visitor &visitor) override
    {
        visitor.visitVariableExpr(*this);
    }

    std::shared_ptr<Token> name() const
    {
        return name_;
    }
private:
    std::shared_ptr<Token> name_;
};

}

#endif
