#pragma once

#include <string>

#include "Exception.h"
#include "Shortcut.h"

class Model
{
public:
    virtual std::string toString() const = 0;
    virtual void fromString(const std::string &) = 0;
};

class Project: virtual public Model
{
private:
    std::string name;
    size_t price;

public:
    Project(std::string name, size_t price)
    {
        setName(name);
        setPrice(price);
    }

    void setName(std::string name)
    {
        Project::name = std::move(name);
    }

    void setPrice(size_t price)
    {
        if (price > 50000) {
            throw ProjectException("Project's maximum price is 50000");
        }
        Project::price = price;
    }

    std::string toString() const
    {
        return (name + std::string("\n") + std::to_string(price));
    }

    void fromString(const std::string &string)
    {
        splitString<std::string, size_t>(string, '\n');
    }

};

class BaseSubdivision : virtual public Model
{
private:
    std::string name;
    std::string director;
    size_t graduateAmount;
    size_t employeeAmount;

public:
    virtual size_t getStudentsAmount() const noexcept = 0;
};
