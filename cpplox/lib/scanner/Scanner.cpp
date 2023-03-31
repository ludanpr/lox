#include <scanner/Scanner.h>
#include <scanner/Token.h>

#include <cctype>

#include <iostream>

namespace Lox {

void Scanner::scanToken()
{
    char c = advance();
    switch(c) {
    case '(':
        addToken(TokenType::LEFT_PAREN);
        break;
    case ')':
        addToken(TokenType::RIGHT_PAREN);
        break;
    case '{':
        addToken(TokenType::LEFT_BRACE);
        break;
    case '}':
        addToken(TokenType::RIGHT_BRACE);
        break;
    case ',':
        addToken(TokenType::COMMA);
        break;
    case '.':
        addToken(TokenType::DOT);
        break;
    case '-':
        addToken(TokenType::MINUS);
        break;
    case '+':
        addToken(TokenType::PLUS);
        break;
    case ';':
        addToken(TokenType::SEMICOLON);
        break;
    case '*':
        addToken(TokenType::STAR);
        break;
    case '!':
        addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        break;
    case '=':
        addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        break;
    case '<':
        addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        break;
    case '>':
        addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        break;
    case '/':
        if (match('/')) {
            while (peek() != '\n' && !isAtEnd())
                advance();;
        }
        else {
            addToken(TokenType::SLASH);
        }
        break;
    case ' ':
    case '\r':
    case '\t':
        break;
    case '\n':
        _line++;
        break;
    case '"':
        string();
        break;
    default:
        if (std::isdigit(c))
            number();
        else if (std::isalpha(c))
            identifier();
        else
            error(_line, "Unexpected character.");
        break;
    }
}

void Scanner::string()
{
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n')
            _line++;
        advance();
    }

    if (isAtEnd()) {
        error(_line, "Unterminated string");
        return;
    }

    advance();
    StringLiteral val { _source.substr(_start + 1, _current - 2 - _start) };
    addToken(TokenType::STRING, val);
}

void Scanner::number()
{
    while (std::isdigit(peek()))
        advance();

    if (peek() == '.' && std::isdigit(peekNext())) {
        advance();

        while (std::isdigit(peek()))
            advance();
    }

    NumberLiteral val { _source.substr(_start, _current - _start) };
    addToken(TokenType::NUMBER, val);
}

void Scanner::identifier()
{
    while (std::isalnum(peek()))
        advance();

    std::string text { _source.substr(_start, _current - _start) };
    auto type { _keywords.find(text) };
    if (type == _keywords.end()) {
        Identifier val { text };
        addToken(TokenType::IDENTIFIER, val);
    }
    else {
        addToken(type->second);
    }
}

/**
 * @brief Looking past the decimal point of a number requires a
 * second character of lookahead since we don't want to consume
 * the '.' until we're sure there is a digit after it.
 */
char Scanner::peekNext() const
{
    if (_current + 1 >= _source.length())
        return '\0';
    return _source.at(_current + 1);
}

bool Scanner::match(char expected)
{
    if (isAtEnd())
        return false;
    if (_source.at(_current) != expected)
        return false;

    _current++;
    return true;
}

/**
 * @brief One character lookahead.
 */
char Scanner::peek() const
{
    if (isAtEnd())
        return '\0';
    return _source.at(_current);
}

char Scanner::advance()
{
    _current++;
    return _source.at(_current - 1);
}

void Scanner::addToken(TokenType type)
{
    addToken(type, Literal {});
}

void Scanner::addToken(TokenType type, Literal literal)
{
    std::string text = _source.substr(_start, _current - _start);
    _tokens.push_back(std::make_shared<Token>(type, text, literal, _line));
}

}
