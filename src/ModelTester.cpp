#include <thread>
#include <vector>
#include <string>

#include "ModelTester.h"


ModelTester::ModelTester() : model(Model::getInstance()) {}

std::vector<std::string> passedTests;

void ModelTester::runAllTests() {
    printTests();
    initializeSitesToTest();

    try {
        testBombersPatrol();
        passedTests.emplace_back("Bombers Patrol Test");
        testStations();
        passedTests.emplace_back("Station Creation Test");
        testAdmirals();
        passedTests.emplace_back("Admiral creation");
        testCommanders();
        passedTests.emplace_back("Commanders creation");
        testBombers();
        passedTests.emplace_back("Bombers And Commanders creation Test");
        testMidshipmen();
        passedTests.emplace_back("Midshipmen creation");
        testFalcons();
        passedTests.emplace_back("Falcons creation Test");
        testDestroyers();
        passedTests.emplace_back("Star Destroyers And Admirals creation Test");
        testShuttles();
        passedTests.emplace_back("Shuttles And Midshipmen creation Test");
        testCommands();
        passedTests.emplace_back("Shoot, Course, Stop, Destination And Position commands Test");
        testAttacks();
        passedTests.emplace_back("Falcon Attacks on Shuttle Test");
        testSupply();
        passedTests.emplace_back("Shuttles Supply Missions Test");

        std::cout << "\n\n\nAll tests completed successfully." << std::endl;
        Logger::getInstance().log("All tests completed successfully.");


        printPassedTests();
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        Logger::getInstance().log(std::string("Test failed: ") + e.what());
    }
}

void ModelTester::printPassedTests() {
    std::cout << "Summary of passed tests:" << std::endl;
    for (const auto& test : passedTests) {
        std::cout << "[CHECK] " << test << std::endl;
    }
    Logger::getInstance().log("Summary of passed tests:");
    for (const auto& test : passedTests) {
        Logger::getInstance().log("[CHECK] " + test);
    }
}

void ModelTester::printTests() {
    Logger::getInstance().log("Starting all tests...");
    std::cout << "Testing";
    std::this_thread::sleep_for(std::chrono::milliseconds (300));
    std::cout << ".";
    std::this_thread::sleep_for(std::chrono::milliseconds (300));
    std::cout << ".";
    std::this_thread::sleep_for(std::chrono::milliseconds (300));
    std::cout << "." << std::endl;





}

void ModelTester::testStations() {
    Logger::getInstance().log("Testing station creation...");
    model.addSite({COMMAND_STATION, "Alpha", "20.00", "20.00", "50000", "10"});
    model.addSite({COMMAND_STATION, "Beta", "30.00", "30.00", "60000", "15"});
    model.addSite({COMMAND_STATION, "Gamma", "10.00", "0.00", "70000", "20"});
    model.addSite({COMMAND_STATION, "Delta", "30.00", "10.00", "50000", "10"});
    model.addSite({COMMAND_STATION, "Zeta", "40.00", "15.00", "50000", "10"});

    // Assertions
    assert(model.validateObjectExists("Alpha"));
    assert(model.getObject("Alpha")->getPosition().getX() == 20.00);
    assert(model.getObject("Alpha")->getPosition().getY() == 20.00);
    assert(model.validateObjectExists("Beta"));
    assert(model.getObject("Beta")->getPosition().getX() == 30.00);
    assert(model.getObject("Beta")->getPosition().getY() == 30.00);
    assert(model.validateObjectExists("Gamma"));
    assert(model.getObject("Gamma")->getPosition().getX() == 10.00);
    assert(model.getObject("Gamma")->getPosition().getY() == 0.00);
    assert(model.validateObjectExists("Delta"));
    assert(model.getObject("Delta")->getPosition().getX() == 30.00);
    assert(model.getObject("Delta")->getPosition().getY() == 10.00);
    assert(model.validateObjectExists("Zeta"));
    assert(model.getObject("Zeta")->getPosition().getX() == 40.00);
    assert(model.getObject("Zeta")->getPosition().getY() == 15.00);


}

void ModelTester::testAdmirals() {
    Logger::getInstance().log("Testing admiral creation...");
    model.create({COMMAND_CREATE, "admiral", "Thrawn"});
    model.create({COMMAND_CREATE, "admiral", "Tarkin"});


}

void ModelTester::testCommanders() {
    Logger::getInstance().log("Testing commander creation...");
    model.create({COMMAND_CREATE, "commander", "Piett"});
    model.create({COMMAND_CREATE, "commander", "Ozzel"});

}

void ModelTester::testMidshipmen() {
    Logger::getInstance().log("Testing midshipman creation...");
    model.create({COMMAND_CREATE, "midshipman", "Ackbar"});
    model.create({COMMAND_CREATE, "midshipman", "Peter"});
    model.create({COMMAND_CREATE, "midshipman", "Flavius"});


}

void ModelTester::testFalcons() {
    Logger::getInstance().log("Testing falcon creation...");
    model.create({COMMAND_CREATE, "falcon", "F1", "30.00", "15.00"});
    model.create({COMMAND_CREATE, "falcon", "Millennium", "42.00", "42.00"});

    // Assertions
    assert(model.validateObjectExists("F1"));
    assert(model.getObject("F1")->getPosition().getX() == 30.00);
    assert(model.getObject("F1")->getPosition().getY() == 15.00);
    assert(model.getObject("F1")->getType() == "Falcon");

    assert(model.validateObjectExists("Millennium"));
    assert(model.getObject("Millennium")->getPosition().getX() == 42.00);
    assert(model.getObject("Millennium")->getPosition().getY() == 42.00);
    assert(model.getObject("Millennium")->getType() == "Falcon");
}

void ModelTester::testDestroyers() {
    Logger::getInstance().log("Testing destroyer creation...");
    model.create({COMMAND_CREATE, "destroyer", "D1", "Thrawn", "50.00", "20.00"});
    model.create({COMMAND_CREATE, "destroyer", "D2", "Tarkin", "20.00", "10.00"});

    // Assertions
    assert(model.validateObjectExists("D1"));
    assert(model.getObject("D1")->getPosition().getX() == 50.00);
    assert(model.getObject("D1")->getPosition().getY() == 20.00);
    assert(model.getObject("D1")->getType() == "Star Destroyer");

    assert(model.validateObjectExists("D2"));
    assert(model.getObject("D2")->getPosition().getX() == 20.00);
    assert(model.getObject("D2")->getPosition().getY() == 10.00);
    assert(model.getObject("D2")->getType() == "Star Destroyer");
}

void ModelTester::testShuttles() {
    Logger::getInstance().log("Testing shuttle creation...");
    model.create({COMMAND_CREATE, "shuttle", "S1", "Peter", "38.00", "6.00"});
    model.create({COMMAND_CREATE, "shuttle", "S2", "Ackbar", "5.00", "5.00"});

    // Assertions
    assert(model.validateObjectExists("S1"));
    assert(model.validateObjectExists("S2"));
    assert(model.getObject("S1")->getType() == "Shuttle");
    assert(model.getObject("S2")->getType() == "Shuttle");
    assert(model.getObject("S1")->getPosition().getX() == 38.00);
    assert(model.getObject("S1")->getPosition().getY() == 6.00);
    assert(model.getObject("S2")->getPosition().getX() == 5.00);
    assert(model.getObject("S2")->getPosition().getY() == 5.00);
}

void ModelTester::testCommands() {
    Logger::getInstance().log("Testing commands execution...");
    testShootingAndInitialMovement();
    testCourseAdjustments();
    testStoppingAndFinalAssertions();
    testDestinationAndPositions();

}

void ModelTester::testShootingAndInitialMovement() {
    Logger::getInstance().log("Testing shooting and initial movement...");
    model.shootCMD({"D1", COMMAND_SHOOT, "42.00", "42.00"});
    for (int i = 0; i < 8; i++) {
        model.goCMD();
    }
    // Assertions
    auto falcon = std::dynamic_pointer_cast<Falcon>(model.getObject("Millennium"));
    assert(falcon->isAlive() == false); // Falcon should be dead after 8 turns
}

void ModelTester::testCourseAdjustments() {
    Logger::getInstance().log("Testing course adjustments...");
    model.courseCMD({"D1", COMMAND_COURSE, "270.00"});
    model.courseCMD({"D2", COMMAND_COURSE, "0.00"});

    for (int i = 0; i < 5; i++) {
        model.goCMD();
    }

    // Assertions
    assert(model.getObject("D1")->getPosition().getX() == 40.00); // Star Destroyer should move to the left
    assert(model.getObject("D2")->getPosition().getY() == 20.00); // Star Destroyer should move to the right

    model.courseCMD({"D1", COMMAND_COURSE, "90.00"});
    model.courseCMD({"D2", COMMAND_COURSE, "180.00"});

    for (int i = 0; i < 5; i++) {
        model.goCMD();
    }

    // Assertions
    assert(model.getObject("D1")->getPosition().getX() == 50.00); // Star Destroyer should move down
    assert(model.getObject("D2")->getPosition().getY() == 10.00); // Star Destroyer should move up
}

void ModelTester::testStoppingAndFinalAssertions() {
    Logger::getInstance().log("Testing stopping and final assertions...");
    model.stopCMD({"D1", COMMAND_STOP});

    for (int i = 0; i < 5; i++) {
        model.goCMD();
    }

    // Assertions
    assert(model.getObject("D1")->getPosition().getX() == 50.00); // Star Destroyer should not move
}

void ModelTester::testDestinationAndPositions(){
    model.create({COMMAND_CREATE, "admiral", "test1"});
    model.create({COMMAND_CREATE, "commander", "test2"});

    model.create({COMMAND_CREATE, "falcon", "F15", "30.00", "15.00"});
    model.create({COMMAND_CREATE, "bomber", "B12", "test2", "5.00", "0.00"});
    model.create({COMMAND_CREATE, "destroyer", "D11", "test1", "0.00", "0.00"});

    model.destinationCMD({"B12", COMMAND_DESTINATION, "Gamma"}); // get there int 5 turns
    model.positionCMD({"F15", COMMAND_POSITION, "30.00", "30.00"}); // get there int 5 turns
    model.destinationCMD({"D11", COMMAND_DESTINATION, "Gamma"}); // get there int 5 turns

    for (int i = 0; i < 5; i++) {
        model.goCMD();
    }

    assert(model.getObject("B12")->getPosition().getX() == 10.00); //  [5(turns) * 1000 km = 5000 km] from 10.00 to 5.00
    assert(model.getObject("B12")->getPosition().getY() == 0.00); //[5(turns) * 1000 km = 5000 km] from 0.00 to 0.00
    assert(model.getObject("F15")->getPosition().getX() == 30.00);
    assert(model.getObject("F15")->getPosition().getY() == 30.00);
    assert(model.getObject("D11")->getPosition().getX() == 10.00);


}

void ModelTester::testAttacks() {
    Logger::getInstance().log("Testing attacks...");

    for (int i = 1; i < 11; i++) {
        const std::string& id = "FF" + std::to_string(i);
        model.create({COMMAND_CREATE, "falcon", id, "60.00", "60.00"});
    }
    model.create({COMMAND_CREATE, "shuttle", "S3", "Ackbar", "60.0001", "60.0001"});
    auto shuttle = std::dynamic_pointer_cast<Shuttle>(model.getObject("S3"));
    assert(shuttle->isAlive() == true); // Shuttle should be Alive

    model.attackCMD({"F15", COMMAND_ATTACK, "S3"}); // too far to attack -1

    for (int i = 1; i < 10; i++) {
        const std::string& id = "FF" + std::to_string(i);
        model.attackCMD({id, COMMAND_ATTACK, "S3"});
    }

    assert(shuttle->isAlive() == false); // Shuttle should be dead



    // Assertions
    // Validate attack behavior
}

void ModelTester::testBombers() {
    Logger::getInstance().log("Testing bomber creation...");
    model.create({COMMAND_CREATE, "bomber", "B1", "Piett", "10.00", "25.00"});
    model.create({COMMAND_CREATE, "bomber", "B2", "Ozzel", "30.00", "40.00"});

    // Assertions
    assert(model.validateObjectExists("B1"));
    assert(model.validateObjectExists("B2"));
    assert(model.getObject("B1")->getType() == "TIEBomber");
    assert(model.getObject("B2")->getType() == "TIEBomber");
    assert(model.getObject("B1")->getPosition().getX() == 10.00);
    assert(model.getObject("B1")->getPosition().getY() == 25.00);
    assert(model.getObject("B2")->getPosition().getX() == 30.00);
    assert(model.getObject("B2")->getPosition().getY() == 40.00);




}

void ModelTester::testBombersPatrol() {
    testBomberInitializationAndCreation();
    testBomberInitialPatrol();
    testBomberExtendedPatrol();
}

void ModelTester::testBomberInitializationAndCreation() {
    model.create({COMMAND_CREATE, "commander", "James"});
    model.create({COMMAND_CREATE, "bomber", "BB", "James", "24.00", "00.00"});

    assert(model.validateObjectExists("BB"));
    assert(model.getObject("BB")->getType() == "TIEBomber");
}

void ModelTester::testBomberInitialPatrol() {
    auto bomber = std::dynamic_pointer_cast<TIEBomber>(model.getObject("BB"));
    auto arcanum = std::dynamic_pointer_cast<SpaceStation>(model.getObject("Arcanum"));
    auto DS = std::dynamic_pointer_cast<FortressStar>(model.getObject("DS"));

    for (int i = 0; i < 6; i++) model.goCMD();
    Logger::getInstance().log("Bomber position: " + std::to_string(bomber->getPosition().getX()));
    Logger::getInstance().log("Arcanum position: " + std::to_string(arcanum->getPosition().getX()));
    assert(bomber->getPosition().getX() == arcanum->getPosition().getX());

    for (int i = 6; i < 21; i++) model.goCMD();
    Logger::getInstance().log("Bomber position: " + std::to_string(bomber->getPosition().getX()));
    Logger::getInstance().log("DS position: " + std::to_string(DS->getPosition().getX()));
    assert(bomber->getPosition().getX() == DS->getPosition().getX());
}

void ModelTester::testBomberExtendedPatrol() {
    auto bomber = std::dynamic_pointer_cast<TIEBomber>(model.getObject("BB"));
    auto claw = std::dynamic_pointer_cast<SpaceStation>(model.getObject("Claw"));
    auto facility = std::dynamic_pointer_cast<SpaceStation>(model.getObject("Facility729D"));
    auto drydock = std::dynamic_pointer_cast<SpaceStation>(model.getObject("Drydock4"));
    auto yavin = std::dynamic_pointer_cast<SpaceStation>(model.getObject("Yavin"));
    auto rakatan = std::dynamic_pointer_cast<SpaceStation>(model.getObject("Rakatan"));

    for (int i = 21; i < 44; i++) model.goCMD();
    Logger::getInstance().log("Bomber position: " + std::to_string(bomber->getPosition().getX()));
    Logger::getInstance().log("Claw position: " + std::to_string(claw->getPosition().getX()));
    assert(bomber->getPosition().getX() == claw->getPosition().getX());

    for (int i = 44; i < 54; i++) model.goCMD();
    Logger::getInstance().log("Bomber position: " + std::to_string(bomber->getPosition().getX()));
    Logger::getInstance().log("Rakatan position: " + std::to_string(rakatan->getPosition().getX()));
    assert(bomber->getPosition().getX() == rakatan->getPosition().getX());

    for (int i = 54; i < 63; i++) model.goCMD();
    Logger::getInstance().log("Bomber position: " + std::to_string(bomber->getPosition().getX()));
    Logger::getInstance().log("Facility729D position: " + std::to_string(facility->getPosition().getX()));
    assert(bomber->getPosition().getX() == facility->getPosition().getX());

    for (int i = 63; i < 69; i++) model.goCMD();
    Logger::getInstance().log("Bomber position: " + std::to_string(bomber->getPosition().getX()));
    Logger::getInstance().log("Yavin position: " + std::to_string(yavin->getPosition().getX()));
    assert(bomber->getPosition().getX() == yavin->getPosition().getX());

    for (int i = 69; i < 92; i++) model.goCMD();
    Logger::getInstance().log("Bomber position: " + std::to_string(bomber->getPosition().getX()));
    Logger::getInstance().log("Drydock4 position: " + std::to_string(drydock->getPosition().getX()));
    assert(bomber->getPosition().getX() == drydock->getPosition().getX());

    for (int i = 92; i < 135; i++) model.goCMD();
    auto arcanum = std::dynamic_pointer_cast<SpaceStation>(model.getObject("Arcanum"));
    assert(bomber->getPosition().getX() == arcanum->getPosition().getX()); // back to the start
}

void ModelTester::testSupply() {
    testSupplyInitialization();
    testSupplyDeltaToDS();
    testSupplyZetaToDS();
}

void ModelTester::testSupplyInitialization() {
    model.create({COMMAND_CREATE, "midshipman", "Pavel"});

    model.create({COMMAND_CREATE, "shuttle", "supplyShuttle", "Pavel", "35.00", "10.00"});
    model.SupplyCMD({"supplyShuttle", COMMAND_START_SUPPLY, "Delta", "DS"});
    model.SupplyCMD({"supplyShuttle", COMMAND_START_SUPPLY, "Zeta", "DS"});
}

void ModelTester::testSupplyDeltaToDS() {
    auto shuttle = std::dynamic_pointer_cast<Shuttle>(model.getObject("supplyShuttle"));

    for (int i = 0; i < 10; i++) model.goCMD();
    assert(shuttle->getPosition() == model.getObject("Delta")->getPosition());
    Logger::getInstance().log("Shuttle position: " + std::to_string(shuttle->getPosition().getX()));
    Logger::getInstance().log("Delta position: " + std::to_string(model.getObject("Delta")->getPosition().getX()));

    model.goCMD();
    Logger::getInstance().log("Shuttle position: " + std::to_string(shuttle->getPosition().getX()));
    Logger::getInstance().log("Delta position: " + std::to_string(model.getObject("Delta")->getPosition().getX()));
    assert(shuttle->getPosition() == model.getObject("Delta")->getPosition());


    for (int i = 0; i < 20; i++) model.goCMD();
    Logger::getInstance().log("Shuttle position: " + std::to_string(shuttle->getPosition().getX()));
    Logger::getInstance().log("DS position: " + std::to_string(model.getObject("DS")->getPosition().getX()));
    assert(shuttle->getPosition() == model.getObject("DS")->getPosition());


    model.goCMD();
    Logger::getInstance().log("Shuttle position: " + std::to_string(shuttle->getPosition().getX()));
    Logger::getInstance().log("DS position: " + std::to_string(model.getObject("DS")->getPosition().getX()));
    assert(shuttle->getPosition() == model.getObject("DS")->getPosition());

}

void ModelTester::testSupplyZetaToDS() {
    auto shuttle = std::dynamic_pointer_cast<Shuttle>(model.getObject("supplyShuttle"));

    for (int i = 0; i < 9; i++) model.goCMD();
    Logger::getInstance().log("Shuttle position: " + std::to_string(shuttle->getPosition().getX()));
    Logger::getInstance().log("Zeta position: " + std::to_string(model.getObject("Zeta")->getPosition().getX()));
    Logger::getInstance().log("Shuttle position: " + std::to_string(shuttle->getPosition().getY()));
    Logger::getInstance().log("Zeta position: " + std::to_string(model.getObject("Zeta")->getPosition().getY()));
    assert(shuttle->getPosition() == model.getObject("Zeta")->getPosition());


    model.goCMD();
    Logger::getInstance().log("Shuttle position: " + std::to_string(shuttle->getPosition().getX()));
    Logger::getInstance().log("Zeta position: " + std::to_string(model.getObject("Zeta")->getPosition().getX()));
    Logger::getInstance().log("Shuttle position: " + std::to_string(shuttle->getPosition().getY()));
    Logger::getInstance().log("Zeta position: " + std::to_string(model.getObject("Zeta")->getPosition().getY()));
    assert(shuttle->getPosition() == model.getObject("Zeta")->getPosition());


    for (int i = 0; i < 10; i++) model.goCMD();
    Logger::getInstance().log("Shuttle position: " + std::to_string(shuttle->getPosition().getX()));
    Logger::getInstance().log("DS position: " + std::to_string(model.getObject("DS")->getPosition().getX()));
    assert(shuttle->getPosition() == model.getObject("DS")->getPosition());


    model.goCMD();
    Logger::getInstance().log("Shuttle position: " + std::to_string(shuttle->getPosition().getX()));
    Logger::getInstance().log("DS position: " + std::to_string(model.getObject("DS")->getPosition().getX()));
    assert(shuttle->getPosition() == model.getObject("DS")->getPosition());

}

void ModelTester::initializeSitesToTest(){
 //station, Yavin, (6.00, 8.00), 100, 5
//station, Rakatan, (10.00, 20.00), 20, 3
//station, Arcanum, (30.00, 0.00), 50, 4
//station, Claw, (20.00, 20.00), 10, 2
//station, Facility729D, (10.00, 10.00), 2, 3
//station, Drydock4, (0.00, 30.00), 6, 3
//fortress, DS, (40.00, 10.00), 100000, 0

    model.clearAllStationsAndFortresses();
    model.addSite({COMMAND_STATION, "Yavin", "6.00", "8.00", "100", "5"});
    model.addSite({COMMAND_STATION, "Rakatan", "10.00", "20.00", "20", "3"});
    model.addSite({COMMAND_STATION, "Arcanum", "30.00", "0.00", "50", "4"});
    model.addSite({COMMAND_STATION, "Claw", "20.00", "20.00", "10", "2"});
    model.addSite({COMMAND_STATION, "Facility729D", "10.00", "10.00", "2", "3"});
    model.addSite({COMMAND_STATION, "Drydock4", "0.00", "30.00", "6", "3"});
    model.defaultSite();



}



