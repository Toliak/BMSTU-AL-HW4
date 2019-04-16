#include "Console.h"

std::string Console::getLine()
{
    // Сборка префиксов
    for (const auto &it : prefixes) {
        *ostream << it << " ";
    }
    *ostream << "> ";

    std::string command;                            ///< Введенная команда
    std::getline(*istream, command);
    return command;
}

std::pair<std::string, std::string> Console::divideCommand(const std::string &line)
{
    const auto iterator = std::find(line.cbegin(), line.cend(), ' ');         ///< Итератор, указывающий на первый пробел
    if (iterator == line.cend()) {
        return {line, ""};
    }

    return {
        std::string(line.cbegin(), iterator),
        std::string(iterator + 1, line.cend())
    };
}
