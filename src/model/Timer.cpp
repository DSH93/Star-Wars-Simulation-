//
// Created by Dor Shukrun on 29/08/2024.
//


#include "model/Timer.h"

int Timer::currentTick = 0;
int Timer::tickInterval = 1;

void Timer::initialize(int interval) {
    currentTick = 0;
    tickInterval = interval;
}

int Timer::getCurrentTick() {
    return currentTick;
}

void Timer::advanceTick() {
    currentTick += tickInterval;
}

void Timer::setTickInterval(int interval) {
    tickInterval = interval;
}
