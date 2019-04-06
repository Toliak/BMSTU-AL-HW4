cmake_minimum_required(VERSION 3.9)
project(BMSTU_HW_4)

set(CMAKE_CXX_STANDARD 17)

set(BMSTU_HW_4_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(
        BMSTU_HW_4_SOURCE_COMMAND
        source/Command/CommandHelp.cpp
        source/Command/CommandSave.cpp
        source/Command/CommandApply.cpp
        source/Command/CommandCreate.cpp
        source/Command/CommandGo.cpp
        source/Command/CommandLeave.cpp
        source/Command/CommandList.cpp
        source/Command/CommandLoad.cpp
        source/Command/CommandRemove.cpp
)

set(
        BMSTU_HW_4_SOURCE_MODEL
        source/Model/BaseSubdivisionModel.cpp
        source/Model/ProjectModel.cpp
        source/Model/CourseModel.cpp
        source/Model/EducationalSubdivisionModel.cpp
        source/Model/ScientificSubdivisionModel.cpp
)

set(
        BMSTU_HW_4_SOURCE
        ${BMSTU_HW_4_SOURCE_COMMAND}
        ${BMSTU_HW_4_SOURCE_MODEL}
        source/Console.cpp
        source/Interaction.cpp
        source/Database.cpp
        main.cpp
)

add_executable(BMSTU_HW_4 ${BMSTU_HW_4_SOURCE})

set(BMSTU_HW_4_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories(${BMSTU_HW_4_INCLUDE})

