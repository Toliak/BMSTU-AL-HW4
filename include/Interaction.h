#pragma once

#include <functional>
#include "Console.h"

#include "Database.h"
#include "Interaction.h"

class Command;

struct Interaction
{
private:
    static Interaction *instance;
    Interaction() = default;

    ~Interaction();

protected:
    Console console;
    std::unordered_map<std::string, HybridDatabase> data = {};
    HybridDatabase *currentDatabase = nullptr;

    std::unordered_map<std::string, Command *> commands = {};

public:
    Interaction(const Interaction &) = delete;
    Interaction(Interaction &&) = delete;

    Interaction &operator=(const Interaction &) = delete;
    Interaction &operator=(Interaction &&) = delete;

    static Interaction &getInstance()
    {
        if (!Interaction::instance) {
            // Exists till the program closed
            Interaction::instance = new Interaction();
        }
        return *Interaction::instance;
    }

    bool registerCommand(const std::string &name, Command *command) noexcept;

    void executeCommand(const std::pair<std::string, std::string> &pair);

    void setCurrentDatabase(HybridDatabase *interactionCurrentDatabase) noexcept
    {
        Interaction::currentDatabase = interactionCurrentDatabase;
    }

    HybridDatabase *getCurrentDatabase() const noexcept
    {
        return Interaction::currentDatabase;
    }

    Console &getConsole() noexcept
    {
        return console;
    }

    std::unordered_map<std::string, HybridDatabase> &getData() noexcept
    {
        return data;
    }

    std::unordered_map<std::string, Command *> &getCommands() noexcept
    {
        return commands;
    }
};

