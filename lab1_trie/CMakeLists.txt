cmake_minimum_required(VERSION 4.3)
project(lab1_trie)

set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_CXX_CLANG_TIDY)
    include("${CMAKE_CURRENT_LIST_DIR}/../cmake/ClangTidy.cmake")
endif()

# Основная программа
add_executable(lab1_trie
        main.cpp
        trie.h
        trie.cpp
)

# Тесты
enable_testing()

find_package(GTest REQUIRED)

# Тестовый код не проверяем clang-tidy: макросы GoogleTest дают много шума.
set_source_files_properties(tests/test.cpp PROPERTIES
        SKIP_LINTING TRUE
)

add_executable(trie_tests
        tests/test.cpp
        trie.h
        trie.cpp
)
target_include_directories(trie_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(trie_tests PRIVATE
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(trie_tests)