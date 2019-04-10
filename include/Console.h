#pragma once

#include <string>
#include <unordered_map>
#include <list>
#include <algorithm>

#include "Shortcut.h"

class Console
{
private:
    std::istream *istream = nullptr;
    std::ostream *ostream = nullptr;

    std::list<std::string> prefixes = {};

public:
    Console() = default;

    Console(std::istream &istream, std::ostream &ostream)
        : istream(&istream), ostream(&ostream)
    {

    }

    std::istream &getIstream() const noexcept
    {
        return *istream;
    }

    std::ostream &getOstream() const noexcept
    {
        return *ostream;
    }

    std::list<std::string> &getPrefixes() noexcept
    {
        return prefixes;
    }

    void start() const
    {
        *ostream << "Welcome to the Toliak's DB.\nEnter 'help' to get available commands." << std::endl;
    }

    /**
     * @brief Выводит текст, затем считывает строку, приводя ее к указанному типу
     * @tparam T Приводимый тип
     * @param output Вывод в поток, перед захватом строки
     * @return Приводимый тип, переведенный из строки
     */
    template<typename T>
    T pureInput(const std::string &output)
    {
        *ostream << output;
        std::string input;
        std::getline(*istream, input);
        return fromString<T>(input);
    }

    /**
     * @brief Считывает строки из консоли
     * @return Введенная строка
     */
    std::string getLine();

    /**
     * @brief Разделяет строку на команду и аргументы
     * @param line Исходная строка
     * @return Пара строк вида (команда, аргуметы)
     */
    static std::pair<std::string, std::string> divideCommand(const std::string &line);
};