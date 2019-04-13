#include "Command.h"

REGISTER_COMMAND(load)
{
    std::ostream &stream = Interaction::getInstance().getConsole().getOstream();
    std::string dbName;
    std::tie(dbName) = splitString<std::string>(string, ' ');

    std::ifstream inputFile;
    inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        inputFile.open("db/" + dbName + ".txt");
    } catch (std::ifstream::failure &e) {
        stream << "Error opening file" << std::endl;
        return;
    }

    std::string wholeFile(
        (std::istreambuf_iterator<char>(inputFile)),
        std::istreambuf_iterator<char>()
    );

    HybridDatabase db("");
    db.fromString(wholeFile);
    Interaction::getInstance().getData().insert({dbName, std::move(db)});


    stream << "File has been loaded" << std::endl;
}