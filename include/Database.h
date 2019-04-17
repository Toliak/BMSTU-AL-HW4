#pragma once

#include <vector>

#include "Model/BaseSubdivisionModel.h"

/**
 * @brief Абстрактный класс БД
 */
class BaseDatabase
{
protected:
    std::string name;                       ///< Название БД

public:
    explicit BaseDatabase(std::string name)
        : name(std::move(name))
    {}

    const std::string &getName() const
    {
        return name;
    }

    BaseDatabase(BaseDatabase &&) = default;

    // Копирование недопустимо

    BaseDatabase(const BaseDatabase &) = delete;
    BaseDatabase &operator=(const BaseDatabase &) = delete;

    virtual std::string fromString(const std::string &string) = 0;

    virtual std::string toString() const = 0;

    virtual ~BaseDatabase() = default;
};

/**
 * @brief Гибридная БД
 */
class HybridDatabase: virtual public BaseDatabase, public std::vector<BaseSubdivisionModel *>
{
public:
    explicit HybridDatabase(const std::string &name)
        : BaseDatabase(name)
    {}

    HybridDatabase(HybridDatabase &&) = default;

    // Копирование недопустимо

    HybridDatabase(const HybridDatabase &) = delete;
    HybridDatabase &operator=(const HybridDatabase &) = delete;

    ~HybridDatabase() override;

    std::string fromString(const std::string &string) override;

    std::string toString() const override;
};