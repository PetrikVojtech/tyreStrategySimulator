#pragma once

#include <iostream>
#include "slickTire.h"
#include "trackEnvironment.h"

class HardCompound : public SlickTire
{
private:
    std::string compoundName;
    float currentWear;
    float warmUpTime;

public:
    HardCompound();
    std::string getName() override;
    virtual float getWear() override;
    float calculateGrip(int lapsCompleted) override;
    void printStatus() override;
};