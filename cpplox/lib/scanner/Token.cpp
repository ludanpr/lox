#include <scanner/Token.h>

namespace Lox {

std::string to_string(TokenType tk)
{
    switch (tk) {
    // Single character tokens
    case TokenType::LEFT_PAREN:
        return "LEFT PAREN";

    case TokenType::RIGHT_PAREN:
        return "RIGHT PAREN";

    case TokenType::LEFT_BRACE:
        return "LEFT BRACE";

    case TokenType::RIGHT_BRACE:
        return "RIGHT BRACE";

    case TokenType::COMMA:
        return "COMMA";

    case TokenType::DOT:
        return "DOT";

    case TokenType::MINUS:
        return "MINUS";

    case TokenType::PLUS:
        return "PLUS";

    case TokenType::SEMICOLON:
        return "SEMICOLON";

    case TokenType::SLASH:
        return "SLASH";

    case TokenType::STAR:
        return "STAR";

    // One or two character tokens
    case TokenType::BANG:
        return "BANG";

    case TokenType::BANG_EQUAL:
        return "BANG EQUAL";

    case TokenType::EQUAL:
        return "EQUAL";

    case TokenType::EQUAL_EQUAL:
        return "EQUAL EQUAL";

    case TokenType::GREATER:
        return "GREATER";

    case TokenType::GREATER_EQUAL:
        return "GREATER EQUAL";

    case TokenType::LESS:
        return "LESS";

    case TokenType::LESS_EQUAL:
        return "LESS EQUAL";

    // Literals
    case TokenType::IDENTIFIER:
        return "IDENTIFIER";

    case TokenType::STRING:
        return "STRING";

    case TokenType::NUMBER:
        return "NUMBER";

    // Keywords
    case TokenType::AND:
        return "AND";

    case TokenType::CLASS:
        return "CLASS";

    case TokenType::ELSE:
        return "ELSE";

    case TokenType::FALSE:
        return "FALSE";

    case TokenType::FUN:
        return "FUN";

    case TokenType::FOR:
        return "FOR";

    case TokenType::IF:
        return "IF";

    case TokenType::NIL:
        return "NIL";

    case TokenType::OR:
        return "OR";

    case TokenType::PRINT:
        return "PRINT";

    case TokenType::RETURN:
        return "RETURN";

    case TokenType::SUPER:
        return "SUPER";

    case TokenType::THIS:
        return "THIS";

    case TokenType::TRUE:
        return "TRUE";

    case TokenType::VAR:
        return "VAR";

    case TokenType::WHILE:
        return "WHILE";

    case TokenType::EndOfFile:
        return "End Of File";
    }
}

}
