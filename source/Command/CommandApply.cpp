#include <iomanip>

#include "Command.h"
#include "Interaction.h"

REGISTER_COMMAND(apply)
{
    std::ostream &stream = Interaction::getInstance().getConsole().getOstream();
    if (!Interaction::getInstance().getCurrentDatabase()) {
        stream << "You are not in database" << std::endl;
        return;
    }

    size_t algorithmIndex;
    std::string remain;
    std::tie(algorithmIndex) = splitString<size_t>(string, ' ', &remain);

    HybridDatabase &db = *Interaction::getInstance().getCurrentDatabase();
    if (algorithmIndex == 0) {
        stream << "Students amount: " << std::endl;
        for (auto it = db.cbegin(); it != db.cend(); it++) {
            BaseSubdivisionModel &subdivision = **it;
            stream << std::setw(4) << it - db.cbegin() << " | "
                   << std::setw(7) << subdivision.getStudentsAmount()
                   << std::endl;
        }
    } else if (algorithmIndex == 1) {
        stream << "Search for director: " << remain << std::endl;
        for (auto it = db.cbegin(); it != db.cend(); it++) {
            size_t index = it - db.cbegin();
            BaseSubdivisionModel &model = **it;
            if (model.getDirector() == remain) {
                stream << "\tID: " << index << std::endl;
            }
        }
    } else if (algorithmIndex == 2) {
        std::sort(
            db.begin(),
            db.end(),
            [](BaseSubdivisionModel *leftModel, BaseSubdivisionModel *rightModel) {
                return leftModel->getName() < rightModel->getName();
            }
        );
        stream << "Sort complete" << std::endl;
    } else if (algorithmIndex == 3) {
        std::sort(
            db.begin(),
            db.end(),
            [](BaseSubdivisionModel *leftModel, BaseSubdivisionModel *rightModel) {
                return leftModel->getEmployeeAmount() < rightModel->getEmployeeAmount();
            }
        );
        stream << "Sort complete" << std::endl;
    } else if (algorithmIndex == 4) {
        size_t maxStudents;
        std::tie(maxStudents) = splitString<size_t>(remain, ' ', &remain);

        for (auto it = db.cbegin(); it != db.cend(); it++) {
            size_t index = it - db.cbegin();
            BaseSubdivisionModel &model = **it;
            if (model.getStudentsAmount() <= maxStudents) {
                stream << "\tID: " << index << std::endl;
            }
        }

        //TODO: сохранять
    } else if (algorithmIndex == 5) {
        size_t maxEmployees;
        std::tie(maxEmployees) = splitString<size_t>(remain, ' ', &remain);

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