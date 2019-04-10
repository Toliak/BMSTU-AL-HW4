#include "Model/ProjectModel.h"

ProjectModel::ProjectModel(std::string name, decltype(ProjectModel::price) price)
{
    ProjectModel::setName(std::move(name));
    ProjectModel::setPrice(price);
}

std::string ProjectModel::toString() const
{
    return (ProjectModel::name + std::string("\n") + std::to_string(ProjectModel::price));
}

std::string ProjectModel::fromString(const std::string &string)
{
    std::string remain;

    std::tie(
        ProjectModel::name,
        ProjectModel::price
    ) = splitString<
        decltype(ProjectModel::name),
        decltype(ProjectModel::price)
    >(string, '\n', &remain);

    return remain;
}
