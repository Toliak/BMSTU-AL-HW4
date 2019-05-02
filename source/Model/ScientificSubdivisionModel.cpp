#include "Model/ScientificSubdivisionModel.h"

decltype(std::declval<BaseSubdivisionModel>().getGraduateAmount())
ScientificSubdivisionModel::getStudentsAmount() const noexcept
{
    decltype(std::declval<BaseSubdivisionModel>().getGraduateAmount())
        returnValue = BaseSubdivisionModel::graduateAmount;

    // Сложение студентов со всех курсов
    for (const auto &it : ScientificSubdivisionModel::courses) {
        returnValue += it.second.getStudentAmount();
    }

    return returnValue;
}

std::string ScientificSubdivisionModel::toString() const
{
    std::string coursesString = std::to_string(ScientificSubdivisionModel::courses.size());
    ///< Строка, содержащая информацию о курсах

    // Не дописываем перенос строки, если словарь пустой
    if (!ScientificSubdivisionModel::courses.empty()) {
        coursesString += "\n";
    }

    // Запись информации о курсах в строку
    for (const auto &course : ScientificSubdivisionModel::courses) {
        coursesString += std::to_string(course.first) + std::string("\n") + course.second.toString();
        coursesString += "\n";
    }
    coursesString = coursesString.substr(0, coursesString.size() - 1);      // Последний перенос строки лишний

    return (
        BaseSubdivisionModel::toString() + std::string("\n")
            + coursesString
    );
}

std::string ScientificSubdivisionModel::fromString(const std::string &string)
{
    // Считываание информации в базовую модель подразделения
    std::string remain = BaseSubdivisionModel::fromString(string);      ///< Остаток строки
    ScientificSubdivisionModel::courses.clear();                        // Очистка словаря курсов

    size_t coursesAmount;                                               ///< Количество курсов
    std::tie(coursesAmount) = splitString<size_t>(remain, '\n', &remain);

    // Считывание курсов из остатка строки
    for (size_t i = 0; i < coursesAmount; i++) {
        CourseModel course(0, 0);

        decltype(courses)::key_type key;                                    ///< Номер курса
        std::tie(key) = splitString<decltype(key)>(remain, '\n', &remain);

        remain = course.fromString(remain);                                 // Считывание информации в курс
        ScientificSubdivisionModel::courses.insert({key, std::move(course)});
    }

    return remain;
}
