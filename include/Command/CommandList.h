#pragma once

#include "Command.h"

REGISTER_COMMAND(list)
{
    std::ostream &stream = Interaction::getInstance().getConsole().getOstream();

    if (!Interaction::getInstance().getCurrentDatabase()) {
        for (const auto &it : Interaction::getInstance().getData()) {
            stream << it.first << std::endl;
        }
    } else {
        HybridDatabase &db = *Interaction::getInstance().getCurrentDatabase();
        for (auto it = db.cbegin(); it != db.cend(); it++) {
            BaseSubdivision &subdivision = **it;
            stream << std::setw(4) << it - db.cbegin() << " | "
                   << std::setw(1) << subdivision.getModelName()[0] << " | "
                   << std::setw(15) << subdivision.getName() << " | "
                   << std::setw(20) << subdivision.getDirector() << " | "
                   << std::setw(7) << subdivision.getGraduateAmount() << " | "
                   << std::setw(7) << subdivision.getEmployeeAmount()
                   << std::endl;
        }
    }
}