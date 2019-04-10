#include "Command.h"

REGISTER_COMMAND(save)
{
    std::ostream &stream = Interaction::getInstance().getConsole().getOstream();
    if (!Interaction::getInstance().getCurrentDatabase()) {
        stream << "You are not in database" << std::endl;
        return;
    }

    const HybridDatabase &database = *Interaction::getInstance().getCurrentDatabase();

    std::ofstream outputFile("db/" + database.getName() + ".txt");
    outputFile << database.toString() << std::endl;

    stream << "File has been saved" << std::endl;
}
