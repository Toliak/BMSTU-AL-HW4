#pragma once

#include <string>
#include <unordered_map>
#include <list>
#include <algorithm>

#include "Shortcut.h"

class Console
{
private:
    std::istream *istream = nullptr;
    std::ostream *ostream = nullptr;
    
    std::list<std::string> prefixes = {};

public:
    Console() = default;

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
        *ostream << "Welcome to the Toliak's DB.\nEnter 'help' to get available commands." << std::endl;
    }

    template <typename T>
    T pureInput(const std::string &output)
    {
        *ostream << output;
        std::string input;
        std::getline(*istream, input);
        return fromString<T>(input);
    }

    std::string getLine();

    static std::pair<std::string, std::string> divideCommand(const std::string &line);
};