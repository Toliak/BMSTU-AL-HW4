#include <utility>

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
    virtual std::string fromString(const std::string &) = 0;

    virtual ~Model() = default;
};

class Project: virtual public Model
{
private:
    std::string name;
    size_t price = 0;

public:
    Project(std::string name, decltype(Project::price) price)
    {
        Project::setName(std::move(name));
        Project::setPrice(price);
    }

    void setName(std::string projectName)
    {
        Project::name = std::move(projectName);
    }

    void setPrice(decltype(Project::price) projectPrice)
    {
        if (projectPrice > 1000000) {
            throw ProjectModelException("Project: Price must be below 1000000");
        }
        Project::price = projectPrice;
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

    std::string fromString(const std::string &string) override
    {
        std::string remain;

        std::tie(
            Project::name,
            Project::price
        ) = splitString<
            decltype(Project::name),
            decltype(Project::price)
        >(string, '\n', &remain);

        return remain;
    }
};

class BaseSubdivision: virtual public Model
{
protected:
    std::string name;
    std::string director;
    size_t graduateAmount = 0;
    size_t employeeAmount = 0;

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

    void setName(const std::string &subdivisionName)
    {
        if (subdivisionName.size() > 50) {
            throw BaseSubdivisionModelException("BaseSubdivision: Name size must be below 50");
        }
        BaseSubdivision::name = subdivisionName;
    }
    void setDirector(const std::string &subdivisionDirector)
    {
        if (director.size() > 50) {
            throw BaseSubdivisionModelException("BaseSubdivision: Director size must be below 50");
        }
        BaseSubdivision::director = subdivisionDirector;
    }
    void setGraduateAmount(decltype(BaseSubdivision::graduateAmount) subdivisionGraduateAmount)
    {
        if (subdivisionGraduateAmount > 1000000) {
            throw BaseSubdivisionModelException("BaseSubdivision: Graduate amount must be below 1000000");
        }
        BaseSubdivision::graduateAmount = subdivisionGraduateAmount;
    }
    void setEmployeeAmount(decltype(BaseSubdivision::employeeAmount) subdivisionEmployeeAmount)
    {
        if (subdivisionEmployeeAmount > 1000000) {
            throw BaseSubdivisionModelException("BaseSubdivision: Graduate amount must be below 1000000");
        }
        BaseSubdivision::employeeAmount = subdivisionEmployeeAmount;
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

    std::string fromString(const std::string &string) override
    {
        std::string remain;

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
        >(string, '\n', &remain);

        return remain;
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
                           decltype(std::declval<BaseSubdivision>().getGraduateAmount()) graduateAmount,
                           decltype(std::declval<BaseSubdivision>().getEmployeeAmount()) employeeAmount,
                           std::vector<Project> projects = {})
        : BaseSubdivision(name, director, graduateAmount, employeeAmount), projects(std::move(projects))
    {}

    decltype(std::declval<BaseSubdivision>().getGraduateAmount()) getStudentsAmount() const noexcept override
    {
        return BaseSubdivision::graduateAmount;
    }

    std::vector<Project> &getProjects()
    {
        return EducationalSubdivision::projects;
    }

    std::string toString() const override
    {
        std::string projectsString = std::to_string(EducationalSubdivision::projects.size()) + std::string("\n");
        auto preEndIterator = EducationalSubdivision::projects.cend();
        preEndIterator--;
        for (auto it = EducationalSubdivision::projects.cbegin(); it != EducationalSubdivision::projects.cend(); it++) {
            projectsString += it->toString();
            if (it != preEndIterator) {
                projectsString += "\n";
            }
        }

        return (
            BaseSubdivision::toString() + std::string("\n")
                + projectsString
        );
    }

    std::string fromString(const std::string &string) override
    {
        std::string remain = BaseSubdivision::fromString(string);
        EducationalSubdivision::projects.clear();

        size_t projectsAmount;
        std::tie(projectsAmount) = splitString<size_t>(remain, '\n', &remain);
        for (size_t i = 0; i < projectsAmount; i++) {
            Project project("", 0);
            remain = project.fromString(remain);
            EducationalSubdivision::projects.emplace_back(project);
        }

        return remain;
    }
};

class Course: virtual public Model
{
private:
    size_t studentAmount = 0;
    size_t price = 0;

public:
    Course(decltype(Course::studentAmount) studentAmount, decltype(Course::price) price)
    {
        Course::setStudentAmount(studentAmount);
        Course::setPrice(price);
    }

    void setStudentAmount(decltype(Course::studentAmount) amount)
    {
        if (amount > 1000000) {
            throw CourseModelException("Course: Students amount must be below 500");
        }
        Course::studentAmount = amount;
    }

    void setPrice(decltype(Course::price) coursePrice)
    {
        if (coursePrice > 1000000) {
            throw CourseModelException("Course: Price must be below 1000000");
        }
        Course::price = coursePrice;
    }

    decltype(Course::studentAmount) getStudentAmount() const
    {
        return studentAmount;
    }

    decltype(Course::price) getPrice() const
    {
        return price;
    }

    std::string toString() const override
    {
        return (std::to_string(Course::studentAmount) + std::string("\n") + std::to_string(Course::price));
    }

    std::string fromString(const std::string &string) override
    {
        std::string remain;

        std::tie(
            Course::studentAmount,
            Course::price
        ) = splitString<
            decltype(Course::studentAmount),
            decltype(Course::price)
        >(string, '\n', &remain);

        return remain;
    }
};


// TODO: заменить size_t на типы меньшей размерности

class ScientificSubdivision: virtual public BaseSubdivision
{
private:
    std::unordered_map<size_t, Course> courses;

public:
    ScientificSubdivision(const std::string &name,
                          const std::string &director,
                          size_t graduateAmount,
                          size_t employeeAmount,
                          std::unordered_map<size_t, Course> courses = {})
        : BaseSubdivision(name, director, graduateAmount, employeeAmount), courses(std::move(courses))
    {}

    decltype(std::declval<BaseSubdivision>().getGraduateAmount()) getStudentsAmount() const noexcept override
    {
        decltype(std::declval<BaseSubdivision>().getGraduateAmount()) returnValue = 0;
        for (const auto &it : courses) {
            returnValue += it.second.getStudentAmount();
        }
        return BaseSubdivision::graduateAmount + returnValue;
    }

    std::string toString() const override
    {
        std::string coursesString = std::to_string(ScientificSubdivision::courses.size()) + std::string("\n");
        for (const auto &course : ScientificSubdivision::courses) {
            coursesString += std::to_string(course.first) + std::string("\n") + course.second.toString();
            coursesString += "\n";
        }
        coursesString = coursesString.substr(0, coursesString.size() - 1);

        return (
            BaseSubdivision::toString() + std::string("\n")
                + coursesString
        );
    }

    std::string fromString(const std::string &string) override
    {
        std::string remain = BaseSubdivision::fromString(string);
        ScientificSubdivision::courses.clear();

        size_t projectsAmount;
        std::tie(projectsAmount) = splitString<size_t>(remain, '\n', &remain);
        for (size_t i = 0; i < projectsAmount; i++) {
            Course course(0, 0);
            decltype(courses)::key_type key;
            std::tie(key) = splitString<decltype(key)>(remain, '\n', &remain);
            remain = course.fromString(remain);
            ScientificSubdivision::courses.insert({key, course});
        }

        return remain;
    }

};