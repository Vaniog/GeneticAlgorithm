cmake_minimum_required(VERSION 3.23)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(SFML_DIR "lib\\SFML-2.5.1\\lib\\cmake\\SFML")

add_executable(GeneticAlgorithm main.cpp GraphicsManager/Object.cpp)

target_link_libraries(GeneticAlgorithm sfml-graphics sfml-audio)