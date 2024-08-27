//
// Created by Dor Shukrun on 24/08/2024.
//

#ifndef TIMER_H
#define TIMER_H

class Timer {
private:
    static int currentTick;
    static int tickInterval;

public:
    static void initialize(int interval) {
        currentTick = 0;
        tickInterval = interval;
    }


    static int getCurrentTick() {
        return currentTick;
    }


    static void advanceTick() {
        currentTick += tickInterval;
    }


    static void setTickInterval(int interval) {
        tickInterval = interval;
    }
};


int Timer::currentTick = 0;
int Timer::tickInterval = 1;

#endif // TIMER_H
