//
// Created by Dor Shukrun on 28/08/2024.
//


#include "Logger.h"

#ifndef STARWARSSIMULATION_CONSTANT_H
#define STARWARSSIMULATION_CONSTANT_H

#include <limits> // For std::numeric_limits

// *** Grid Constants ***
constexpr int DEFAULT_GRID_SIZE = 25;
constexpr int MIN_GRID_SIZE = 6;
constexpr int MAX_GRID_SIZE = 30;

constexpr int DEFAULT_SCALE = 2;
constexpr int MIN_SCALE = 1;
constexpr int MAX_SCALE = 10;

constexpr int DEFAULT_ORIGIN_X = 0;
constexpr int DEFAULT_ORIGIN_Y = 0;
constexpr char EMPTY_CELL[] = ".";

// *** Command Constants ***
constexpr char COMMAND_CREATE[] = "create";
constexpr char COMMAND_STATUS[] = "status";
constexpr char COMMAND_GO[] = "go";
constexpr char COMMAND_SHOW[] = "show";
constexpr char COMMAND_PAN[] = "pan";
constexpr char COMMAND_ZOOM[] = "zoom";
constexpr char COMMAND_SIZE[] = "size";
constexpr char COMMAND_ATTACK[] = "attack";
constexpr char COMMAND_STOP[] = "stop";
constexpr char COMMAND_SHOOT[] = "shoot";
constexpr char COMMAND_FORTRESS[] = "fortress";
constexpr char COMMAND_STATION[] = "station";
constexpr char COMMAND_POSITION[] = "position";
constexpr char COMMAND_DESTINATION[] = "destination";
constexpr char COMMAND_COURSE[] = "course";
constexpr char COMMAND_START_SUPPLY[] = "start_supply";
constexpr char COMMAND_TEST[] = "test";
constexpr char COMMAND_EXIT[] = "exit";
constexpr char COMMAND_DEFAULT[] = "default";
constexpr char COMMAND_PLAY[] = "play";

// *** Falcon Constants ***
constexpr int FALCON_INITIAL_ATTACK_POWER = 5;
constexpr int FALCON_MAX_ATTACK_POWER = 20;
constexpr float FALCON_DEFAULT_SPEED = 3000.0f;
constexpr float FALCON_MIN_DISTANCE_TO_BOMBER = 250.0f; // 250 Km
constexpr float FALCON_MAX_DISTANCE_TO_TARGET = 100.0f; // 100 Km buffer

// *** Falcon Error Messages ***
constexpr char ERROR_TARGET_TOO_FAR[] = "Target is too far for attack";
constexpr char ERROR_TARGET_TOO_STRONG[] = "Target has too much defense power";
constexpr char ERROR_BOMBER_TOO_CLOSE[] = "Falcon is too close to a bomber for attack";

// *** Timer Constants ***
constexpr int DEFAULT_TICK_INTERVAL = 1;      // Default interval between ticks
constexpr int INITIAL_TICK_VALUE = 0;         // Initial value of the tick counter

// *** Error Messages ***
constexpr char ERROR_INVALID_SCALE[] = "Error: Invalid scale";
constexpr char ERROR_INVALID_SIZE[] = "Error: Invalid size";
constexpr char ERROR_FILE_NOT_FOUND[] = "Error: file not found";

// *** SpaceObject Constants ***
constexpr int MAX_ID_LENGTH = 15; // Maximum length for an ID

// *** Model Constants ***
constexpr float MAX_DISTANCE = std::numeric_limits<float>::max();
constexpr float DEFAULT_STAR_DESTROYER_SPEED = 2000.0f;
constexpr float DEFAULT_TIE_BOMBER_SPEED = 1000.0f;
constexpr float DEFAULT_SHUTTLE_SPEED = 500.0f;
constexpr float SPACESHIP_DEFAULT_SPEED = 500.0f; // Default speed in km/h

// *** Missile Constants ***
constexpr float MISSILE_SPEED = 3000.0f; // Speed of the missile in km/h

// *** Spaceship Constants ***
constexpr float SPACESHIP_MIN_DISTANCE_THRESHOLD = 0.1f;   // Threshold for reaching the destinationCMD
constexpr float SPACESHIP_ANGLE_THRESHOLD = 0.00001f;      // Threshold for angle deviation

// *** Distance Conversion Constants ***
constexpr float UNIT_TO_KM_CONVERSION = 1000.0f; // Conversion factor for units to kilometers

// *** Shuttle Constants ***
constexpr int SHUTTLE_MAX_CRYSTALS = 5;          // Maximum number of crystals the shuttle can carry
constexpr int SHUTTLE_MAX_POWER_UNITS = 20;      // Maximum power units the shuttle can have
constexpr int SHUTTLE_INITIAL_POWER_UNITS = 10;  // Initial power units for the shuttle

#endif //STARWARSSIMULATION_CONSTANT_H
