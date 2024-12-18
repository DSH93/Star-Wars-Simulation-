cmake_minimum_required(VERSION 3.10)
project(StarWarsSimulation)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS_DEBUG "-g")

include_directories(include)


set(SOURCES
        main.cpp
        src/model/Model.cpp
        src/model/spaceships/Shuttle.cpp
        src/model/spaceships/Spaceship.cpp
        src/model/SpaceStation.cpp
        src/model/spaceships/TIEBomber.cpp
        src/model/spaceships/StarDestroyer.cpp
        src/model/spaceships/Falcon.cpp
        src/controller/Controller.cpp
        src/view/View.cpp
        src/model/spaceships/Missile.cpp
        include/Constant.h
        src/Logger.cpp
        include/Logger.h
        src/ModelTester.cpp
        include/ModelTester.h
)


add_executable(simST ${SOURCES})
