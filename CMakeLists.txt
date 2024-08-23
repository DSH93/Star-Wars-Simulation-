cmake_minimum_required(VERSION 3.10)
project(StarWarsSimulation)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SOURCES "src/*.cpp" "src/model/*.cpp" "src/view/*.cpp" "src/controller/*.cpp")

add_executable(StarWarsSimulation ${SOURCES}
        src/main.cpp
        src/model/Position.cpp
        include/model/Position.h
        src/model/Direction.cpp
        include/model/Direction.h
        src/model/Space.cpp
        include/model/Space.h
        src/model/SimulationModel.cpp
        include/model/SimulationModel.h)
