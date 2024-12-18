//
// Created by Dor Shukrun on 2/12/2024
//


#ifndef MODELTESTER_H
#define MODELTESTER_H

#include "model/Model.h"
#include "Logger.h"

class ModelTester {
public:
    explicit ModelTester();
    void runAllTests();

private:
    Model& model;

    void testStations();
    void testAdmirals();
    void testCommanders();
    void testMidshipmen();
    void testFalcons();
    void testDestroyers();
    void testBombers();
    void testShuttles();
    void testCommands();
    void testAttacks();
};

#endif // MODELTESTER_H
