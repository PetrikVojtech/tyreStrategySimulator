#pragma once

#include <vector>
#include <cstdlib>

#include "raceCar.h"
#include "softCompound.h"
#include "hardCompound.h"
#include "wetTyre.h"

class EnduranceSimulation
{
private:
    std::vector<RaceCar *> grid;
    float currentRaceHours;
    float totalRaceHours;

public:
    EnduranceSimulation();
    ~EnduranceSimulation();
    void start24hRace();
};