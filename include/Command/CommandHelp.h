#include "Command.h"
#include "Interaction.h"

REGISTER_COMMAND(help)
{
    std::ostream &stream = Interaction::getInstance().getConsole().getOstream();

    stream << "General commands:" << std::endl;
    stream << "\thelp - to get available commands" << std::endl;
    stream << "\tload [name] - to load database from file" << std::endl;
    stream << "\tsave - to save database to file" << std::endl;
    stream << "\texit - to exit" << std::endl;

    stream << "Database commands:" << std::endl;
    stream << "\tlist - to get list of loaded databases" << std::endl;
    stream << "\tcreate [DB name] - to create empty database" << std::endl;
    stream << "\tgo [DB name] - to go into database" << std::endl;
    stream << "\tleave - to leave database" << std::endl;

    stream << "Models commands:" << std::endl;
    stream << "\t?list - get list of models in database" << std::endl;
    stream << "\tcreate [entity type] - to create entity" << std::endl;
    stream << "\t\tS - scientific subdivision" << std::endl;
    stream << "\t\tE - educational subdivision" << std::endl;
    stream << "\tremove [ID] - to remove entity" << std::endl;
    stream << "\t?apply [algorithm ID] - to apply predefined algorithm" << std::endl;
    stream << "\t\t 0 - to count amount of students for every subdivision" << std::endl;
    stream << "\t\t 1 [Director] - to find subdivision by director" << std::endl;
    stream << "\t\t 2 - to sort subdivisions by name" << std::endl;
    stream << "\t\t 3 - to sort subdivisions by employees amount" << std::endl;
    stream << "\t\t 4 [N] - to get subdivisions where student amount is less or equal N" << std::endl;
    stream << "\t\t 5 [N] - to get subdivisions where employee amount is greater N" << std::endl;
}