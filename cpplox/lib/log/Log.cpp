#include <log/Log.h>

namespace Lox {

void Log::add(std::string str, bool nl)
{
    _log += str;
    if (nl)
        _log += "\n";

    ++_nlogs;
}

void Log::clear()
{
    _log.clear();
    _nlogs = 0;
}

}
