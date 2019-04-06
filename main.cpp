#include <iostream>
#include <functional>
#include <iomanip>

#include "Console.h"
#include "Database.h"
#include "Interaction.h"

/*
struct MainInteraction
{
    Console console;
    std::unordered_map<std::string, HybridDatabase> data = {};
    HybridDatabase *currentDatabase = nullptr;
};
*/

/*

void executeCommand(const std::pair<std::string, std::string> &pair)
{




static std::unordered_map<std::string, std::function<void(MainInteraction &, const std::string &)>> commands = {
        {
            "help",
            [](MainInteraction &interaction, const std::string &) {
                executeCommand(interaction, {"?", ""});
            }
        },
        {
            "?",
            [](MainInteraction &interaction, const std::string &) {
                std::ostream &stream = interaction.console.getOstream();

                stream << "General commands:" << std::endl;
                stream << "\t?, help - to get available commands" << std::endl;
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
        },
        {
            "save",
            [](MainInteraction &interaction, const std::string &) {
                std::ostream &stream = interaction.console.getOstream();
                if (!interaction.currentDatabase) {
                    stream << "You are not in database" << std::endl;
                    return;
                }

                std::ofstream outputFile(interaction.currentDatabase->getName());
                outputFile << interaction.currentDatabase->toString() << std::endl;

                stream << "File has been saved" << std::endl;
            }
        },
        {
            "load",
            [](MainInteraction &interaction, const std::string &string) {
                std::string dbName;
                std::tie(dbName) = splitString<std::string>(string, ' ');

                std::ifstream inputFile;
                inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
                inputFile.open(dbName);

                std::string wholeFile(
                    (std::istreambuf_iterator<char>(inputFile)),
                    std::istreambuf_iterator<char>()
                );

                HybridDatabase db("");
                db.fromString(wholeFile);
                interaction.data.insert({dbName, std::move(db)});

                std::ostream &stream = interaction.console.getOstream();
                stream << "File has been loaded" << std::endl;
            }
        },
        {
            "create",
            [](MainInteraction &interaction, const std::string &string) {
                Console &console = interaction.console;
                std::ostream &stream = console.getOstream();
                if (!interaction.currentDatabase) {
                    std::string dbName;
                    std::tie(dbName) = splitString<std::string>(string, ' ');

                    if (dbName.size() > 50) {
                        stream << "Database name size is above 50" << std::endl;
                        return;
                    } else if (interaction.data.find(dbName) != interaction.data.cend()) {
                        stream << "Database with the same name already exists" << std::endl;
                        return;
                    }

                    interaction.data.insert({dbName, std::move(HybridDatabase(dbName))});
                } else {
                    std::string modelType;
                    std::tie(modelType) = splitString<std::string>(string, ' ');
                    if (!(modelType == "E" || modelType == "S")) {
                        stream << "Unexpected model type" << std::endl;
                        return;
                    }

                    HybridDatabase &db = *interaction.currentDatabase;

                    BaseSubdivisionModel *subdivision;
                    std::tuple<
                        std::string,
                        std::string,
                        decltype(std::declval<BaseSubdivisionModel>().getGraduateAmount()),
                        decltype(std::declval<BaseSubdivisionModel>().getEmployeeAmount())
                    > baseInfo = {
                        console.pureInput<std::string>("Name: "),
                        console.pureInput<std::string>("Director: "),
                        console.pureInput<decltype(std::declval<BaseSubdivisionModel>().getGraduateAmount())>(
                            "Graduate amount: "
                        ),
                        console.pureInput<decltype(std::declval<BaseSubdivisionModel>().getEmployeeAmount())>(
                            "Employee amount: "
                        )
                    };

                    if (modelType == "E") {
                        auto *educationalSubdivision = new EducationalSubdivisionModel(
                            std::get<0>(baseInfo),
                            std::get<1>(baseInfo),
                            std::get<2>(baseInfo),
                            std::get<3>(baseInfo)
                        );

                        auto projectAmount = console.pureInput<size_t>("ProjectModel amount: ");
                        for (size_t i = 0; i < projectAmount; i++) {
                            ProjectModel project(
                                console.pureInput<std::string>("\tName: "),
                                console.pureInput<decltype(std::declval<ProjectModel>().getPrice())>("\tPrice: ")
                            );

                            educationalSubdivision->getProjects().emplace_back(std::move(project));
                        }
                        subdivision = educationalSubdivision;
                    } else {
                        auto *scientificSubdivision = new ScientificSubdivisionModel(
                            std::get<0>(baseInfo),
                            std::get<1>(baseInfo),
                            std::get<2>(baseInfo),
                            std::get<3>(baseInfo)
                        );

                        auto coursesAmount = console.pureInput<size_t>("CourseModel amount: ");
                        for (size_t i = 0; i < coursesAmount; i++) {
                            using CourseMap = std::remove_reference<
                                decltype(std::declval<ScientificSubdivisionModel>().getCourses())
                            >::type;

                            auto courseKey = console.pureInput<CourseMap::key_type>("\tCourseModel: ");
                            CourseModel course(
                                console.pureInput<
                                    decltype(std::declval<CourseModel>().getStudentAmount())
                                >("\tStudent amount: "),
                                console.pureInput<decltype(std::declval<CourseModel>().getPrice())>("\tPrice: ")
                            );

                            scientificSubdivision->getCourses().insert({courseKey, std::move(course)});
                        }
                        subdivision = scientificSubdivision;
                    }
                    db.emplace_back(subdivision);
                }
            }
        },
        {
            "remove",
            [](MainInteraction &interaction, const std::string &string) {
                std::ostream &stream = interaction.console.getOstream();
                if (!interaction.currentDatabase) {
                    stream << "You are not in database" << std::endl;
                    return;
                }

                size_t index;
                std::tie(index) = splitString<size_t>(string, ' ');

                HybridDatabase &db = *interaction.currentDatabase;
                if (index >= db.size()) {
                    stream << "Index is out of range" << std::endl;
                    return;
                }

                db.erase(db.cbegin() + index);
                stream << "Item removed" << std::endl;
            }
        },
        {
            "apply",
            [](MainInteraction &interaction, const std::string &string) {
                std::ostream &stream = interaction.console.getOstream();
                if (!interaction.currentDatabase) {
                    stream << "You are not in database" << std::endl;
                    return;
                }

                size_t index;
                std::tie(index) = splitString<size_t>(string, ' ');
                if (index > 5) {
                    stream << "Wrong algorithm ID" << std::endl;
                    return;
                }

                HybridDatabase &db = *interaction.currentDatabase;
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
        },
        {
            "list",
            [](MainInteraction &interaction, const std::string &string) {
                std::ostream &stream = interaction.console.getOstream();

                if (!interaction.currentDatabase) {
                    for (const auto &it : interaction.data) {
                        stream << it.first << std::endl;
                    }
                } else {
                    HybridDatabase &db = *interaction.currentDatabase;
                    for (auto it = db.cbegin(); it != db.cend(); it++) {
                        BaseSubdivisionModel &subdivision = **it;
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
        },
        {
            "go",
            [](MainInteraction &interaction, const std::string &string) {
                std::ostream &stream = interaction.console.getOstream();
                if (interaction.currentDatabase) {
                    stream << "Leave current database before entering to another" << std::endl;
                    return;
                }

                std::string dbName;
                std::tie(dbName) = splitString<std::string>(string, ' ');

                auto it = interaction.data.find(dbName);
                if (it == interaction.data.cend()) {
                    stream << "Database with given name does not exist" << std::endl;
                    return;
                }

                interaction.currentDatabase = &it->second;
                interaction.console.getPrefixes().emplace_back(dbName);
            }
        },
        {
            "leave",
            [](MainInteraction &interaction, const std::string &string) {
                if (!interaction.currentDatabase) {
                    return;
                }

                interaction.currentDatabase = nullptr;
                std::list<std::string> &prefixes = interaction.console.getPrefixes();
                prefixes.pop_back();
            }
        }
    };


    auto &interaction = Interaction::getInstance();

    auto iterator = interaction.getCommands().find(pair.first);
    if (iterator == interaction.getCommands().cend()) {
        interaction.getConsole().getOstream() << "Command '" << pair.first << "' not found" << std::endl;
        return;
    }

    return iterator->second->execute(pair.second);
}
*/

void test()
{
    ProjectModel p("", 0);
    p.fromString("asdasdasdasdpa posdpa ojspfoaj sofapofj \n5252");

    std::string remain;
    auto result0 = splitString<int, std::string>("3\nasdasd asd asd\nasdasda sdas d\n5.6\n686", '\n');
    auto result1 = splitString<int, std::string>("3\nasdasd asd asd", '\n', &remain);

    EducationalSubdivisionModel es("", "", 1, 1);

    std::string result2 = es.fromString("Test tested\nThe big director\n14\n500\n2\nasd\n4\nHEH\n600\ndfgdfg");

    ScientificSubdivisionModel ss("", "", 1, 1);

    std::string result3 = ss.fromString("Test tested\nThe big director\n14\n500\n2\n1\n14\n400\n4\n70\n600\ndfg dfg");

    HybridDatabase db("");
    db.fromString("test\n"
                  "1\n"
                  "EducationalSubdivisionModel\n"
                  "ASDadasd\n"
                  "ASdaSdadsasda\n"
                  "1312\n"
                  "13123\n"
                  "1\n"
                  "Projecascasdas\n"
                  "555"
    );

    std::vector<BaseSubdivisionModel *> &v = db;

    std::cout << es.toString() << std::endl;
    std::cout << ss.toString() << std::endl;
}

int main()
{
    test();

    auto &interaction = Interaction::getInstance();

    interaction.getConsole() = std::move(Console(std::cin, std::cout));
    Console &console = interaction.getConsole();
    console.start();

    std::string command;
    while ((command = console.getLine()) != "exit") {
        try {
            interaction.executeCommand(Console::divideCommand(command));
        } catch (Exception &e) {
            std::cout << e.what() << std::endl;
        }
    }

    std::cout << "Bye" << std::endl;
    return 0;
}