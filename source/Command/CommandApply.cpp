#include <iomanip>

#include "Command.h"
#include "Interaction.h"

REGISTER_COMMAND(apply)
{
    std::ostream &stream = Interaction::getInstance().getConsole().getOstream();    ///< Поток вывода

    // Проверка на нахождение внутри БД
    if (!Interaction::getInstance().getCurrentDatabase()) {
        stream << "You are not in database" << std::endl;
        return;
    }

    size_t algorithmIndex;                                                  ///< Номер алгоритма
    std::string remain;                                                     ///< Остаточная строка
    std::tie(algorithmIndex) = splitString<size_t>(string, ' ', &remain);   // Разбиение строки

    HybridDatabase &db = *Interaction::getInstance().getCurrentDatabase();  ///< Текущая БД
    if (algorithmIndex == 0) {
        stream << " ID  | Amount " << std::endl;

        // Получение количества студентов для каждой модели
        for (auto it = db.cbegin(); it != db.cend(); it++) {
            // *it: BaseSubdivisionModel*
            BaseSubdivisionModel &subdivision = **it;                       ///< Подразделение
            stream << std::setw(4) << it - db.cbegin() << " | "
                   << std::setw(7) << subdivision.getStudentsAmount()
                   << std::endl;
        }
    } else if (algorithmIndex == 1) {
        stream << "Search for director: " << remain << std::endl;

        // Сравнение каждого директора
        for (auto it = db.cbegin(); it != db.cend(); it++) {
            size_t index = it - db.cbegin();                ///< Индекс
            BaseSubdivisionModel &model = **it;
            if (model.getDirector() == remain) {
                stream << "\tID: " << index << std::endl;
            }
        }
    } else if (algorithmIndex == 2) {
        // Лексикографическая сортировка
        std::sort(
            db.begin(),
            db.end(),
            [](BaseSubdivisionModel *leftModel, BaseSubdivisionModel *rightModel) {
                return leftModel->getName() < rightModel->getName();
            }
        );
        stream << "Sort complete" << std::endl;
    } else if (algorithmIndex == 3) {
        // Сортировка по возрастанию
        std::sort(
            db.begin(),
            db.end(),
            [](BaseSubdivisionModel *leftModel, BaseSubdivisionModel *rightModel) {
                return leftModel->getEmployeeAmount() < rightModel->getEmployeeAmount();
            }
        );
        stream << "Sort complete" << std::endl;
    } else if (algorithmIndex == 4) {
        size_t maxStudents;                     ///< Максимальное число стундентов
        std::tie(maxStudents) = splitString<size_t>(remain, ' ', &remain);      // Получение из остаточной строки

        // Для каждого объекта модели проверка условия
        for (auto it = db.cbegin(); it != db.cend(); it++) {
            size_t index = it - db.cbegin();
            BaseSubdivisionModel &model = **it;
            if (model.getStudentsAmount() <= maxStudents) {
                stream << "\tID: " << index << std::endl;
            }
        }

        //TODO: сохранять
    } else if (algorithmIndex == 5) {
        size_t maxEmployees;                                    ///< Максимальное число сотрудников
        std::tie(maxEmployees) = splitString<size_t>(remain, ' ', &remain);

        // Проверка условия для каждого объекта модели
        for (auto it = db.cbegin(); it != db.cend(); it++) {
            size_t index = it - db.cbegin();
            BaseSubdivisionModel &model = **it;
            if (model.getEmployeeAmount() > maxEmployees) {
                stream << "\tID: " << index << std::endl;
            }
        }
    } else {
        stream << "Wrong algorithm ID" << std::endl;
        return;
    }
}