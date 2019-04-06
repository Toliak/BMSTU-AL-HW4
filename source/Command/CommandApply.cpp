#include <iomanip>

#include "Command.h"

REGISTER_COMMAND(apply)
{
    std::ostream &stream = Interaction::getInstance().getConsole().getOstream();
    if (!Interaction::getInstance().getCurrentDatabase()) {
        stream << "You are not in database" << std::endl;
        return;
    }

    size_t index;
    std::tie(index) = splitString<size_t>(string, ' ');
    if (index > 5) {
        stream << "Wrong algorithm ID" << std::endl;
        return;
    }

    HybridDatabase &db = *Interaction::getInstance().getCurrentDatabase();
    switch (index) {
        case 1: {
            for (auto it = db.cbegin(); it != db.cend(); it++) {
                BaseSubdivisionModel &subdivision = **it;
                stream << std::setw(4) << it - db.cbegin() << " | "
                       << std::setw(7) << subdivision.getStudentsAmount()
                       << std::endl;
            }
            break;
        }
        default: {

        }
    }
}