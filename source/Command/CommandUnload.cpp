#include "Command.h"

REGISTER_COMMAND(unload)
{
    std::ostream &stream = Interaction::getInstance().getConsole().getOstream();
    if (!Interaction::getInstance().getCurrentDatabase()) {
        stream << "You are not in database" << std::endl;
        return;
    }

    const HybridDatabase &database = *Interaction::getInstance().getCurrentDatabase();
    auto &data = Interaction::getInstance().getData();

    data.erase(database.getName());
    Interaction::getInstance().setCurrentDatabase(nullptr);
    Interaction::getInstance().getConsole().getPrefixes().clear();

    stream << "Database has been unloaded" << std::endl;
}