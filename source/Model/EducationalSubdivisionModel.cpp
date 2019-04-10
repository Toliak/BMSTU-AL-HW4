#include "Model/EducationalSubdivisionModel.h"

std::string EducationalSubdivisionModel::toString() const
{
    return (
        BaseSubdivisionModel::toString() + std::string("\n")
            + vectorToString(EducationalSubdivisionModel::projects, [](const ProjectModel &project) {
                return project.toString();
            })
    );
}

std::string EducationalSubdivisionModel::fromString(const std::string &string)
{
    std::string remain = BaseSubdivisionModel::fromString(string);
    EducationalSubdivisionModel::projects.clear();

    size_t projectsAmount;
    std::tie(projectsAmount) = splitString<size_t>(remain, '\n', &remain);
    for (size_t i = 0; i < projectsAmount; i++) {
        ProjectModel project("", 0);
        remain = project.fromString(remain);
        EducationalSubdivisionModel::projects.emplace_back(project);
    }

    return remain;
}
