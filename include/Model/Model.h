#pragma once

#include <string>

#include "Shortcut.h"

/**
 * @brief Абстрактный класс Model
 * @details Каждая модель наследуется от этого класса
 */
class Model
{
public:

    /**
     * @brief Получение названия модели
     */
    virtual std::string getModelName() const noexcept = 0;

    /**
     * @brief Приведение модели к строке
     * @return Строка, разделителем которой является символ переноса строки
     */
    virtual std::string toString() const = 0;

    /**
     * @brief Считывание данных из строки в модель
     * @details Данные из строки помещаются в поля класса
     * @param str Строка, разделителем которой является символ переноса строки
     * @return Остаток строки, который остался неиспользованной
     */
    virtual std::string fromString(const std::string &) = 0;

    /**
     * @brief Стандартный деструктор
     */
    virtual ~Model() = default;
};
