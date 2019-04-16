#include "Interaction.h"
#include "Command.h"

void Interaction::executeCommand(const std::pair<std::string, std::string> &pair)
{
    // Нахождение команды
    auto iterator = Interaction::commands.find(pair.first);            ///< Итератор, содержащий (команду, функцию)
    if (iterator == Interaction::commands.cend()) {
        throw ExecuteInteractionException("Command '" + pair.first + "' not found");
    }

    // Выполнение функции, связанной с командой
    return iterator->second->execute(pair.second);
}

bool Interaction::registerCommand(const std::string &name, Command *command) noexcept
{
    const auto result = commands.insert({name, command});     ///< Результат добавления
    return result.second;
}

Interaction::~Interaction()
{
    // Пока есть команды
    while (Interaction::commands.begin() != Interaction::commands.end()) {
        delete Interaction::commands.begin()->second;               // Производится очистка памяти
        Interaction::commands.erase(Interaction::commands.begin()); // Производится удаление из словаря
    }
}

Interaction *Interaction::instance = nullptr;                       // Объявление статического поля