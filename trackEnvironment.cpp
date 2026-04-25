#include "trackEnvironment.h"

TrackEnvironment::TrackEnvironment()
{
    this->trackTemperature = 35.0f;
    this->timeOfDayHours = 16.0f;
    this->isNightTime = false;
    this->currentWetness = 0.0f;
    this->rainIntensity = 0;
    this->remainingRainLaps = 0;
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

float TrackEnvironment::getCurrentWetness()
{
    return this->currentWetness;
}

int TrackEnvironment::getRainIntensity()
{
    return this->rainIntensity;
}

int TrackEnvironment::getRemainingRainLaps()
{
    return this->remainingRainLaps;
}

void TrackEnvironment::setRainLaps(int minRainLaps, int maxRainLaps)
{
    // Initialize a random number generator
    std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(minRainLaps, maxRainLaps);

    // Generate random number in the range [min, max]
    int randomValue = distrib(gen);

    this->remainingRainLaps = randomValue;
}

void TrackEnvironment::updateWeather()
{
    if (this->rainIntensity > 0)
    {
        // raining already
        this->remainingRainLaps--;
        this->currentWetness += 0.05f * this->rainIntensity;
        if (this->currentWetness > 1.0f)
            this->currentWetness = 1.0f;
        if (this->remainingRainLaps == 0)
            this->rainIntensity = 0;
    }
    else
    {
        int rng = rand() % 1000 + 1;
        if (rng == 500)
        {
            // is raining
            rng = rand() % 3 + 1;
            this->rainIntensity = rng;
            if (rng == 1)
            {
                setRainLaps(2, 6);
            }
            else if (rng == 2)
            {
                setRainLaps(7, 15);
            }
            else if (rng == 3)
            {
                setRainLaps(16, 25);
            }
        }
        else
        {
            this->rainIntensity = 0;
            this->remainingRainLaps = 0;
            if (this->currentWetness > 0.0f)
            {
                if (checkIsNight())
                {
                    this->currentWetness -= 0.02f;
                    if (this->currentWetness < 0.0f)
                    {
                        this->currentWetness = 0.0f;
                    }
                }
                else
                {
                    this->currentWetness -= 0.04f;
                    if (this->currentWetness < 0.0f)
                    {
                        this->currentWetness = 0.0f;
                    }
                }
            }
        }
    }
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