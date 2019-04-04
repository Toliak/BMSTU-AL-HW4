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

void test()
{
    Project p("",0);
    p.fromString("asdasdasdasdpa posdpa ojspfoaj sofapofj \n5252");

    std::string remain;
    auto result0 = splitString<int, std::string>("3\nasdasd asd asd\nasdasda sdas d\n5.6\n686", '\n');
    auto result1 = splitString<int, std::string>("3\nasdasd asd asd", '\n', &remain);

    EducationalSubdivision es("","",1,1);

    std::string result2 = es.fromString("Test tested\nThe big director\n14\n500\n2\nasd\n4\nHEH\n600\ndfgdfg");

    ScientificSubdivision ss("","",1,1);

    std::string result3 = ss.fromString("Test tested\nThe big director\n14\n500\n2\n1\n14\n400\n4\n70\n600\ndfg dfg");

    std::cout << es.toString() << std::endl;
    std::cout << ss.toString() << std::endl;

    return;
}

int main()
{
    test();

    Console console(std::cin, std::cout);
    console.start();

    std::string command;
    while ((command = console.getLine()) != "exit") {
        executeCommand(console, console.divideCommand(command));
    }

    std::cout << "Bye" << std::endl;
    return 0;
}