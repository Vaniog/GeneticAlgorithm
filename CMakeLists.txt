cmake_minimum_required(VERSION 3.20)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 14)

set(SFML_DIR "lib\\SFML-2.5.1\\lib\\cmake\\SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(GeneticAlgorithm main.cpp GraphicsManager/Object.cpp Objects/Button.h SpaceManager.h SpaceManager.cpp Objects/Background.h Objects/SceneDraft.h Objects/ConstantsInit.cpp)

target_link_libraries(GeneticAlgorithm sfml-graphics sfml-audio)