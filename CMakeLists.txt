cmake_minimum_required(VERSION 3.20)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 14)

if (WIN32)
    set(SFML_DIR "C:\\SFML\\lib\\cmake\\SFML")
    set(SFML_STATIC_LIBRARIES TRUE)
endif (WIN32)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(GeneticAlgorithm main.cpp
        SpaceManager.h SpaceManager.cpp

        GraphicsManager/include/Object.h GraphicsManager/src/Object.cpp
        GraphicsManager/include/Space.h GraphicsManager/src/Space.cpp

        Objects/src/ConstantsInit.cpp
        Objects/include/Button.h Objects/src/Button.cpp
        Objects/include/Background.h Objects/src/Background.cpp
        Objects/include/SceneGraphic.h Objects/src/SceneGraphic.cpp
        Objects/include/ButtonNew.h Objects/src/ButtonNew.cpp

        GeneticAlgorithmCore/Evolution.h GeneticAlgorithmCore/Evolution.cpp
        GeneticAlgorithmCore/Bot.h
        GeneticAlgorithmCore/Battle.cpp
        GeneticAlgorithmCore/Mutation.cpp
        GeneticAlgorithmCore/Scene.h
        )
target_link_libraries(GeneticAlgorithm sfml-graphics sfml-audio)