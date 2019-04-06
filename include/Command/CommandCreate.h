#pragma once

#include <tuple>

#include "Command.h"

REGISTER_COMMAND(create)
{
    Console &console = Interaction::getInstance().getConsole();
    std::ostream &stream = console.getOstream();
    if (!Interaction::getInstance().getCurrentDatabase()) {
        std::string dbName;
        std::tie(dbName) = splitString<std::string>(string, ' ');

        auto &data = Interaction::getInstance().getData();

        if (dbName.size() > 50) {
            stream << "Database name size is above 50" << std::endl;
            return;
        } else if (data.find(dbName) != data.cend()) {
            stream << "Database with the same name already exists" << std::endl;
            return;
        }

        data.insert({dbName, std::move(HybridDatabase(dbName))});
    } else {
        std::string modelType;
        std::tie(modelType) = splitString<std::string>(string, ' ');
        if (!(modelType == "E" || modelType == "S")) {
            stream << "Unexpected model type" << std::endl;
            return;
        }

        HybridDatabase &db = *Interaction::getInstance().getCurrentDatabase();

        BaseSubdivision *subdivision;
        std::tuple<
            std::string,
            std::string,
            decltype(std::declval<BaseSubdivision>().getGraduateAmount()),
            decltype(std::declval<BaseSubdivision>().getEmployeeAmount())
        > baseInfo = {
            console.pureInput<std::string>("Name: "),
            console.pureInput<std::string>("Director: "),
            console.pureInput<decltype(std::declval<BaseSubdivision>().getGraduateAmount())>(
                "Graduate amount: "
            ),
            console.pureInput<decltype(std::declval<BaseSubdivision>().getEmployeeAmount())>(
                "Employee amount: "
            )
        };


        if (modelType == "E") {
            auto *educationalSubdivision = new EducationalSubdivision(
                std::get<0>(baseInfo),
                std::get<1>(baseInfo),
                std::get<2>(baseInfo),
                std::get<3>(baseInfo)
            );

            auto projectAmount = console.pureInput<size_t>("Project amount: ");
            for (size_t i = 0; i < projectAmount; i++) {
                Project project(
                    console.pureInput<std::string>("\tName: "),
                    console.pureInput<decltype(std::declval<Project>().getPrice())>("\tPrice: ")
                );

                educationalSubdivision->getProjects().emplace_back(std::move(project));
            }
            subdivision = educationalSubdivision;
        } else {
            auto *scientificSubdivision = new ScientificSubdivision(
                std::get<0>(baseInfo),
                std::get<1>(baseInfo),
                std::get<2>(baseInfo),
                std::get<3>(baseInfo)
            );

            auto coursesAmount = console.pureInput<size_t>("Course amount: ");
            for (size_t i = 0; i < coursesAmount; i++) {
                using CourseMap = std::remove_reference<
                    decltype(std::declval<ScientificSubdivision>().getCourses())
                >::type;

                auto courseKey = console.pureInput<CourseMap::key_type>("\tCourse: ");
                Course course(
                    console.pureInput<
                        decltype(std::declval<Course>().getStudentAmount())
                    >("\tStudent amount: "),
                    console.pureInput<decltype(std::declval<Course>().getPrice())>("\tPrice: ")
                );

                scientificSubdivision->getCourses().insert({courseKey, std::move(course)});
            }
            subdivision = scientificSubdivision;
        }
        db.emplace_back(subdivision);
    }
}