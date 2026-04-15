#include "hardCompound.h"

HardCompound::HardCompound()
{
    this->compoundName = "Hard";
    this->currentWear = 0.0f;
    this->optimalTempWindow = 40.0f;
    this->warmUpTime = 3.0f;
}

float HardCompound::calculateGrip(int lapsCompleted)
{
    float currentTemp = TrackEnvironment::getInstance().getTrackTemp();
    float tempDiff = currentTemp - this->optimalTempWindow;
    float wearThisLap = 0.01f;

    this->currentWear += wearThisLap;
    if (this->currentWear > 1.0f)
        this->currentWear = 1.0f;

    float currentGrip = 1.0f - this->currentWear;

    float requiredWarmUpTime = this->warmUpTime;
    if (tempDiff < -5.0f)
        requiredWarmUpTime += 2.0f;

    if (requiredWarmUpTime > lapsCompleted)
        currentGrip *= 0.7f;

    return currentGrip;
}

void HardCompound::printStatus()
{
    std::cout << "Current wear of " << this->compoundName << " tyre is -> " << this->currentWear * 100 << "%" << std::endl;
}
