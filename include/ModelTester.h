#ifndef STARWARSSIMULATION_MODELTESTER_H
#define STARWARSSIMULATION_MODELTESTER_H

#include "model/Model.h"
#include "Logger.h"
#include <cassert>
#include <vector>
#include <string>

/**
 * @class ModelTester
 * @brief Class responsible for testing various functionalities of the Star Wars Simulation Model.
 */
class ModelTester {
private:
    Model& model; ///< Reference to the singleton Model instance.

public:
    ModelTester(); ///< Constructor to initialize the tester with the Model instance.

    /**
     * @brief Runs all tests sequentially.
     *        Includes creation, commands, attacks, and supply tests.
     */
    void runAllTests();

    /**
     * @brief Tests the creation of space stations.
     *        Validates their positions and initialization parameters.
     */
    void testStations();

    /**
     * @brief Tests the creation of admirals.
     *        Ensures admirals are created correctly and linked to their respective objects.
     */
    void testAdmirals();

    /**
     * @brief Tests the creation of commanders.
     *        Ensures commanders are properly initialized and associated with their units.
     */
    void testCommanders();

    /**
     * @brief Tests the creation of midshipmen.
     *        Validates that midshipmen are created with proper attributes.
     */
    void testMidshipmen();

    /**
     * @brief Tests the creation of Falcon ships.
     *        Validates positions, types, and proper initialization.
     */
    void testFalcons();

    /**
     * @brief Tests the creation of destroyer ships.
     *        Checks their positions, types, and association with admirals.
     */
    void testDestroyers();

    /**
     * @brief Tests the creation and operations of bomber ships.
     *        Ensures proper initialization and association with commanders.
     */
    void testBombers();

    /**
     * @brief Tests the creation and supply operations of shuttles.
     *        Validates supply missions, positions, and types.
     */
    void testShuttles();

    /**
     * @brief Tests command execution like shooting, course adjustments, stopping, and destination setting.
     *        Verifies expected object behavior in response to commands.
     */
    void testCommands();

    /**
     * @brief Tests attack commands and verifies proper behavior.
     *        Ensures attacks follow the expected rules and logic.
     */
    void testAttacks();

    /**
     * @brief Tests destination and position commands.
     *        Validates object movement to expected locations.
     */
    void testDestinationAndPositions();

    /**
     * @brief Tests the shooting and initial movement commands.
     *        Validates object actions immediately after the command execution.
     */
    void testShootingAndInitialMovement();

    /**
     * @brief Tests course adjustments.
     *        Verifies object movement and orientation after course changes.
     */
    void testCourseAdjustments();

    /**
     * @brief Tests stopping commands.
     *        Ensures objects stop at their expected positions.
     */
    void testStoppingAndFinalAssertions();

    /**
     * @brief Tests bomber patrol behavior.
     *        Validates patrol routes and arrival at designated positions.
     */
    void testBombersPatrol();

    /**
     * @brief Tests the extended patrol logic for bombers.
     *        Ensures bombers visit all expected patrol stations.
     */
    void testBomberExtendedPatrol();

    /**
     * @brief Tests the initial patrol behavior for bombers.
     *        Validates their first patrol movements.
     */
    void testBomberInitialPatrol();

    /**
     * @brief Tests bomber creation and initialization.
     *        Ensures bombers are created with proper types and attributes.
     */
    void testBomberInitializationAndCreation();

    /**
     * @brief Tests shuttle supply missions.
     *        Includes initialization, mission execution, and completion validation.
     */
    void testSupply();

    /**
     * @brief Initializes shuttle supply missions.
     *        Validates the setup of supply routes and positions.
     */
    void testSupplyInitialization();

    /**
     * @brief Tests the supply mission from Delta station to the Death Star (DS).
     *        Ensures proper shuttle movements and mission completion.
     */
    void testSupplyDeltaToDS();

    /**
     * @brief Tests the supply mission from Zeta station to the Death Star (DS).
     *        Validates movements and ensures mission success.
     */
    void testSupplyZetaToDS();

    /**
     * @brief Initializes the sites (stations and fortresses) for testing.
     *        Ensures proper setup of positions, attributes, and connections.
     */
    void initializeSitesToTest();

    /**
     * @brief Prints the test progress.
     *        Displays a loading-like message during test initialization.
     */
    static void printTests();

    /**
     * @brief Prints a summary of passed tests.
     *        Displays all tests that were successfully completed.
     */
    static void printPassedTests();
};

#endif // STARWARSSIMULATION_MODELTESTER_H
