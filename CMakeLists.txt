cmake_minimum_required(VERSION 3.20)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 14)

set(SFML_DIR "SFML-2.5.1\\lib\\cmake\\SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(GeneticAlgorithm main.cpp
        GraphicsManager/Object.cpp
        Objects/Button.h
        SpaceManager.h SpaceManager.cpp
        Objects/Background.h Objects/Background.cpp
        Objects/ConstantsInit.cpp
        GeneticAlgorithmCore/Evolution.h
        GeneticAlgorithmCore/Evolution.cpp
        GeneticAlgorithmCore/Bot.h
        GeneticAlgorithmCore/Battle.cpp
        GeneticAlgorithmCore/Mutation.cpp
        GeneticAlgorithmCore/Scene.h Objects/SceneGraphic.h Objects/Background.cpp Objects/Button.cpp Objects/SceneGraphic.cpp)

target_link_libraries(GeneticAlgorithm sfml-graphics sfml-audio)