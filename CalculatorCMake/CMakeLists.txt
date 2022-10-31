# CMakeList.txt: проект CMake для CalculatorCMake; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)             # Стандарт C++
set(CMAKE_CXX_STANDARD_REQUIRED ON)    # Обязательность установки указанного стандарта (если OFF (по умолчанию), то воспринимается как совет)
# project ("CalculatorCMake")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (CalculatorCMake "CalculatorCMake.cpp" "CalculatorCMake.h" "Operators/operator.h" "Operators/st_operators.h" "Operators/operator.cpp" "Error/error.h" "Token/token.h" "reader/reader.h" "reader/reader.cpp" "Parser/parser.h" "Parser/parser.cpp" "Eval/eval.h" "Eval/eval.cpp" "PluginLoader/pluginLoader.h" "Calculator/calculator.h" "Calculator/calculator.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
add_subdirectory ("DLLs")