#pragma once

#include <sstream>
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>

#include "Exception.h"


/**
 * @brief (Скрытая структура) Преобразует строку в тип T
 * @private Скрытая структура
 * @tparam T Тип возвращаемого значения
 */
template<typename T>
struct _fromString
{
    T value;        ///< Результат

    explicit _fromString(const std::string &string)
    {
        // Создание потока
        std::stringstream ss;

        // Записывание строки, затем считывание необходимого типа
        ss << string;
        ss >> value;
    }
};


/**
 * @brief (Скрытая структура) Заглушка для преобразования строки в строку
 */
template<>
struct _fromString<std::string>
{
    std::string value;
    explicit _fromString(std::string string)
        : value(std::move(string))
    {
        // Преобразование строки в строку не требует преобразований
    }
};


/**
 * @brief Преобразовывает строку в тип T
 * @tparam T Результирующий тип
 * @param string Исходная строка
 * @return Значение типа T, полученное из исходной строки
 */
template<typename T>
T fromString(const std::string &string)
{
    // Создает структуру (которая обрабатывает значение)
    return _fromString<T>(string).value;
}


/**
 * @brief (Скрытая структура) Содержит числа в шаблоне (для compile-time операций)
 * @tparam T Числа
 */
template<int ...T>
struct _Numbers
{
};


/**
 * @brief (Скрытая структура) Добавляет N к последовательности чисел в compile-time
 * @tparam N Добавляемое число
 * @tparam T Последовательность
 */
template<int N, typename T>
struct _GenerateNumbers
{
};


/**
 * @brief (Скрытая структура) Добавляет N к последовательности чисел в compile-time
 * @tparam N Добавляемое число
 * @tparam T Числа последовательности
 */
template<int N, int ...T>
struct _GenerateNumbers<N, _Numbers<T...>>
{
    // Рекурсивное описание типа структуры, добавляющей N-1
    using type = typename _GenerateNumbers<N - 1, _Numbers<N, T...>>::type;
};


/**
 * @brief (Скрытая структура) Ничего не делает, если нужно добавлять 0
 * @tparam T Числа последовательности
 */
template<int ...T>
struct _GenerateNumbers<0, _Numbers<T...>>
{
    // Описывает переданную последовательность
    using type = _Numbers<T...>;
};


/**
 * @brief (Скрытая структура) Используется для разбиения строки
 * @tparam T Описание шаблонов
 */
template<class ...T>
struct _splitString
{
};


/**
 * @brief (Скрытая структура) Используется для разбиения строки
 * @tparam B Последовательность чисел
 * @tparam T Типы
 */
template<int ...B, class ...T>
struct _splitString<_Numbers<B...>, T...>
{
    std::tuple<T...> value;             ///< Результат

    explicit _splitString(std::vector<std::string>::const_iterator &iterator)
    {
        // Сборка кортежа из B-1 строки, преобразованной к типу T
        // Причем, B и T (которые являются последовательностями чисел и типов, соответственно) раскрываются одновременно
        value = std::make_tuple(fromString<T>(*(iterator + (B - 1)))...);
    }
};


/**
 * @brief Разделяет строку и приводит подстроки к указанным типам
 * @tparam T Приводимые типы
 * @param line Исходная строка
 * @param splitter Символ разделения
 * @param remain Указатель на строку, в которую записывается неиспользуемая часть исходной
 * @return Кортеж из значений приводимых типов
 */
template<typename ...T>
std::tuple<T...> splitString(std::string line, char splitter = ' ', std::string *const remain = nullptr)
{
    // Пустая строка не приводится
    if (line.empty()) {
        throw SplitShortcutException("splitString: expected non-empty string");
    }

    constexpr size_t templateSize = sizeof...(T);       ///< Количество шаблонных параметров
    std::vector<std::string> substrings;                ///< Вектор подстрок
    std::string::const_iterator iterator;               ///< Итератор по строке
    size_t separatorCounter = 0;                        ///< Количество разделителей

    // Обход строки, пока есть симолы разделители
    while ((iterator = std::find(line.cbegin(), line.cend(), splitter)) != line.cend()) {
        substrings.emplace_back(line.cbegin(), iterator);   // Добавление в вектор подстрок новой подстроки
        line = std::string(iterator + 1, line.cend());      // Изменение строки
        separatorCounter++;                                 // Увеличение счетчика
        if (separatorCounter >= templateSize) {             // Считано достаточное количество подстрок
            break;
        }
    }

    // При недостатке количества подстрок - добавление конечной
    if (separatorCounter < templateSize && !line.empty()) {
        substrings.emplace_back(line);
        line.clear();                   // Очистка
    }

    // Если существует указатель на остаточную строку, то копирование в нее остатка
    if (remain) {
        *remain = line;
    }

    // Подстрок меньше, чем ожидаемых значений
    if (substrings.size() < templateSize) {
        throw SplitShortcutException("splitString: excepted at least " + std::to_string(templateSize) + " substrings");
    }

    auto resultIterator = substrings.cbegin();      ///< Итератор, по которому будет бегать сборщик кортежа

    // Сборка кортежа из последовательности чисел (1, ..., n), типов и итератора
    return _splitString<typename _GenerateNumbers<templateSize, _Numbers<>>::type, T...>(resultIterator).value;
}


/**
 * @brief Преобразует вектор в строку, используя переданную функцию
 * @tparam T Тип вектора
 * @tparam F Тип функции
 * @param vector Преобразуемый вектор
 * @param stringify Функция преобразования (принимает T, возвращает std::string)
 * @return Преобразованная строка
 */
template<typename T, typename F>
std::string vectorToString(const std::vector<T> &vector, F stringify)
{
    std::string result = std::to_string(vector.size());    ///< Результат. Содержит размер вектора

    // Не дописываем перенос строки, если вектор пустой
    if (!vector.empty()) {
        result += "\n";
    }

    auto preEndIterator = vector.cend();                                       ///< Предпоследний итератор
    preEndIterator--;                   // Перемещение итератора на 1 назад

    // Обход вектора
    for (auto it = vector.cbegin(); it != vector.cend(); it++) {
        // Добавление преобразованного в строку значения
        result += stringify(*it);

        // Дописывание переноса строки, если значение не последнее
        if (it != preEndIterator) {
            result += "\n";
        }
    }

    return result;
}
