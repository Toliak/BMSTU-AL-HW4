#include "Model/ScientificSubdivisionModel.h"

decltype(std::declval<BaseSubdivisionModel>().getGraduateAmount())
ScientificSubdivisionModel::getStudentsAmount() const noexcept
{
    decltype(std::declval<BaseSubdivisionModel>().getGraduateAmount()) returnValue = 0;
    for (const auto &it : ScientificSubdivisionModel::courses) {
        returnValue += it.second.getStudentAmount();
    }
    return BaseSubdivisionModel::graduateAmount + returnValue;
}

std::string ScientificSubdivisionModel::toString() const
{
    std::string coursesString = std::to_string(ScientificSubdivisionModel::courses.size()) + std::string("\n");
    for (const auto &course : ScientificSubdivisionModel::courses) {
        coursesString += std::to_string(course.first) + std::string("\n") + course.second.toString();
        coursesString += "\n";
    }
    coursesString = coursesString.substr(0, coursesString.size() - 1);

    return (
        BaseSubdivisionModel::toString() + std::string("\n")
            + coursesString
    );
}

std::string ScientificSubdivisionModel::fromString(const std::string &string)
{
    std::string remain = BaseSubdivisionModel::fromString(string);
    ScientificSubdivisionModel::courses.clear();

    size_t projectsAmount;
    std::tie(projectsAmount) = splitString<size_t>(remain, '\n', &remain);
    for (size_t i = 0; i < projectsAmount; i++) {
        CourseModel course(0, 0);
        decltype(courses)::key_type key;
        std::tie(key) = splitString<decltype(key)>(remain, '\n', &remain);
        remain = course.fromString(remain);
        ScientificSubdivisionModel::courses.insert({key, course});
    }

    return remain;
}
