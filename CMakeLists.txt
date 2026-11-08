cmake_minimum_required(VERSION 4.2.3)
project(oop_labsNSU_Nyavro_Maxim)

set(CMAKE_CXX_STANDARD 14)

find_program(CLANG_TIDY clang-tidy)

if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
endif()

include_directories(oop)

add_executable(oop_labsNSU_Nyavro_Maxim
        oop/main.cpp
        oop/wordCounter.cpp
        oop/wordCounter.h
        oop/FileReader.cpp
        oop/FileReader.h
        oop/CSVWriter.cpp
        oop/CSVWriter.h)
