/**
 * @brief Tokens of the Lox language.
 */
#ifndef TOKEN_LOX_H_
#define TOKEN_LOX_H_

#include <cstdint>
#include <cstddef>

#include <string>
#include <utility>
#include <memory>
#include <vector>

namespace Lox {


struct Literal {
public:
    virtual std::string get()
    {
        return std::move(_literal);
    }

protected:
    std::string _literal;
};

struct StringLiteral : public Literal {
public:
    StringLiteral(std::string literal)
    {
        _literal = std::move(literal);
    }

    ~StringLiteral() {}
};

struct NumberLiteral : public Literal {
public:
    NumberLiteral(std::string literal)
    {
        _literal = std::move(literal);
    }

    ~NumberLiteral() {}

    double asNumber() const
    {
        return stod(_literal);
    }
};

struct Identifier : public Literal
{
public:
    Identifier(std::string literal)
    {
        _literal = std::move(literal);
    }

    ~Identifier() {}
};

enum class TokenType : std::uint16_t {
    // Single character tokens
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,

    // One or two character tokens
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,

    // Literals
    IDENTIFIER,
    STRING,
    NUMBER,

    // Keywords
    AND,
    CLASS,
    ELSE,
    FALSE,
    FUN,
    FOR,
    IF,
    NIL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    TRUE,
    VAR,
    WHILE,

    EndOfFile,
};

std::string to_string(TokenType);


struct Token {
public:
    Token(TokenType type, std::string lexeme, Literal literal, size_t line)
        : _type { type }, _lexeme { std::move(lexeme) }, _literal { literal }, _line { line }
    {
    }
    ~Token() {}

    std::string toString()
    {
        return to_string(_type) + " " + _lexeme + " " + _literal.get() + " "  + std::to_string(_line);
    }

    std::string lexeme() const
    {
        return _lexeme;
    }

private:
    TokenType _type;
    std::string _lexeme;
    Literal _literal;
    size_t _line;
};


}

#endif
