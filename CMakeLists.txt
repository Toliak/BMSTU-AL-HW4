cmake_minimum_required(VERSION 3.4)
project(BMSTU_HW_4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Library

set(BMSTU_HW_4_LIB_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${BMSTU_HW_4_LIB_INCLUDE})
file(GLOB BMSTU_HW_4_LIB_SOURCE_COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/source/Command/*.cpp")
file(GLOB BMSTU_HW_4_LIB_SOURCE_MODEL "${CMAKE_CURRENT_SOURCE_DIR}/source/Model/*.cpp")
set(
        BMSTU_HW_4_LIB_SOURCE
        ${BMSTU_HW_4_LIB_SOURCE_MODEL}
        source/Console.cpp
        source/Interaction.cpp
        source/Database.cpp
)

find_package(Threads)

add_library(BMSTU_HW_4_LIB ${BMSTU_HW_4_LIB_SOURCE})

target_link_libraries(BMSTU_HW_4_LIB ${CMAKE_THREAD_LIBS_INIT})

find_library(
        FS_LIBRARY
        NAMES stdc++fs
        HINTS /usr/lib/gcc/x86_64-linux-gnu/8/
)
if (FS_LIBRARY)
    target_link_libraries(BMSTU_HW_4_LIB ${FS_LIBRARY})
else ()
	if (NOT MSVC)
		message(WARNING "Filesystem library not found")
	endif ()
endif ()


# Main executable

add_executable(BMSTU_HW_4 main.cpp ${BMSTU_HW_4_LIB_SOURCE_COMMAND})

target_link_libraries(BMSTU_HW_4 BMSTU_HW_4_LIB)


# Tests

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/googletest/CMakeLists.txt")
    add_subdirectory(googletest)

    file(GLOB BMSTU_HW_4_TESTS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
    add_executable(BMSTU_HW_4_TESTS ${BMSTU_HW_4_TESTS_SOURCE})

    target_link_libraries(BMSTU_HW_4_TESTS BMSTU_HW_4_LIB gtest gtest_main)

    message(STATUS "Added google test config")
endif ()