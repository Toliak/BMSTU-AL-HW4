#pragma once

#include <string>

#include "Interaction.h"

/**
 * @brief Макрос для создания команд
 * @detail Создается класс с описанной функцией. Объект класса регистрируется
 * @param commandName Название команды
 * @param f Тело функции (как аргумент используется строка аргументов команды)
 */
#define REGISTER_COMMAND(commandName)             \
class Command_##commandName: public Command                 \
{                                                           \
    void execute(const std::string &string);                 \
                                                            \
    static bool registerCommandResult;                      \
};                                                          \
bool Command_##commandName::registerCommandResult =         \
/* Exists till the program closed         */             \
Interaction::getInstance().registerCommand(#commandName, new Command_##commandName()); \
void Command_##commandName::execute(const std::string &string)


/**
 * @brief Абстрактный класс команды
 */
class Command
{
public:
    virtual void execute(const std::string &string) = 0;

    virtual ~Command() = default;
};