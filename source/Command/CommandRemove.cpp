#include "Command.h"

REGISTER_COMMAND(remove)
{
    std::ostream &stream = Interaction::getInstance().getConsole().getOstream();
    HybridDatabase *db = Interaction::getInstance().getCurrentDatabase();
    if (!db) {
        stream << "You are not in database" << std::endl;
        return;
    }

    size_t index;
    std::tie(index) = splitString<size_t>(string, ' ');

    if (index >= db->size()) {
        stream << "Index is out of range" << std::endl;
        return;
    }

    db->erase(db->cbegin() + index);
    stream << "Item removed" << std::endl;
}
