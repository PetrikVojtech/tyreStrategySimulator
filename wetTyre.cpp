#include "wetTyre.h"

#include "trackEnvironment.h"

WetTyre::WetTyre()
{
    this->compoundName = "Wet";
    this->currentWear = 0.0f;
    this->waterDisplacementRate = 70.0f;
}

float WetTyre::calculateGrip(int /* lapsCompleted */)
{
    float currentWetness = TrackEnvironment::getInstance().getCurrentWetness();
    int rainIntensity = TrackEnvironment::getInstance().getRainIntensity();
    float currentTemp = TrackEnvironment::getInstance().getTrackTemp();
    float wearThisLap = 0.02f;

    if (currentWetness >= 0.0f && currentWetness < 0.1f && rainIntensity == 0)
    {
        wearThisLap += 0.11f;
        if (currentTemp >= 30.0f)
        {
            wearThisLap += 0.05f;
        }
    }
    else if (currentWetness >= 0.1f && currentWetness < 0.3f)
    {
        wearThisLap += 0.08f;
        if (currentTemp >= 30.0f)
        {
            wearThisLap += 0.02f;
        }
    }

    this->currentWear += wearThisLap;
    if (this->currentWear > 1.0f)
    {
        this->currentWear = 1.0f;
    }

    float currentGrip = 1.0f - this->currentWear;

    return currentGrip;
}

void WetTyre::printStatus()
{
    std::cout << "Current wear of " << this->compoundName << " tyre is -> " << this->currentWear * 100 << "%" << std::endl;
}
