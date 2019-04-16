#pragma once

#include <unordered_map>

#include "CourseModel.h"
#include "BaseSubdivisionModel.h"

class ScientificSubdivisionModel final: virtual public BaseSubdivisionModel
{
private:
    std::unordered_map<size_t, CourseModel> courses = {};

public:
    ScientificSubdivisionModel(const std::string &name,
                               const std::string &director,
                               decltype(std::declval<BaseSubdivisionModel>().getGraduateAmount()) graduateAmount,
                               decltype(std::declval<BaseSubdivisionModel>().getEmployeeAmount()) employeeAmount,
                               decltype(ScientificSubdivisionModel::courses) courses = {})
        : BaseSubdivisionModel(name, director, graduateAmount, employeeAmount), courses(std::move(courses))
    {}

    decltype(std::declval<BaseSubdivisionModel>().getGraduateAmount()) getStudentsAmount() const noexcept override;

    decltype(ScientificSubdivisionModel::courses) &getCourses()
    {
        return ScientificSubdivisionModel::courses;
    }

    std::string getModelName() const noexcept override
    {
        return "ScientificSubdivisionModel";
    }

    std::string toString() const override;

    std::string fromString(const std::string &string) override;

};
