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
    static void initialize(int interval);
    static int getCurrentTick();
    static void advanceTick();
    static void setTickInterval(int interval);
};

#endif // TIMER_H



