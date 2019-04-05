#pragma once

#include <sstream>
#include <tuple>
#include <vector>
#include <string>

#include "Exception.h"

template <typename T>
struct _fromString
{
    T value;
    explicit _fromString(const std::string &string)
    {
        std::stringstream ss;
        ss << string;
        ss >> value;
    }
};

template <>
struct _fromString<std::string>
{
    std::string value;
    explicit _fromString(std::string string):
        value(std::move(string))
    {
        
    }
};

template <typename T>
T fromString(const std::string &string)
{
    return _fromString<T>(string).value;
}

template <int ...T>
struct _Numbers
{

};

template <int N, typename T>
struct _GenerateNumbers
{
    
};

template <int N, int ...T>
struct _GenerateNumbers<N, _Numbers<T...>>
{
    using type = typename _GenerateNumbers<N - 1, _Numbers<N, T...>>::type;
};

template <int ...T>
struct _GenerateNumbers<0, _Numbers<T...>>
{
    using type = _Numbers<T...>;
};

template<class ...T>
struct _splitString
{

};

template<int ...B, class ...T>
struct _splitString<_Numbers<B...>, T...>
{
    std::tuple<T...> value;
    explicit _splitString(std::vector<std::string>::const_iterator &iterator)
    {
        value = std::make_tuple(fromString<T>(*(iterator + (B - 1)))...);
    }
};


template<typename ...T>
std::tuple<T...> splitString(std::string line, char splitter = ' ', std::string * const remain = nullptr)
{
    constexpr size_t templateSize = sizeof...(T);
    std::vector<std::string> substrings;
    std::string::const_iterator iterator;
    size_t separatorCounter = 0;

    while ((iterator = std::find(line.cbegin(), line.cend(), splitter)) != line.cend()) {
        substrings.emplace_back(line.cbegin(), iterator);
        line = std::string(iterator + 1, line.cend());
        separatorCounter++;
        if (separatorCounter >= templateSize) {
            break;
        }
    }
    if (separatorCounter < templateSize) {
        substrings.emplace_back(line);
    } else if (remain) {
        *remain = line;
    }
    if (substrings.size() < templateSize) {
        throw SplitShortcutException("splitString: excepted at least " + std::to_string(templateSize) + " substrings");
    }

    auto resultIterator = substrings.cbegin();

    return _splitString<typename _GenerateNumbers<templateSize, _Numbers<>>::type, T...>(resultIterator).value;
}

/*
template <typename T>
struct _vectorToString
{
    std::string toString(typename std::vector<T>::const_iterator &value) const
    {
        return value->toString();
    }
};

template <typename T>
struct _vectorToString<T*>
{
    std::string toString(typename std::vector<T*>::const_iterator &value) const
    {
        return (*value)->toString();
    }
};
*/

template <typename T, typename F>
std::string vectorToString(const std::vector<T> &vector, F stringify)
{
    std::string result = std::to_string(vector.size()) + std::string("\n");
    auto preEndIterator = vector.cend();
    preEndIterator--;
    for (auto it = vector.cbegin(); it != vector.cend(); it++) {
        result += stringify(*it);
        if (it != preEndIterator) {
            result += "\n";
        }
    }

    return result;
}
