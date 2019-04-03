#pragma once

#include <exception>

class Exception : virtual public std::exception
{
private:
    std::string errorText;

public:
    Exception(std::string text) :
        errorText(std::move(text))
    {

    }

    virtual const char *what() const noexcept
    {
        return errorText.c_str();
    }
};

class ProjectException: virtual public Exception
{
public:
    ProjectException(std::string text) :
        Exception(std::move(text))
    {

    }
};