#include "trackEnvironment.h"

TrackEnvironment::TrackEnvironment()
{
    this->trackTemperature = 35.0f;
    this->timeOfDayHours = 16.0f;
    this->isNightTime = false;
}

TrackEnvironment &TrackEnvironment::getInstance()
{
    static TrackEnvironment instance;
    return instance;
}

float TrackEnvironment::getTrackTemp()
{
    return this->trackTemperature;
}

bool TrackEnvironment::checkIsNight()
{
    return this->isNightTime;
}

void TrackEnvironment::advanceTime(float hours)
{
    // 20.5 = 20:30 ...
    float nextTime = this->timeOfDayHours + hours;
    if (nextTime >= 24.00f)
    {
        nextTime -= 24.00f;
    }
    this->timeOfDayHours = nextTime;

    // day / night difference
    if (this->timeOfDayHours >= 20.0f || this->timeOfDayHours <= 6.0f)
    {
        this->isNightTime = true;
        this->trackTemperature = 15.0f;
    }
    else
    {
        this->isNightTime = false;
        this->trackTemperature = 35.0f;
    }
}