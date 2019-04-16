#include <iomanip>

#include "Command.h"
#include "Interaction.h"

/**
 * @brief Применение выборки
 * @param db БД
 * @param stream Поток вывода
 * @param remain Остаток строки
 * @param compare Функция сравнения
*/
void applySelect(
    const std::string remain,
    const std::function<bool(const BaseSubdivisionModel &)> &compare)
{
    std::ostream &stream = Interaction::getInstance().getConsole().getOstream();    ///< Поток вывода
    HybridDatabase &db = *Interaction::getInstance().getCurrentDatabase();      ///< Текущая БД
    std::vector<size_t> indexes;                ///< Правильные индексы
   
    // Прохождение по БД
    for (auto it = db.cbegin(); it != db.cend(); it++) {
        size_t index = it - db.cbegin();        ///< Индекс
        if (compare(**it)) {
            stream << "\tID: " << index << std::endl;
            indexes.push_back(index);
        }
    }
    
    // Попытка создать новую БД
    std::string dbName;                         ///< Название БД
    try {
        std::tie(dbName) = splitString<std::string>(remain);
    } catch (SplitShortcutException &) {
        // Значит не требуется создание новой БД
    }

    // Если есть название => необходимо создать БД с выборкой
    if (!dbName.empty()) {
        auto &databases = Interaction::getInstance().getData();
        if (databases.find(dbName) != databases.cend()) {
            stream << "Database with this name already exists" << std::endl;
            return;
        }

        HybridDatabase createdDb(dbName);                   ///< БД с выборкой

        for (auto index : indexes) {
            createdDb.push_back(db[index]);
        }
        databases.insert({ dbName, std::move(createdDb) });

        stream << "Selection saved to " << dbName << std::endl;
        stream << "Database IS NOT saved to file" << std::endl;
    }
    
}

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

        applySelect(
            remain,
            [maxStudents](const BaseSubdivisionModel &model)
            {
                return model.getStudentsAmount() <= maxStudents;
            }
        );
    } else if (algorithmIndex == 5) {
        size_t maxEmployees;                                    ///< Максимальное число сотрудников
        std::tie(maxEmployees) = splitString<size_t>(remain, ' ', &remain);

        applySelect(
            remain,
            [maxEmployees](const BaseSubdivisionModel &model)
            {
                return model.getEmployeeAmount() > maxEmployees;
            }
        );
    } else {
        stream << "Wrong algorithm ID" << std::endl;
        return;
    }
}