#pragma once

#include <exception>

class Exception: virtual public std::exception
{
private:
    std::string errorText = "";

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

class ShortcutException: public Exception
{
public:
    explicit ShortcutException(const std::string &text)
        : Exception(text)
    {}
};

class SplitShortcutException final: public ShortcutException
{
public:
    explicit SplitShortcutException(const std::string &text)
        : ShortcutException(text)
    {}
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

class DatabaseException: public Exception
{
public:
    explicit DatabaseException(const std::string &text)
        : Exception(text)
    {}
};

class HybridDatabaseException final: public DatabaseException
{
public:
    explicit HybridDatabaseException(const std::string &text)
        : DatabaseException(text)
    {}
};

class InteractionException: public Exception
{
public:
    explicit InteractionException(const std::string &text)
        : Exception(text)
    {}
};

class ExecuteInteractionException final: public InteractionException
{
public:
    explicit ExecuteInteractionException(const std::string &text)
        : InteractionException(text)
    {}
};