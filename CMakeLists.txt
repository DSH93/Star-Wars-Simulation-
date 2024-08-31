cmake_minimum_required(VERSION 3.10)
project(StarWarsSimulation)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

add_executable(simST ${SOURCES}
        main.cpp
        src/model/Model.cpp
        src/model/spaceships/Shuttle.cpp
        src/model/spaceships/Spaceship.cpp
        src/model/Timer.cpp
        src/model/SpaceStation.cpp
        src/model/spaceships/TIEBomber.cpp
        src/model/spaceships/StarDestroyer.cpp
        src/model/spaceships/MillenniumFalcon.cpp
        src/model/agent/ImperialAgent.cpp
        src/controller/Controller.cpp
        src/view/View.cpp
)

