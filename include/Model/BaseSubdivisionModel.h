#pragma once

#include "Model.h"

class BaseSubdivisionModel: virtual public Model
{
protected:
    std::string name;
    std::string director;
    size_t graduateAmount = 0;
    size_t employeeAmount = 0;

public:
    BaseSubdivisionModel(const std::string &name,
                         const std::string &director,
                         decltype(BaseSubdivisionModel::graduateAmount) graduateAmount,
                         decltype(BaseSubdivisionModel::employeeAmount) employeeAmount);

    void setName(const std::string &subdivisionName)
    {
        if (subdivisionName.size() > 50) {
            throw BaseSubdivisionModelException("BaseSubdivisionModel: Name size must be below 50");
        }
        BaseSubdivisionModel::name = subdivisionName;
    }
    void setDirector(const std::string &subdivisionDirector)
    {
        if (director.size() > 50) {
            throw BaseSubdivisionModelException("BaseSubdivisionModel: Director size must be below 50");
        }
        BaseSubdivisionModel::director = subdivisionDirector;
    }
    void setGraduateAmount(decltype(BaseSubdivisionModel::graduateAmount) subdivisionGraduateAmount)
    {
        if (subdivisionGraduateAmount > 1000000) {
            throw BaseSubdivisionModelException("BaseSubdivisionModel: Graduate amount must be below 1000000");
        }
        BaseSubdivisionModel::graduateAmount = subdivisionGraduateAmount;
    }
    void setEmployeeAmount(decltype(BaseSubdivisionModel::employeeAmount) subdivisionEmployeeAmount)
    {
        if (subdivisionEmployeeAmount > 1000000) {
            throw BaseSubdivisionModelException("BaseSubdivisionModel: Graduate amount must be below 1000000");
        }
        BaseSubdivisionModel::employeeAmount = subdivisionEmployeeAmount;
    }

    const std::string &getName() const
    {
        return BaseSubdivisionModel::name;
    }

    const std::string &getDirector() const
    {
        return BaseSubdivisionModel::director;
    }

    decltype(BaseSubdivisionModel::graduateAmount) getGraduateAmount() const
    {
        return BaseSubdivisionModel::graduateAmount;
    }

    decltype(BaseSubdivisionModel::employeeAmount) getEmployeeAmount() const
    {
        return BaseSubdivisionModel::employeeAmount;
    }

    std::string toString() const override;

    std::string fromString(const std::string &string) override;

    virtual decltype(BaseSubdivisionModel::graduateAmount) getStudentsAmount() const noexcept = 0;
};
