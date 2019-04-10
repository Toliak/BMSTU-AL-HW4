#pragma once

#include <functional>
#include "Console.h"

#include "Database.h"
#include "Interaction.h"

// Описание класса Command, для использование в коде ниже
class Command;

/**
 * @brief Синглтон класс, отвечающий за взаимодействие между пользователем и программой
 */
class Interaction
{
private:
    static Interaction *instance;       ///< Единственный объект данного типа

    Interaction() = default;
    ~Interaction();

protected:
    Console console;                                            ///< Консоль
    std::unordered_map<std::string, HybridDatabase> data = {};  ///< Словарь (название, БД)
    HybridDatabase *currentDatabase = nullptr;                  ///< Указатель на текущую базу данных
    std::unordered_map<std::string, Command *> commands = {};   ///< Зарегистрированные команды

public:
    // Для синглтон класса удалены конструкторы копирования и перемещения

    Interaction(const Interaction &) = delete;
    Interaction(Interaction &&) = delete;

    Interaction &operator=(const Interaction &) = delete;
    Interaction &operator=(Interaction &&) = delete;

    /**
     * @return Экземляр класса
     */
    static Interaction &getInstance()
    {
        // Создает экземпляр, если он не был создан
        if (!Interaction::instance) {
            // Exists till the program closed
            Interaction::instance = new Interaction();
        }
        return *Interaction::instance;
    }

    /**
     * @brief Регистрирует команду
     * @param name Название команды
     * @param command Указатель на объект класса Command (либо наследованного от него класса)
     * @return Статус
     */
    bool registerCommand(const std::string &name, Command *command) noexcept;

    /**
     * @brief Выполняет команду
     * @param pair Пара строк (команда, аргументы)
     * @throw ExecuteInteractionException если команда не найдена
     */
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

