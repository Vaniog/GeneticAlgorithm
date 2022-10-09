cmake_minimum_required(VERSION 3.20)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 14)

set(SFML_DIR "SFML-2.5.1\\lib\\cmake\\SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(GeneticAlgorithm main.cpp
        GraphicsManager/Object.cpp
        Objects/include/Button.h
        SpaceManager.h SpaceManager.cpp
        Objects/include/Background.h Objects/src/Background.cpp
        Objects/src/ConstantsInit.cpp
        GeneticAlgorithmCore/Evolution.h
        GeneticAlgorithmCore/Evolution.cpp
        GeneticAlgorithmCore/Bot.h
        GeneticAlgorithmCore/Battle.cpp
        GeneticAlgorithmCore/Mutation.cpp
        GeneticAlgorithmCore/Scene.h Objects/include/SceneGraphic.h Objects/src/Background.cpp Objects/src/Button.cpp Objects/src/SceneGraphic.cpp)

target_link_libraries(GeneticAlgorithm sfml-graphics sfml-audio)