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

    const std::string &getName() const
    {
        return name;
    }

    BaseDatabase(BaseDatabase&&) = default;
    BaseDatabase(const BaseDatabase&) = delete;
    BaseDatabase& operator=(const BaseDatabase&) = delete;

    virtual std::string fromString(const std::string &string) = 0;

    virtual std::string toString() const = 0;

    virtual ~BaseDatabase() = default;
};

class HybridDatabase: virtual public BaseDatabase, public std::vector<BaseSubdivision*>
{
public:
    explicit HybridDatabase(const std::string &name)
        : BaseDatabase(name)
    {}

    std::string fromString(const std::string &string) override
    {
        std::string remain;
        size_t elementAmount;
        std::tie(BaseDatabase::name, elementAmount) = splitString<std::string, size_t>(string, '\n', &remain);

        for (size_t i = 0; i < elementAmount; i++) {
            std::string modelType;
            std::tie(modelType) = splitString<std::string>(remain, '\n', &remain);

            BaseSubdivision *subdivision;
            if (modelType == "EducationalSubdivision") {
                subdivision = new EducationalSubdivision("","",0,0);
            } else if (modelType == "ScientificSubdivision") {
                subdivision = new ScientificSubdivision("","",0,0);
            } else {
                throw HybridDatabaseException("HybridDatabase: wrong model type");
            }
            remain = subdivision->fromString(remain);
            std::vector<BaseSubdivision*>::emplace_back(subdivision);
        }

        return remain;
    }

    std::string toString() const override
    {
        return BaseDatabase::name + std::string("\n") + vectorToString(
            *this,
            [](const BaseSubdivision * const baseSubdivision) {
                return baseSubdivision->getModelName() + std::string("\n") + baseSubdivision->toString();
            }
        );
    }
};