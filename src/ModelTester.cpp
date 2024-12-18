//
// Created by Dor Shukrun on 2/12/2024
//

#include "ModelTester.h"

ModelTester::ModelTester() : model(Model::getInstance()) {}

void ModelTester::runAllTests() {
    Logger::getInstance().log("Starting all tests...");

    testStations();
    testAdmirals();
    testCommanders();
    testMidshipmen();
    testFalcons();
    testDestroyers();
    testBombers();
    testShuttles();
    testCommands();
    testAttacks();

    Logger::getInstance().log("All tests completed successfully.");
}

void ModelTester::testStations() {
    Logger::getInstance().log("Testing station creation...");
    model.addSite({COMMAND_STATION, "Alpha", "20.00", "20.00", "50000", "10"});
    model.addSite({COMMAND_STATION, "Beta", "30.00", "30.00", "60000", "15"});
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
    model.create({COMMAND_CREATE, "falcon", "F2", "56.00", "56.0001"});
    model.create({COMMAND_CREATE, "falcon", "F3", "56.0001", "56.0001"});
    model.create({COMMAND_CREATE, "falcon", "F4", "56.0001", "56.00"});
    model.create({COMMAND_CREATE, "falcon", "F1", "30.00", "15.00"});
    model.create({COMMAND_CREATE, "falcon", "Millennium", "42.00", "42.00"});
}

void ModelTester::testDestroyers() {
    Logger::getInstance().log("Testing destroyer creation...");
    model.create({COMMAND_CREATE, "destroyer", "T1", "Thrawn", "50.00", "20.00"});
    model.create({COMMAND_CREATE, "destroyer", "T0", "Tarkin", "20.00", "10.00"});




}

void ModelTester::testBombers() {
    Logger::getInstance().log("Testing bomber creation...");
    model.create({COMMAND_CREATE, "bomber", "B1", "Piett", "10.00", "25.00"});
    model.create({COMMAND_CREATE, "bomber", "B2", "Ozzel", "30.00", "40.00"});



    model.positionCMD({"B1", COMMAND_POSITION, "20", "25"});
    model.destinationCMD({"B2", COMMAND_DESTINATION, "DS"});

    for (int i = 0; i < 10; i++) {
        model.goCMD();
    }
    model.statusCMD();
    // B1 should be at (20, 25)



}

void ModelTester::testShuttles() {
    Logger::getInstance().log("Testing shuttle creation...");
    model.create({COMMAND_CREATE, "shuttle", "GX", "Peter", "38.00", "6.00"});
    model.create({COMMAND_CREATE, "shuttle", "GY", "Ackbar", "5.00", "5.00"});
    model.create({COMMAND_CREATE, "shuttle", "GZ", "Flavius", "56.00", "56.00"});

    model.SupplyCMD({"GY", COMMAND_START_SUPPLY, "Alpha", "DS"});
    model.SupplyCMD({"GX", COMMAND_START_SUPPLY, "Yavin", "DS"});

}

void ModelTester::testCommands() {
    Logger::getInstance().log("Testing commands execution...");
    model.shootCMD({"T0", COMMAND_SHOOT, "42.00", "42.00"});
    model.courseCMD({"T0", COMMAND_COURSE, "0"});
    for (int i = 0; i < 4; i++) {
        model.goCMD();
    }

    model.courseCMD({"T0", COMMAND_COURSE, "180"});
    for (int i = 0; i < 8; i++) {
        model.goCMD();
    }

    model.courseCMD({"T0", COMMAND_COURSE, "90"});

    model.stopCMD({"T0", COMMAND_STOP});
    model.positionCMD({"F1", COMMAND_POSITION, "30.00", "15.00"});
}

void ModelTester::testAttacks() {
    Logger::getInstance().log("Testing attacks...");
    model.attackCMD({"F1", COMMAND_ATTACK, "GZ"}); // -1
    model.attackCMD({"F2", COMMAND_ATTACK, "GZ"}); // -2
    model.attackCMD({"F3", COMMAND_ATTACK, "GZ"}); // -3
    model.attackCMD({"F4", COMMAND_ATTACK, "GZ"}); // -4
    model.attackCMD({"Millennium", COMMAND_ATTACK, "GZ"}); // -5

    model.goCMD();

    model.attackCMD({"F1", COMMAND_ATTACK, "GZ"}); // -6
    model.attackCMD({"F2", COMMAND_ATTACK, "GZ"}); // -7
    model.attackCMD({"F3", COMMAND_ATTACK, "GZ"}); // -8
    model.attackCMD({"F4", COMMAND_ATTACK, "GZ"}); // -9
    model.attackCMD({"Millennium", COMMAND_ATTACK, "GZ"}); // -10 Destroyed

    model.goCMD();
    model.attackCMD({"F1", COMMAND_ATTACK, "GZ"}); // Checks -11 or destroyed
    model.SupplyCMD({"GZ", COMMAND_START_SUPPLY, "Beta", "DS"}); // Checks that thr shuttle cannot start a new mission


}
