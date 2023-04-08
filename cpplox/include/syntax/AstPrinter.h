/**
 * @brief AstPrinter visitor.
 */
#ifndef LOX_AST_PRINTER_H_
#define LOX_AST_PRINTER_H_

#include <syntax/Expr.h>
#include <syntax/Stmt.h>

#include <ostream>
#include <memory>
#include <initializer_list>

namespace Lox {

class AstPrinter : public Expr::Visitor, public Stmt::Visitor {
public:
    AstPrinter(std::ostream &os) : os_ { os } {}
    ~AstPrinter() {}

    void print(std::shared_ptr<Expr> expr)
    {
        expr->accept(*this);
    }

    void print(std::shared_ptr<Stmt> stmt)
    {
        stmt->accept(*this);
    }

    void visitBlockStmt(BlockStmt &) override;
    void visitClassStmt(ClassStmt &) override;
    void visitExpressionStmt(ExpressionStmt &) override;
    void visitFunctionStmt(FunctionStmt &) override;
    void visitIfStmt(IfStmt &) override;
    void visitPrintStmt(PrintStmt &) override;
    void visitReturnStmt(ReturnStmt &) override;
    void visitVarStmt(VarStmt &) override;
    void visitWhileStmt(WhileStmt &) override;

    void visitAssignExpr(AssignExpr &) override;
    void visitBinaryExpr(BinaryExpr &) override;
    void visitCallExpr(CallExpr &) override;
    void visitGetExpr(GetExpr &) override;
    void visitGroupingExpr(GroupingExpr &) override;
    void visitLiteralExpr(LiteralExpr &) override;
    void visitLogicalExpr(LogicalExpr &) override;
    void visitSetExpr(SetExpr &) override;
    void visitSuperExpr(SuperExpr &) override;
    void visitThisExpr(ThisExpr &) override;
    void visitUnaryExpr(UnaryExpr &) override;
    void visitVariableExpr(VariableExpr &) override;

private:
    std::ostream &os_;


    void parenthesize(std::string name, std::initializer_list<std::shared_ptr<Expr>> exprs);

    // TODO
    template<typename... Args>
    void parenthesize2(std::string name, Args... args);

    template<typename... Args>
    void transform(Args... args);
};

}

#endif
