#include "Model/EducationalSubdivisionModel.h"

std::string EducationalSubdivisionModel::toString() const
{
    // Получение строки от базовой модели и добавление проектов
    return (
        BaseSubdivisionModel::toString() + std::string("\n")
            + vectorToString(EducationalSubdivisionModel::projects, [](const ProjectModel &project) {
                return project.toString();
            })
    );
}

std::string EducationalSubdivisionModel::fromString(const std::string &string)
{
    // Считывание из строки информации для базовой модели подразделения
    std::string remain = BaseSubdivisionModel::fromString(string);      ///< Остаток строки
    EducationalSubdivisionModel::projects.clear();

    size_t projectsAmount;                                              ///< Количество проектов
    std::tie(projectsAmount) = splitString<size_t>(remain, '\n', &remain);
    // Получение проектов
    for (size_t i = 0; i < projectsAmount; i++) {
        ProjectModel project("", 0);
        remain = project.fromString(remain);
        EducationalSubdivisionModel::projects.emplace_back(project);
    }

    return remain;
}
