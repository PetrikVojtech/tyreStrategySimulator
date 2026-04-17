#include "raceCar.h"

RaceCar::RaceCar(std::string teamName, float fuelTankCapacity, ITyreCompound *firstSetOfTyres)
{
    this->teamName = teamName;
    this->fuelTankCapacity = fuelTankCapacity;
    this->currentFuel = this->fuelTankCapacity;
    this->currentStintLaps = 0;
    this->currentTyres = firstSetOfTyres;
    // usedTyres is automatically initialized as empty by vectors default constructor
}

RaceCar::~RaceCar()
{
    delete this->currentTyres;

    for (ITyreCompound *tyre : this->usedTyres) // foreach
    {
        delete tyre;
    }
}

void RaceCar::executePitstop(float fuelAmount)
{
    this->currentFuel += fuelAmount;
    if (this->currentFuel > this->fuelTankCapacity)
        this->currentFuel = this->fuelTankCapacity;

    std::cout << this->teamName << " pits for fuel only (Double-stint)." << std::endl;
}

void RaceCar::executePitstop(float fuelAmount, ITyreCompound *newTyres)
{
    this->currentFuel += fuelAmount;
    if (this->currentFuel > this->fuelTankCapacity)
        this->currentFuel = this->fuelTankCapacity;

    this->usedTyres.push_back(this->currentTyres);
    this->currentTyres = newTyres;

    this->currentStintLaps = 0;

    std::cout << this->teamName << " pits for fuel and fresh " << newTyres->getName() << " tyres." << std::endl;
}

float RaceCar::completeLap()
{
    // simulate Le Mans lap
    float currentGrip = this->currentTyres->calculateGrip(this->currentStintLaps);

    float lapTime = 210.0f + ((1.0f - currentGrip) * 20.0f);

    this->currentFuel -= 6.5f;
    if (this->currentFuel < 0.0f)
        lapTime += 999.0f;
    this->currentStintLaps++;

    // returning lap time
    return lapTime;
}
