#pragma once

#include <cstdlib>
#include <random>

class TrackEnvironment
{
private:
    float trackTemperature;
    float timeOfDayHours;
    bool isNightTime;
    float currentWetness;
    int rainIntensity;
    int remainingRainLaps;
    TrackEnvironment();

public:
    /* (&) toto je reference - dava programu garanci ze objekt
    neodkazuje do prazna narozdil od * */
    static TrackEnvironment &getInstance();

    float getTrackTemp();
    bool checkIsNight();
    float getCurrentWetness();
    int getRainIntensity();
    int getRemainingRainLaps();

    void setRainLaps(int minRainLaps, int maxRainLaps);
    void updateWeather();
    void advanceTime(float hours);
};