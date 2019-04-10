#include "Command.h"

REGISTER_COMMAND(load)
{
    std::string dbName;
    std::tie(dbName) = splitString<std::string>(string, ' ');

    std::ifstream inputFile;
    inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    inputFile.open("db/" + dbName + ".txt");

    std::string wholeFile(
        (std::istreambuf_iterator<char>(inputFile)),
        std::istreambuf_iterator<char>()
    );

    HybridDatabase db("");
    db.fromString(wholeFile);
    Interaction::getInstance().getData().insert({dbName, std::move(db)});

    std::ostream &stream = Interaction::getInstance().getConsole().getOstream();
    stream << "File has been loaded" << std::endl;
}