cmake_minimum_required(VERSION 4.2.3)
project(oop_labsNSU_Nyavro_Maxim)

set(CMAKE_CXX_STANDARD 14)

# clang-tidy для текущего проекта и всех подпроектов, подключённых ниже.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(ClangTidy)

add_executable(oop_labsNSU_Nyavro_Maxim
        oop/main.cpp
        oop/wordCounter.cpp
        oop/wordCounter.h
        oop/FileReader.cpp
        oop/FileReader.h
        oop/CSVWriter.cpp
        oop/CSVWriter.h
        oop/wordFrequency.h)

target_include_directories(oop_labsNSU_Nyavro_Maxim PRIVATE oop)

# Автоматически подключаем все лабораторные проекты (lab1_trie, lab2, ...).
# Достаточно положить папку с CMakeLists.txt рядом с этим файлом — она
# подхватится при следующей переконфигурации вместе с общим clang-tidy.
file(GLOB labDirs CONFIGURE_DEPENDS LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/lab*")

foreach(labDir IN LISTS labDirs)
    if(EXISTS "${labDir}/CMakeLists.txt")
        # EXCLUDE_FROM_ALL: незавершённая лаба не ломает сборку всего проекта,
        # но её цель по-прежнему можно собрать отдельно (и clang-tidy при этом работает).
        add_subdirectory("${labDir}" EXCLUDE_FROM_ALL)
    endif()
endforeach()
