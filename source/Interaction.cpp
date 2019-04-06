#include "Interaction.h"


void Interaction::executeCommand(const std::pair<std::string, std::string> &pair)
{
    auto iterator = Interaction::commands.find(pair.first);
    if (iterator == Interaction::commands.cend()) {
        throw ExecuteInteractionException("Command '" + pair.first + "' not found");
    }

    return iterator->second->execute(pair.second);
}

bool Interaction::registerCommand(const std::string &name, Command *command) noexcept
{
    auto result = commands.insert({name, command});
    return result.second;
}

Interaction::~Interaction()
{
    while (Interaction::commands.begin() != Interaction::commands.end()) {
        delete Interaction::commands.begin()->second;
        Interaction::commands.erase(Interaction::commands.begin());
    }
}

Interaction *Interaction::instance = nullptr;