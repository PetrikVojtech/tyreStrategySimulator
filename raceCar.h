#pragma once

#include <string>
#include <vector>
#include <iostream>

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

public:
    RaceCar(std::string teamName, float fuelTankCapacity, ITyreCompound *firstSetOfTyres);
    ~RaceCar();
    void executePitstop(float fuelAmount);
    void executePitstop(float fuelAmount, ITyreCompound *newTyres);
    float completeLap();
};