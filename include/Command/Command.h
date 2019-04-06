#pragma once

#include <utility>
#include <string>

#define REGISTER_COMMAND(commandName)             \
class Command_##commandName: public Command                 \
{                                                           \
    void execute(const std::string &string);                 \
                                                            \
    static bool registerCommandResult;                      \
};                                                          \
bool Command_##commandName::registerCommandResult =         \
Interaction::getInstance().registerCommand(#commandName, new Command_##commandName()); \
void Command_##commandName::execute(const std::string &string)


class Command
{
public:
    virtual void execute(const std::string &string) = 0;

    virtual ~Command() = default;
};