#pragma once

#include "Model.h"
#include "ProjectModel.h"
#include "BaseSubdivisionModel.h"

class EducationalSubdivisionModel final: virtual public BaseSubdivisionModel
{
private:
    std::vector<ProjectModel> projects;

public:
    EducationalSubdivisionModel(const std::string &name,
                           const std::string &director,
                           decltype(std::declval<BaseSubdivisionModel>().getGraduateAmount()) graduateAmount,
                           decltype(std::declval<BaseSubdivisionModel>().getEmployeeAmount()) employeeAmount,
                           std::vector<ProjectModel> projects = {})
        : BaseSubdivisionModel(name, director, graduateAmount, employeeAmount), projects(std::move(projects))
    {}

    decltype(std::declval<BaseSubdivisionModel>().getGraduateAmount()) getStudentsAmount() const noexcept override
    {
        return BaseSubdivisionModel::graduateAmount;
    }

    std::vector<ProjectModel> &getProjects()
    {
        return EducationalSubdivisionModel::projects;
    }

    std::string getModelName() const noexcept override
    {
        return "EducationalSubdivisionModel";
    }

    std::string toString() const override;

    std::string fromString(const std::string &string) override;
};