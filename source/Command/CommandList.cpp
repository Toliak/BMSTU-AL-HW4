#include <iomanip>
#include <filesystem>

#include "Command.h"

REGISTER_COMMAND(list)
{
    std::ostream &stream = Interaction::getInstance().getConsole().getOstream();

    if (!Interaction::getInstance().getCurrentDatabase()) {
        stream << "Loaded: " << std::endl;
        const auto &data = Interaction::getInstance().getData();
        for (const auto &it : data) {
            stream << "\t" << it.first << std::endl;
        }

        stream << "Unloaded: " << std::endl;

        if (std::filesystem::exists("db")) {
            for (const auto &it : std::filesystem::directory_iterator("db")) {
                std::string stem = it.path().filename().stem().string();
                if (data.find(stem) == data.cend()) {
                    stream << "\t" << stem << std::endl;
                }
            }
        }
    } else {
        std::string flag;
        bool fullInfo = false;

        try {
            std::tie(flag) = splitString<std::string>(string, ' ');
        } catch (Exception &) {

        }

        if (!flag.empty() && *flag.cbegin() == '-') {
            if (flag.find('A') != std::string::npos) {
                fullInfo = true;
            }
        }

        HybridDatabase &db = *Interaction::getInstance().getCurrentDatabase();
        for (auto it = db.cbegin(); it != db.cend(); it++) {
            BaseSubdivisionModel &subdivision = **it;
            std::string modelType = subdivision.getModelName();
            stream << "ID              : " << it - db.cbegin() << std::endl
                   << "Type            : " << modelType[0] << std::endl
                   << "Name            : " << subdivision.getName() << std::endl
                   << "Director        : " << subdivision.getDirector() << std::endl
                   << "Graduates amount: " << subdivision.getGraduateAmount() << std::endl
                   << "Employees amount: " << subdivision.getEmployeeAmount() << std::endl;

            if (fullInfo) {
                if (modelType == "EducationalSubdivisionModel") {
                    auto &model = dynamic_cast<EducationalSubdivisionModel &>(subdivision);
                    stream << "Projects        :" << std::endl;
                    for (const auto &project : model.getProjects()) {
                        stream << "\tName : " << project.getName() << std::endl
                               << "\tPrice: " << project.getPrice() << std::endl;
                    }
                } else if (modelType == "ScientificSubdivisionModel") {
                    auto &model = dynamic_cast<ScientificSubdivisionModel &>(subdivision);
                    stream << "Courses         :" << std::endl;
                    for (const auto &course : model.getCourses()) {
                        stream << "\tCourse ID      : " << course.first << std::endl
                               << "\tStudents amount: " << course.second.getStudentAmount() << std::endl
                               << "\tPrice          : " << course.second.getPrice() << std::endl;
                    }
                } else {
                    stream << "Unknown model" << std::endl;
                }
            }

            stream << std::endl;
        }
    }
}