#pragma once

#include <string>
#include <unordered_map>
#include <list>

class Console
{
private:
    std::istream *istream;
    std::ostream *ostream;
    
    std::list<std::string> prefixes;

public:
    Console(std::istream &istream, std::ostream &ostream):
        istream(&istream), ostream(&ostream)
    {

    }

    std::istream &getIstream() const noexcept
    {
        return *istream;
    }

    std::ostream &getOstream() const noexcept
    {
        return *ostream;
    }

    std::list<std::string> &getPrefixes() noexcept
    {
        return prefixes;
    }

    void start() const
    {
        *ostream << "Welcome to the Toliak's DB.\nEnter ? or 'help' to get available commands." << std::endl;
    }

    std::string getLine()
    {
        for (auto it : prefixes) {
            *ostream << it << " ";
        }
        *ostream << "> ";

        std::string command;
        std::getline(*istream, command);
        return command;
    }

    static std::pair<std::string, std::string> divideCommand(const std::string &line)
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
};