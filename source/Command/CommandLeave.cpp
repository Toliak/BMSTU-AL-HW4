#include "Command.h"

REGISTER_COMMAND(leave)
{
    if (!Interaction::getInstance().getCurrentDatabase()) {
        return;
    }

    Interaction::getInstance().setCurrentDatabase(nullptr);
    std::list<std::string> &prefixes = Interaction::getInstance().getConsole().getPrefixes();
    prefixes.pop_back();
}