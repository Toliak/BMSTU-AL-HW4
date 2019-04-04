#pragma once

#include <exception>

class Exception: virtual public std::exception
{
private:
    std::string errorText;

public:
    explicit Exception(std::string text)
        : errorText(std::move(text))
    {

    }

    const char *what() const noexcept override
    {
        return errorText.c_str();
    }
};

class ModelException: public Exception
{
public:
    explicit ModelException(std::string text)
        : Exception(std::move(text))
    {}
};

class BaseSubdivisionModelException: public ModelException
{
public:
    explicit BaseSubdivisionModelException(std::string text)
        : ModelException(std::move(text))
    {}
};

class ProjectModelException final: public ModelException
{
public:
    explicit ProjectModelException(std::string text)
        : ModelException(std::move(text))
    {}
};

class CourseModelException final: public ModelException
{
public:
    explicit CourseModelException(std::string text)
        : ModelException(std::move(text))
    {}
};