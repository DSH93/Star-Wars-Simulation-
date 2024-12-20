# Star Wars Simulation

## Overview
This project is a **Star Wars Simulation** implemented in C++ using advanced Object-Oriented Programming (OOP) principles and the MVC (Model-View-Controller) design pattern. The simulation models an intergalactic environment where various agents, spaceships, and stations interact in a dynamic grid-based map.

The main goal of the project is to manage **spaceships, imperial agents, and space objects** while supporting key operations like navigation, combat, and resource management.

---

## Project Structure
The project is organized into logical folders and files:

```
Star-Wars-Simulation/
│   CMakeLists.txt          # Build configuration
│   main.cpp                # Entry point of the simulation
│   README.md               # Project documentation
│
├───include/                # Header files
│   ├───controller/         # Controller classes
│   │       Controller.h
│   ├───model/              # Core model classes
│   │   ├───agents/         # Imperial agent-related headers
│   │   └───spaceships/     # Spaceship-related headers
│   ├───view/               # View class header
│   │       View.h
│   │
├───src/                    # Implementation files
│   ├───controller/         # Controller implementation
│   ├───model/              # Model implementation
│   │   └───spaceships/     # Spaceship implementations
│   ├───view/               # View implementation
│   │       View.cpp
│
├───logs/                   # Log files for debugging
└───cmake-build-debug-new/  # Build output folder
```

---

## Compilation and Execution
### Prerequisites:
- **CMake**: Version 3.10 or higher.
- **C++ Compiler**: Supports C++17 or above.

### Build Instructions:
1. Clone the repository:
   ```bash
   git clone https://github.com/DSH93/Star-Wars-Simulation-.git
   cd Star-Wars-Simulation
   ```
2. Create a build directory and compile the project:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```
3. Run the simulation:
   ```bash
   ./StarWarsSimulation <config-file>
   ```

### Configuration File:
The `site.dat` file contains the initial configuration of space stations:

#### Example - `site.dat`:
```text
station, Yavin, (6.00, 8.00), 100, 5
station, Rakatan, (10.00, 20.00), 20, 3
station, Arcanum, (30.00, 0.00), 50, 4
station, Claw, (20.00, 20.00), 10, 2
station, Facility729D, (10.00, 10.00), 2, 3
station, Drydock4, (0.00, 30.00), 6, 3
```
- Each line defines a station with:
    - **Type**: `station`
    - **Name**: Station identifier
    - **Position**: Coordinates `(x, y)`
    - **Crystals**: Initial crystal amount
    - **Production Rate**: Rate of crystal production per tick

---

## Classes and Responsibilities

### 1. **Model**
Manages the core logic and state of the simulation.
- **Responsibilities**:
    - Store all objects (spaceships, agents, and stations) in data structures.
    - Handle operations such as creating spaceships, moving them, attacking, and advancing time.
- **Key Methods**:
    - `advanceTime()`: Updates the state of all objects.
    - `addSite()`: Adds new space stations or fortresses.
    - `createSpaceship()`: Creates and initializes spaceships with pilots.
    - `statusCMD()`: Outputs the status of all objects.

### 2. **Spaceships**
Abstract base class for all spaceship types. Derived classes:
- **Falcon**: Represents rebel ships.
- **StarDestroyer**: Imperial ships capable of firing missiles.
- **TIEBomber**: Bombers piloted by commanders.
- **Shuttle**: Responsible for resource transport.

### 3. **Agents**
Imperial agents created using the **Abstract Factory** design pattern:
- **Admiral**
- **Commander**
- **Midshipman**

### 4. **SpaceStation**
Represents resource-producing stations that interact with shuttles.

### 5. **View**
Manages the visualization of the simulation on a dynamic **grid**:
- **Responsibilities**:
    - Update and display grid with objects.
    - Pan and zoom the view.
- **Key Methods**:
    - `printGrid()`: Displays the grid with current positions.
    - `pan(int a, int b)`: Moves the view origin.
    - `zoom(int s)`: Changes the scale of the grid.

### 6. **Controller**
Handles user commands and interacts with the `Model` and `View` components.
- Processes commands like `create`, `attack`, `status`, `go`, and `stop`.

### 7. **Timer**
Manages the simulation time using static members.

---

## Key Features
- **Grid-Based Visualization**:
    - Dynamic grid with pan and zoom capabilities.
    - Objects are rendered based on their positions.

- **Object Management**:
    - Creation of agents, spaceships, and space stations.
    - Interaction between ships (attacks, resource transport).

- **Time Simulation**:
    - The simulation advances through ticks, updating all objects.

- **Logging**:
    - Logs warnings, errors, and time-related events for debugging.

---

## Testing
The project includes comprehensive testing of the `Model` logic and simulation flow. Below is a breakdown of the current tests:

### Key Testing Areas
- **Model Validation**:
  - Ensures objects like stations, ships, and personnel (e.g., admirals, commanders) are correctly created and managed.
  - Verifies the correctness of attributes such as position, type, and associations.
- **Command Execution**:
  - Tests the behavior of commands like `shoot`, `course`, `stop`, and `destination`, ensuring the expected responses and movements in the simulation.
- **Patrol and Movement**:
  - Validates bomber patrol logic, ensuring patrol routes are followed and objects reach expected locations.
  - Tests shuttle supply missions, verifying proper movements and successful completion of tasks.
- **Attack Logic**:
  - Tests attack scenarios, ensuring correct damage, targeting, and results.
- **Grid Updates**:
  - Ensures that visualization changes occur accurately after updates to object positions.
- **Simulation Flow**:
  - Verifies the integration of all components, including stations, ships, commands, and interactions.

### Summary of Tests
- **Stations**: Validates creation and correct placement of space stations.
- **Admirals and Commanders**: Ensures leadership roles are properly initialized.
- **Ships**: Includes tests for Falcons, Destroyers, Bombers, and Shuttles, focusing on initialization and unique functionality.
- **Supply Missions**: Tests supply routes from stations to destinations, ensuring correct shuttle operations.
- **Commands**: Tests a wide variety of commands, including shooting, movement, and stopping.
- **Attacks**: Validates attack mechanics and ensures expected outcomes in various scenarios.

### Extensibility
For additional testing:
- **Unit Tests**: Extend testing coverage by adding unit tests for individual classes like `Falcon`, `TIEBomber`, and `Shuttle`.
- **Edge Cases**: Incorporate scenarios like invalid commands, overlapping positions, or extreme attribute values.
- **Performance Testing**: Add tests to validate the system's behavior under heavy load or with large numbers of objects.

All tests log their results to ensure traceability and debugging support, with a final summary of passed tests provided upon completion.


---

## Future Improvements
- Implement an interactive map displaying real-time object positions with distinct icons for different types (e.g., ships, stations).
- Add user controls with buttons for commands (e.g., "Launch," "Stop") and live data display (e.g., speed, health) on hover.
- Enhance performance by introducing multithreading for handling movements, attacks, and updates without interface lag.
- Introduce custom missions (e.g., "Defend Alpha") and resource management (e.g., fuel, ammunition) to influence object behavior.

---


## Author
**Dor Shukrun**
* **Email**: ShukrunDor@gmail.com
* **GitHub**: https://github.com/DSH93
* **LinkedIn**: https://www.linkedin.com/in/dor-shukrun/

---

## Acknowledgments
This project was developed as part of the Advanced Topics in Object-Oriented Programming (ATOOP) course, Winter 2024.
