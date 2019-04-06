#include "Command.h"

REGISTER_COMMAND(go)
{
    std::ostream &stream = Interaction::getInstance().getConsole().getOstream();
    if (Interaction::getInstance().getCurrentDatabase()) {
        stream << "Leave current database before entering to another" << std::endl;
        return;
    }

    std::string dbName;
    std::tie(dbName) = splitString<std::string>(string, ' ');

    auto it = Interaction::getInstance().getData().find(dbName);
    if (it == Interaction::getInstance().getData().cend()) {
        stream << "Database with given name does not exist" << std::endl;
        return;
    }

    Interaction::getInstance().setCurrentDatabase(&it->second);
    Interaction::getInstance().getConsole().getPrefixes().emplace_back(dbName);
}