# Общая настройка clang-tidy для всех проектов репозитория.
#
# Подключается из корневого CMakeLists.txt (тогда настройка наследуется
# всеми подпроектами через add_subdirectory) и из CMakeLists отдельной лабы,
# если её открывают как самостоятельный проект.
#
# Сам конфиг проверок лежит в корне репозитория в файле .clang-tidy.
#
# Опция OOP_CLANG_TIDY:
#   ON  — clang-tidy запускается при каждой сборке (строгий режим);
#   OFF — сборка без clang-tidy, удобно во время активной разработки.
# Переключается при конфигурации: cmake -DOOP_CLANG_TIDY=OFF ...
# В CLion: Settings -> Build, Execution, Deployment -> CMake -> CMake options.

option(OOP_CLANG_TIDY "Run clang-tidy during build" ON)

if(OOP_CLANG_TIDY)
    if(NOT CMAKE_CXX_CLANG_TIDY)
        find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)

        if(CLANG_TIDY_EXECUTABLE)
            set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXECUTABLE};--quiet")
        else()
            message(WARNING "clang-tidy не найден: статический анализ при сборке отключён")
        endif()
    endif()

    if(CMAKE_CXX_CLANG_TIDY)
        # CMake 4.3+ для C++20 добавляет в команду компиляции флаги
        # сканирования модулей (-fdeps-format, -fmodule-mapper, -fmodules-ts),
        # которые clang-tidy не понимает. Модули в лабах не используются,
        # поэтому сканирование можно отключить.
        set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
    endif()
else()
    message(STATUS "OOP_CLANG_TIDY=OFF: сборка без clang-tidy")
endif()
