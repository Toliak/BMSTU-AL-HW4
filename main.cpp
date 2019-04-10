#include <iostream>
#include <functional>
#include <iomanip>

#include "Console.h"
#include "Database.h"
#include "Interaction.h"
#include "Exception.h"

void test()
{
    ProjectModel p("", 0);
    p.fromString("asdasdasdasdpa posdpa ojspfoaj sofapofj \n5252");

    std::string remain;
    auto result0 = splitString<int, std::string>("3\nasdasd asd asd\nasdasda sdas d\n5.6\n686", '\n');
    auto result1 = splitString<int, std::string>("3\nasdasd asd asd", '\n', &remain);

    EducationalSubdivisionModel es("", "", 1, 1);

    std::string result2 = es.fromString("Test tested\nThe big director\n14\n500\n2\nasd\n4\nHEH\n600\ndfgdfg");

    ScientificSubdivisionModel ss("", "", 1, 1);

    std::string result3 = ss.fromString("Test tested\nThe big director\n14\n500\n2\n1\n14\n400\n4\n70\n600\ndfg dfg");

    HybridDatabase db("");
    db.fromString("test\n"
                  "1\n"
                  "EducationalSubdivisionModel\n"
                  "ASDadasd\n"
                  "ASdaSdadsasda\n"
                  "1312\n"
                  "13123\n"
                  "1\n"
                  "Projecascasdas\n"
                  "555"
    );

    std::vector<BaseSubdivisionModel *> &v = db;

    std::cout << es.toString() << std::endl;
    std::cout << ss.toString() << std::endl;
}

int main()
{
    test();

    auto &interaction = Interaction::getInstance();

    interaction.getConsole() = std::move(Console(std::cin, std::cout));
    Console &console = interaction.getConsole();
    console.start();

    std::string command;
    while ((command = console.getLine()) != "exit") {
        try {
            interaction.executeCommand(Console::divideCommand(command));
        } catch (SplitShortcutException &e) {
            console.getOstream() << "Arguments mismatch" << std::endl
                                 << "\t" << e.what() << std::endl;
        } catch (Exception &e) {
            console.getOstream() << e.what() << std::endl;
        }
    }

    console.getOstream() << "Bye" << std::endl;
    return 0;
}