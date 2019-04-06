cmake_minimum_required(VERSION 3.9)
project(BMSTU_HW_4)

set(CMAKE_CXX_STANDARD 14)

IF(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

add_executable(
        BMSTU_HW_4
        main.cpp
        source/Database.cpp
        source/Console.cpp
        include/Interaction.h
        include/Command/Command.h
        source/Interaction.cpp include/Command/CommandSave.h include/Command/CommandLoad.h include/Command/CommandCreate.h include/Command/CommandList.h include/Command/CommandRemove.h include/Command/CommandGo.h include/Command/CommandLeave.h include/Command/CommandApply.h)

set(BMSTU_HW_4_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories(${BMSTU_HW_4_INCLUDE})

