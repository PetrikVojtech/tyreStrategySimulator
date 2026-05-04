#pragma once

#include <string>

#include "trackEnvironment.h"

class ITireCompound
{
public:
    virtual ~ITireCompound() = default;

    virtual std::string getName() = 0;
    virtual float getWear() = 0;
    virtual float calculateGrip(int lapsCompleted) = 0; // "= 0" -> pure virtual
    virtual void printStatus() = 0;
};