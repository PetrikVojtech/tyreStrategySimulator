#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <random>

#include "iTireCompound.h"

class RaceCar
{
private:
    std::string teamName;
    float fuelTankCapacity; // no BoP for now
    float currentFuel;
    int currentStintLaps; // for one set of tires
    ITireCompound *currentTires;
    std::vector<ITireCompound *> usedTires;
    bool isDNF;
    int lapsCompleted;
    float totalRaceTime;

public:
    RaceCar(std::string teamName, float fuelTankCapacity, ITireCompound *firstSetOfTires);
    ~RaceCar();

    std::string getTeamName();
    float getFuelTankCapacity();
    float getCurrentFuel();
    int getCurrentStintLaps();
    ITireCompound *getCurrentTires();
    int getTireUsageCount(std::string tireName);
    bool getIsDNF();
    int getLapsCompleted();
    float getTotalRaceTime();

    void executePitstop(float fuelAmount);
    void executePitstop(float fuelAmount, ITireCompound *newTires);
    float completeLap();
};