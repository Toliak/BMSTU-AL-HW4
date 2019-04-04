#include <utility>

#include <utility>

#pragma once

#include <string>

#include "Exception.h"
#include "Shortcut.h"

class Model
{
public:
    virtual std::string toString() const = 0;
    virtual void fromString(const std::string &) = 0;

    virtual ~Model() = default;
};

class Project: virtual public Model
{
private:
    std::string name;
    size_t price;

public:
    Project() = default;

    Project(std::string name, decltype(Project::price) price)
    {
        Project::setName(std::move(name));
        Project::setPrice(price);
    }

    void setName(std::string name)
    {
        Project::name = std::move(name);
    }

    void setPrice(decltype(Project::price) price)
    {
        if (price > 1000000) {
            throw ProjectModelException("Project: Price must be below 1000000");
        }
        Project::price = price;
    }

    const std::string &getName() const noexcept
    {
        return Project::name;
    }

    decltype(Project::price) getPrice() const noexcept
    {
        return Project::price;
    }

    std::string toString() const override
    {
        return (Project::name + std::string("\n") + std::to_string(Project::price));
    }

    void fromString(const std::string &string) override
    {
        std::tie(Project::name, Project::price) = splitString<std::string, size_t>(string, '\n');
    }
};

class BaseSubdivision: virtual public Model
{
protected:
    std::string name;
    std::string director;
    size_t graduateAmount;
    size_t employeeAmount;

public:
    BaseSubdivision(const std::string &name,
                    const std::string &director,
                    decltype(BaseSubdivision::graduateAmount) graduateAmount,
                    decltype(BaseSubdivision::employeeAmount) employeeAmount)
    {
        BaseSubdivision::setName(name);
        BaseSubdivision::setDirector(director);
        BaseSubdivision::setGraduateAmount(graduateAmount);
        BaseSubdivision::setEmployeeAmount(employeeAmount);
    }

    void setName(const std::string &name)
    {
        if (name.size() > 50) {
            throw BaseSubdivisionModelException("BaseSubdivision: Name size must be below 50");
        }
        BaseSubdivision::name = name;
    }
    void setDirector(const std::string &director)
    {
        if (director.size() > 50) {
            throw BaseSubdivisionModelException("BaseSubdivision: Director size must be below 50");
        }
        BaseSubdivision::director = director;
    }
    void setGraduateAmount(decltype(BaseSubdivision::graduateAmount) graduateAmount)
    {
        if (graduateAmount > 1000000) {
            throw BaseSubdivisionModelException("BaseSubdivision: Graduate amount must be below 1000000");
        }
        BaseSubdivision::graduateAmount = graduateAmount;
    }
    void setEmployeeAmount(decltype(BaseSubdivision::employeeAmount) employeeAmount)
    {
        if (employeeAmount > 1000000) {
            throw BaseSubdivisionModelException("BaseSubdivision: Graduate amount must be below 1000000");
        }
        BaseSubdivision::employeeAmount = employeeAmount;
    }

    const std::string &getName() const
    {
        return BaseSubdivision::name;
    }

    const std::string &getDirector() const
    {
        return BaseSubdivision::director;
    }

    decltype(BaseSubdivision::graduateAmount) getGraduateAmount() const
    {
        return BaseSubdivision::graduateAmount;
    }

    decltype(BaseSubdivision::employeeAmount) getEmployeeAmount() const
    {
        return BaseSubdivision::employeeAmount;
    }

    std::string toString() const override
    {
        return (
            BaseSubdivision::name + std::string("\n")
                + BaseSubdivision::director + std::string("\n")
                + std::to_string(BaseSubdivision::graduateAmount) + std::string("\n")
                + std::to_string(BaseSubdivision::employeeAmount)
        );
    }

    void fromString(const std::string &string) override
    {
        std::tie(
            BaseSubdivision::name,
            BaseSubdivision::director,
            BaseSubdivision::graduateAmount,
            BaseSubdivision::employeeAmount
        ) = splitString<
            decltype(BaseSubdivision::name),
            decltype(BaseSubdivision::director),
            decltype(BaseSubdivision::graduateAmount),
            decltype(BaseSubdivision::employeeAmount)
        >(string, '\n');
    }

    virtual decltype(BaseSubdivision::graduateAmount) getStudentsAmount() const noexcept = 0;
};

class EducationalSubdivision: virtual public BaseSubdivision
{
private:
    std::vector<Project> projects;

public:

    EducationalSubdivision(const std::string &name,
                           const std::string &director,
                           decltype(BaseSubdivision::graduateAmount) graduateAmount,
                           decltype(BaseSubdivision::employeeAmount) employeeAmount,
                           const std::vector<Project> &projects = {})
        : BaseSubdivision(name, director, graduateAmount, employeeAmount)
    {

    }

    decltype(BaseSubdivision::graduateAmount) getStudentsAmount() const noexcept override
    {
        return BaseSubdivision::graduateAmount;
    }

    std::string toString() const
    {
        std::string projects = std::to_string(EducationalSubdivision::projects.size()) + std::string("\n");
        auto preEndIterator = EducationalSubdivision::projects.cend();
        preEndIterator--;
        for (auto it = EducationalSubdivision::projects.cbegin(); it != EducationalSubdivision::projects.cend(); it++) {
            projects += it->toString();
            if (it != preEndIterator) {
                projects += "\n";
            }
        }

        return (
            BaseSubdivision::toString() + std::string("\n")
                + projects
        );
    }

    void fromString(const std::string &string) override
    {
        BaseSubdivision::fromString(string);
        //TODO: а что со строкой-то?
    }
};

class Course: virtual public Model
{
private:
    size_t studentAmount;
    size_t price;

public:
    Course(size_t studentAmount, size_t price)
    {
        setStudentAmount(studentAmount);
        setPrice(price);
    }

    void setStudentAmount(size_t amount)
    {
        if (amount > 1000000) {
            throw CourseModelException("Course: Students amount must be below 500");
        }
        Course::studentAmount = amount;
    }

    void setPrice(size_t price)
    {
        if (price > 1000000) {
            throw CourseModelException("Course: Price must be below 1000000");
        }
        Course::price = price;
    }
};


// TODO: заменить size_t на типы меньшей размерности

class ScientificSubdivision: virtual public BaseSubdivision
{
private:
    std::unordered_map<size_t, Course> courses;

public:
    std::string toString() const;
    void fromString(const std::string &);
};