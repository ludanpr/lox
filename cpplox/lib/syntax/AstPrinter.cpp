#include <syntax/AstPrinter.h>

namespace Lox {

void AstPrinter::visitBlockStmt(BlockStmt &stmt)
{
    os_ << "(block ";

    for (auto &stmt : stmt.statements()) {
        stmt->accept(*this);
    }

    os_ << ")";
}

void AstPrinter::visitClassStmt(ClassStmt &stmt)
{
    os_ << "(class " << stmt.name()->lexeme();

    if (stmt.superclass()) {
        os_ << " < ";
        print(stmt.superclass());
    }

    for (auto &method : stmt.methods()) {
        os_ << " ";
        print(method);
    }

    os_ << ")";
}

void AstPrinter::visitExpressionStmt(ExpressionStmt &stmt)
{
    parenthesize(";", { stmt.expression() });
}

void AstPrinter::visitFunctionStmt(FunctionStmt &stmt)
{
    os_ << "(fun" << stmt.name()->lexeme() << "(";

    for (auto &param : stmt.params()) {
        if (param != stmt.params().at(0)) {
            os_ << " ";
        }
        os_ << param->lexeme();
    }

    for (auto &body : stmt.body()) {
        body->accept(*this);
    }

    os_ << ")";
}

void AstPrinter::visitIfStmt(IfStmt &stmt)
{
    if (!stmt.elsebranch()) {
        parenthesize2("if", stmt.condition(), stmt.thenbranch());
    }
    else {
        parenthesize2("if-else", stmt.condition(), stmt.thenbranch());
    }
}

void AstPrinter::visitPrintStmt(PrintStmt &stmt)
{
    parenthesize("print", { stmt.expression() });
}

void AstPrinter::visitReturnStmt(ReturnStmt &stmt)
{
    if (!stmt.value())
        os_ << "(return)";
    else
        parenthesize("return", { stmt.value() });
}

void AstPrinter::visitVarStmt(VarStmt &stmt)
{
    if (!stmt.initializer())
        parenthesize2("var", stmt.name());
    else
        parenthesize2("var", stmt.name(), "=", stmt.initializer());
}

void AstPrinter::visitWhileStmt(WhileStmt &stmt)
{
    parenthesize2("while", stmt.condition(), stmt.body());
}


void AstPrinter::visitAssignExpr(AssignExpr &expr)
{
    parenthesize2("=", expr.name()->lexeme(), expr.value());
}

void AstPrinter::visitBinaryExpr(BinaryExpr &expr)
{
    parenthesize(expr.op()->lexeme(), { expr.left(), expr.right() });
}

void AstPrinter::visitCallExpr(CallExpr &expr)
{
    parenthesize2("call", expr.callee(), expr.args());
}

void AstPrinter::visitGetExpr(GetExpr &expr)
{
    parenthesize2(".", expr.object(), expr.name()->lexeme());
}

void AstPrinter::visitGroupingExpr(GroupingExpr &expr)
{
    parenthesize("group", { expr.expression() });
}

void AstPrinter::visitLiteralExpr(LiteralExpr &expr)
{
    if (!expr.value())
        os_ << "nil";
    else
        os_ << expr.value()->get();
}

void AstPrinter::visitLogicalExpr(LogicalExpr &expr)
{
    parenthesize(expr.op()->lexeme(), { expr.left(), expr.right() });
}

void AstPrinter::visitSetExpr(SetExpr &expr)
{
    parenthesize2("=", expr.object(), expr.name()->lexeme(), expr.value());
}

void AstPrinter::visitSuperExpr(SuperExpr &expr)
{
    parenthesize2("super", expr.method());
}

void AstPrinter::visitThisExpr(ThisExpr &expr)
{
    os_ << "this";
}

void AstPrinter::visitUnaryExpr(UnaryExpr &expr)
{
    parenthesize(expr.op()->lexeme(), { expr.right() });
}

void AstPrinter::visitVariableExpr(VariableExpr &expr)
{
    os_ << expr.name()->lexeme();
}


void AstPrinter::parenthesize(std::string name, std::initializer_list<std::shared_ptr<Expr>> exprs)
{
    os_ << "(" << name;
    for (auto &expr : exprs) {
        os_ << " ";
        expr->accept(*this);
    }
    os_ << ")";
}

template<typename... Args>
void AstPrinter::parenthesize2(std::string name, Args... args)
{
    os_ << "Unimplemented";
}

template<typename... Args>
void AstPrinter::transform(Args... args)
{
    os_ << "Unimplemented";
}

}
