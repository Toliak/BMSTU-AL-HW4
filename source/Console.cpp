#include "Console.h"

std::string Console::getLine()
{
    for (const auto& it : prefixes) {
        *ostream << it << " ";
    }
    *ostream << "> ";

    std::string command;
    std::getline(*istream, command);
    return command;
}

std::pair<std::string, std::string> Console::divideCommand(const std::string &line)
{
    auto iterator = std::find(line.cbegin(), line.cend(), ' ');
    if (iterator == line.cend()) {
        return {line, ""};
    }

    return {
        std::string(line.cbegin(), iterator),
        std::string(iterator + 1, line.cend())
    };
}
