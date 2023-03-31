/**
 * @brief Lox scanner
 */
#ifndef LOX_SCANNER_H_
#define LOX_SCANNER_H_

#include <cstddef>

#include <vector>
#include <unordered_map>
#include <sstream>
#include <memory>

#include <scanner/Token.h>
#include <log/Log.h>

namespace Lox {

class Scanner {
public:
    Scanner(std::string source) : _source { std::move(source) }
    {
    }

    std::vector<std::shared_ptr<Token>> &scanTokens()
    {
        while (!isAtEnd()) {
            _start = _current;
            scanToken();
        }

        _tokens.push_back(std::make_shared<Token>(TokenType::EndOfFile, "", Literal {}, _line));
        return _tokens;
    }

    void setHadError(bool val)
    {
        _had_error = val;
    }

    bool getHadError() const
    {
        return _had_error;
    }

    void outputErrors(std::ostream &os, bool reset=false)
    {
        os << Lox::Log::instance().get();

        if (reset)
            Log::instance().clear();
    }

private:
    std::string _source;
    std::vector<std::shared_ptr<Token>> _tokens;
    size_t _start { 0 };
    size_t _current { 0 };
    size_t _line { 1 };

    std::unordered_map<std::string, TokenType> _keywords {
        { "and"   , TokenType::AND },
        { "class" , TokenType::CLASS },
        { "else"  , TokenType::ELSE },
        { "false" , TokenType::FALSE },
        { "for"   , TokenType::FOR },
        { "fun"   , TokenType::FUN },
        { "if"    , TokenType::IF },
        { "nil"   , TokenType::NIL },
        { "or"    , TokenType::OR },
        { "print" , TokenType::PRINT },
        { "return", TokenType::RETURN },
        { "super" , TokenType::SUPER },
        { "this"  , TokenType::THIS },
        { "true"  , TokenType::TRUE },
        { "var"   , TokenType::VAR },
        { "while" , TokenType::WHILE },
    };
    bool _had_error { false };

    void scanToken();
    char advance();
    char peek() const;
    void addToken(TokenType type);
    void addToken(TokenType type, Literal literal);
    bool match(char expected);
    char peekNext() const;
    // Literals
    void string();
    void number();
    void identifier();

    void cstyle_block_comment();

    bool isAtEnd() const
    {
        return _current >= _source.length();
    }

    void error(size_t line, std::string message)
    {
        report(line, "", message);
    }

    void report(size_t line, std::string where, std::string message)
    {
        std::stringstream ss;
        ss << "[line " << line << "] Error" << where << ": " << message;
        Lox::Log::instance().add(ss.str());
        //os << Lox::Log::instance().get();

        setHadError(true);
    }
};

}

#endif
