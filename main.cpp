#include <iostream>
#include <functional>
#include <iomanip>

#include "Console.h"
#include "Database.h"
#include "Interaction.h"
#include "Exception.h"

int main()
{
    // Получение объекта взаимодействия
    auto &interaction = Interaction::getInstance();

    // Создание обертки над потоками ввода/вывода
    interaction.getConsole() = std::move(Console(std::cin, std::cout));
    Console &console = interaction.getConsole();

    // Выведение стартового сообщения
    console.start();

    std::string command;
    // Ожидание команды (выход на команде exit)
    while ((command = console.getLine()) != "exit") {
        try {
            // Попытка выполнения команды (предварительно разделив входную строку на команду и аргументы)
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