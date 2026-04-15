#pragma once

#include <iostream>

#include "slickTyre.h"
#include "trackEnvironment.h"

class SoftCompound : public SlickTyre
{
private:
    float blisteringFactor;

public:
    SoftCompound();
    float calculateGrip(int lapsCompleted) override;
    void printStatus() override;
};