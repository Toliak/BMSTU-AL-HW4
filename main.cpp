#include <iostream>
#include <functional>

#include "Console.h"
#include "Database.h"

void executeCommand(Console &console, const std::pair<std::string, std::string> &pair)
{
    static std::unordered_map<std::string, std::function<void(Console &, const std::string &)>> commands = {
        {
            "help",
            [](Console &console, const std::string &)
            {
                executeCommand(console, {"?", ""});
            }
        },
        {
            "?",
            [](Console &console, const std::string &)
            {
                std::ostream &stream = console.getOstream();
                stream << "Available commands:" << std::endl;
                stream << "\t?, help - to get available commands" << std::endl;
                stream << "\tload - to load database from file" << std::endl;
                stream << "\tsave - to save database to file" << std::endl;
                stream << "\tgo [DB name] - to go into database" << std::endl;
                stream << "\tleave - to leave database to file" << std::endl;
                stream << "\texit - to exit" << std::endl;
            }
        },
    };

    auto iterator = commands.find(pair.first);
    if (iterator == commands.cend()) {
        console.getOstream() << "Command '" << pair.first << "' not found" << std::endl;
        return;
    }

    return iterator->second(console, pair.second);
}

int main()
{
    // _split<Numbers<1, 2, 3>, int, double, char>();

    using T = _GenerateNumbers<5, _Numbers<>>::type;
    auto t = T();

    auto tuple = splitString<int, double, std::string, char, std::string>("1\n3.6\nkkk kk\ni\nasd asd asd s", '\n');




    Console console(std::cin, std::cout);
    console.start();

    std::string command;
    while ((command = console.getLine()) != "exit") {
        executeCommand(console, console.divideCommand(command));
    }

    std::cout << "Bye" << std::endl;
    return 0;
}