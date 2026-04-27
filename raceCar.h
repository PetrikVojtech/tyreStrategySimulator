#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <random>

#include "iTyreCompound.h"

class RaceCar
{
private:
    std::string teamName;
    float fuelTankCapacity; // no BoP for now
    float currentFuel;
    int currentStintLaps; // for one set of tyres
    ITyreCompound *currentTyres;
    std::vector<ITyreCompound *> usedTyres;
    bool isDNF;
    int lapsCompleted;
    float totalRaceTime;

public:
    RaceCar(std::string teamName, float fuelTankCapacity, ITyreCompound *firstSetOfTyres);
    ~RaceCar();

    std::string getTeamName();
    float getFuelTankCapacity();
    float getCurrentFuel();
    int getCurrentStintLaps();
    ITyreCompound *getCurrentTyres();
    int getTyreUsageCount(std::string tyreName);
    bool getIsDNF();
    int getLapsCompleted();
    float getTotalRaceTime();

    void executePitstop(float fuelAmount);
    void executePitstop(float fuelAmount, ITyreCompound *newTyres);
    float completeLap();
};