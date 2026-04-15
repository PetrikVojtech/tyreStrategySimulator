#pragma once

#include <string>

#include "trackEnvironment.h"

class ITyreCompound
{
protected:
    float currentWear;
    std::string compoundName;

public:
    virtual ~ITyreCompound() = default;

    virtual float calculateGrip(int lapsCompleted) = 0;
    virtual void printStatus() = 0;

    std::string getName()
    {
        return this->compoundName;
    };
};