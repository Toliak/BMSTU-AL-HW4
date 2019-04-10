#pragma once
#include "Model/Model.h"

#include <utility>
#include <string>

#include "Interaction.h"

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


class Command
{
public:
    virtual void execute(const std::string &string) = 0;

    virtual ~Command() = default;
};