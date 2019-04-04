#include <utility>

#include <utility>

#pragma once

#include <vector>
#include <fstream>

#include "Exception.h"
#include "Model.h"

class BaseDatabase
{
protected:
    std::string name;

public:
    explicit BaseDatabase(std::string name)
        : name(std::move(name))
    {}

    virtual std::string fromString(const std::string &string) = 0;

    virtual std::string toString() const = 0;

    virtual ~BaseDatabase() = default;
};

template <class T>
class SingleDatabase: virtual public BaseDatabase
{
    std::vector<T> models;

public:
    using ModelType = T;

    explicit SingleDatabase(const std::string& name)
        : BaseDatabase(name)
    {}

    std::vector<T> &getModels()
    {
        return models;
    }

    std::string fromString(const std::string &string) override
    {
        return std::__cxx11::string();
    }

    std::string toString() const override
    {
        return BaseDatabase::name + std::string("\n") + vectorToString(models);
    }
};