#pragma once

#include <iostream>

#include "iTyreCompound.h"

class WetTyre : public ITyreCompound
{
private:
    float waterDisplacementRate;

public:
    WetTyre();
    float calculateGrip(int lapsCompleted) override;
    void printStatus() override;
};