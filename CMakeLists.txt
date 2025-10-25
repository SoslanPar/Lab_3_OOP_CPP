cmake_minimum_required(VERSION 3.10)
project(Laboratory_3)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")


# Установка Google Test
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
    TLS_VERIFY false
)

# Отключаем использование статической библиотеки и переключаем на динамическую (Более подробно про это можно прочитать в файле Materials.md)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_library(${PROJECT_NAME}_lib src/figure.cpp src/point.cpp src/array_of_figures.cpp src/pentagon.cpp src/hexagon.cpp src/octagon.cpp)
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

# Добавление тестов
enable_testing()

# Тесты для класса Point
add_executable(test_point tests/test_point.cpp)
target_link_libraries(test_point ${PROJECT_NAME}_lib gtest_main)

add_test(NAME Lab_3_tests_point COMMAND test_point)

# Тесты для класса Pentagon
add_executable(test_pentagon tests/test_pentagon.cpp)
target_link_libraries(test_pentagon ${PROJECT_NAME}_lib gtest_main)

add_test(NAME Lab_3_tests_pentagon COMMAND test_pentagon)

# Тесты для класса Hexagon
add_executable(test_hexagon tests/test_hexagon.cpp)
target_link_libraries(test_hexagon ${PROJECT_NAME}_lib gtest_main)

add_test(NAME Lab_3_tests_hexagon COMMAND test_hexagon)

# Тесты для класса Ocatogn
add_executable(test_ocatgon tests/test_octagon.cpp)
target_link_libraries(test_ocatgon ${PROJECT_NAME}_lib gtest_main)

add_test(NAME Lab_3_tests_ocatgon COMMAND test_ocatgon)

# Тесты для класса Array_Of_Figures
add_executable(test_array_of_figures tests/test_array_of_figures.cpp)
target_link_libraries(test_array_of_figures ${PROJECT_NAME}_lib gtest_main)

add_test(NAME Lab_3_tests_array_of_figures COMMAND test_array_of_figures)