/**
 * @brief Logging
 */
#ifndef LOG_LOX_H_
#define LOG_LOX_H_

#include <cstddef>

#include <string>

namespace Lox {

class Log {
public:
    void add(std::string str, bool nl=true);
    void clear();

    std::string get() const
    {
        return _log;
    }

    size_t getNumLogs() const
    {
        return _nlogs;
    }

    static Log &instance()
    {
        static Log inst;
        return inst;
    }

private:
    Log() : _nlogs { 0 }, _log { "" } {};

    std::string _log;
    size_t _nlogs;

};

}

#endif
