cmake_minimum_required(VERSION 3.9)
project(BMSTU_HW_4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BMSTU_HW_4_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${BMSTU_HW_4_INCLUDE})


file(GLOB BMSTU_HW_4_SOURCE_COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/source/Command/*.cpp")

file(GLOB BMSTU_HW_4_SOURCE_MODEL "${CMAKE_CURRENT_SOURCE_DIR}/source/Model/*.cpp")

set(
        BMSTU_HW_4_SOURCE
        ${BMSTU_HW_4_SOURCE_COMMAND}
        ${BMSTU_HW_4_SOURCE_MODEL}
        source/Console.cpp
        source/Interaction.cpp
        source/Database.cpp
        main.cpp
)

find_package(Threads)

add_executable(BMSTU_HW_4 ${BMSTU_HW_4_SOURCE})

target_link_libraries(BMSTU_HW_4 ${CMAKE_THREAD_LIBS_INIT} )

find_library(FS_LIBRARY stdc++fs)

target_link_libraries(BMSTU_HW_4 ${FS_LIBRARY})
