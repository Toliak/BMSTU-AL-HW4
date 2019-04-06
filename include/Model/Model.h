#include <utility>

#include <utility>

#include <utility>

#pragma once

#include <unordered_map>
#include <string>

#include "Exception.h"
#include "Shortcut.h"

class Model
{
public:
    virtual std::string getModelName() const noexcept = 0;
    virtual std::string toString() const = 0;
    virtual std::string fromString(const std::string &) = 0;

    virtual ~Model() = default;
};


// TODO: заменить size_t на типы меньшей размерности
