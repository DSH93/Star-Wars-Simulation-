#ifndef TIMER_H
#define TIMER_H

#include "Constant.h"

/**
 * @class Timer
 * @brief Manages the simulation time, represented as ticks.
 *
 * Each tick represents a unit of time in the simulation (e.g., 1 Tick = 1 Hour).
 */
class Timer {
private:
    static int currentTick; ///< Current simulation tick.
    static int tickInterval; ///< Interval at which ticks advance.

public:
    /**
     * @brief Initializes the timer with a specific tick interval.
     *
     * @param interval The interval value for advancing time (default unit: hours).
     */
    static void initialize(int interval) {
        currentTick = INITIAL_TICK_VALUE;
        tickInterval = interval;
    }

    /**
     * @brief Retrieves the current tick value.
     *
     * @return The current tick as an integer.
     */
    static int getCurrentTick() {
        return currentTick;
    }

    /**
     * @brief Advances the simulation time by the tick interval.
     */
    static void advanceTick() {
        currentTick += tickInterval;
    }

};

// Initialize static members
inline int Timer::currentTick = INITIAL_TICK_VALUE;
inline int Timer::tickInterval = DEFAULT_TICK_INTERVAL;

#endif // TIMER_H
