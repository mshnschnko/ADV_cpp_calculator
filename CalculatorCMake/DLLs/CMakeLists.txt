# CMakeList.txt: проект CMake для calc_with_dll; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# unar opers
add_subdirectory("sinus")
add_subdirectory("cosinus")
add_subdirectory("logarithm")

# binary opers
add_subdirectory("power")