cmake_minimum_required(VERSION 3.10)
project(StarWarsSimulation)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SOURCES "src/*.cpp" "src/model/*.cpp" "src/view/*.cpp" "src/controller/*.cpp")

add_executable(StarWarsSimulation ${SOURCES}
        src/main.cpp
        include/model/Position.h
        include/model/Direction.h
        src/model/Model.cpp
        include/model/Model.h
        include/model/SpaceObject.h
        src/model/Shuttle.cpp
        include/model/Shuttle.h
        src/model/Spaceship.cpp
        include/model/Spaceship.h
        include/model/Timer.h
        src/model/SpaceStation.cpp
        include/model/SpaceStation.h
        include/model/FortressStar.h
        src/model/TIEBomber.cpp
        include/model/TIEBomber.h
        src/model/StarDestroyer.cpp
        include/model/StarDestroyer.h)
