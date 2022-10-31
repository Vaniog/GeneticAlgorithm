cmake_minimum_required(VERSION 3.20)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 14)

if (WIN32)
    set(SFML_DIR "C:\\SFML\\lib\\cmake\\SFML")
    set(SFML_STATIC_LIBRARIES TRUE)
endif (WIN32)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(GeneticAlgorithm main.cpp
        GraphicsManager/include/SpaceManager.h GraphicsManager/src/SpaceManager.cpp

        GraphicsManager/include/Object.h GraphicsManager/src/Object.cpp
        GraphicsManager/include/Space.h GraphicsManager/src/Space.cpp

        Objects/src/ConstantsInit.cpp
        Objects/include/Background.h Objects/src/Background.cpp
        Objects/include/SceneGraphic.h Objects/src/SceneGraphic.cpp

        GeneticAlgorithmCore/Evolution.h GeneticAlgorithmCore/Evolution.cpp
        GeneticAlgorithmCore/Bot.h
        GeneticAlgorithmCore/Bot.cpp
        GeneticAlgorithmCore/Battle.cpp
        GeneticAlgorithmCore/Mutation.cpp
        GeneticAlgorithmCore/Scene.h
        GraphicsManager/include/ObjectsAttributes.h GraphicsManager/src/ObjectsAttributes.cpp
        Objects/src/Button.cpp Objects/include/Button.h
        MySpaceManager.h)
target_link_libraries(GeneticAlgorithm sfml-graphics sfml-audio)