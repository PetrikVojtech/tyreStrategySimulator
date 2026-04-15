#pragma once

#include <iostream>

#include "slickTyre.h"
#include "trackEnvironment.h"

class HardCompound : public SlickTyre
{
private:
    float warmUpTime;

public:
    HardCompound();
    float calculateGrip(int lapsCompleted) override;
    void printStatus() override;
};