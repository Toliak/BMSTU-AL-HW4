#include "Model/CourseModel.h"

CourseModel::CourseModel(decltype(CourseModel::studentAmount) studentAmount, decltype(CourseModel::price) price)
{
    CourseModel::setStudentAmount(studentAmount);
    CourseModel::setPrice(price);
}

std::string CourseModel::toString() const
{
    return (
        std::to_string(CourseModel::studentAmount) + std::string("\n")
            + std::to_string(CourseModel::price)
    );
}

std::string CourseModel::fromString(const std::string &string)
{
    std::string remain;

    std::tie(
        CourseModel::studentAmount,
        CourseModel::price
    ) = splitString<
        decltype(CourseModel::studentAmount),
        decltype(CourseModel::price)
    >(string, '\n', &remain);

    return remain;
}
