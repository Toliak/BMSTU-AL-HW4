#include "Model/BaseSubdivisionModel.h"

BaseSubdivisionModel::BaseSubdivisionModel(const std::string &name,
                                           const std::string &director,
                                           decltype(BaseSubdivisionModel::graduateAmount) graduateAmount,
                                           decltype(BaseSubdivisionModel::employeeAmount) employeeAmount)
{
    BaseSubdivisionModel::setName(name);
    BaseSubdivisionModel::setDirector(director);
    BaseSubdivisionModel::setGraduateAmount(graduateAmount);
    BaseSubdivisionModel::setEmployeeAmount(employeeAmount);
}

std::string BaseSubdivisionModel::toString() const
{
    return (
        BaseSubdivisionModel::name + std::string("\n")
            + BaseSubdivisionModel::director + std::string("\n")
            + std::to_string(BaseSubdivisionModel::graduateAmount) + std::string("\n")
            + std::to_string(BaseSubdivisionModel::employeeAmount)
    );
}

std::string BaseSubdivisionModel::fromString(const std::string &string)
{
    std::string remain;

    std::tie(
        BaseSubdivisionModel::name,
        BaseSubdivisionModel::director,
        BaseSubdivisionModel::graduateAmount,
        BaseSubdivisionModel::employeeAmount
    ) = splitString<
        decltype(BaseSubdivisionModel::name),
        decltype(BaseSubdivisionModel::director),
        decltype(BaseSubdivisionModel::graduateAmount),
        decltype(BaseSubdivisionModel::employeeAmount)
    >(string, '\n', &remain);

    return remain;
}
