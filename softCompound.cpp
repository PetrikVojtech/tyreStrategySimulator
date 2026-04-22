#include "softCompound.h"

SoftCompound::SoftCompound()
{
    this->compoundName = "Soft";
    this->currentWear = 0.0f;
    this->optimalTempWindow = 20.0f; // optimal track temp
    this->blisteringFactor = 0.3f;
}
float SoftCompound::calculateGrip(int /* lapsCompleted */)
{
    float currentTemp = TrackEnvironment::getInstance().getTrackTemp();
    float tempDiff = currentTemp - this->optimalTempWindow;
    float wearThisLap = 0.04;

    if (tempDiff > 5.0f)
    {
        float blisteringPenalty = tempDiff * this->blisteringFactor;
        wearThisLap += blisteringPenalty;
    }

    this->currentWear += wearThisLap;
    if (this->currentWear > 1.0f)
        this->currentWear = 1.0f;

    float currentGrip = 1.0f - this->currentWear;

    return currentGrip;
}

void SoftCompound::printStatus()
{
    std::cout << "Current wear of " << this->compoundName << " tyre is -> " << this->currentWear * 100 << "%" << std::endl;
}