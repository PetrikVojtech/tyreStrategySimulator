#pragma once

#include "iTireCompound.h"

class WetTire : public ITireCompound
{
private:
    std::string compoundName;
    float currentWear;
    float waterDisplacementRate;

public:
    WetTire();
    std::string getName() override;
    virtual float getWear() override;
    float calculateGrip(int lapsCompleted) override;
    void printStatus() override;
};
