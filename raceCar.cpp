#include "raceCar.h"

RaceCar::RaceCar(std::string teamName, float fuelTankCapacity, ITireCompound *firstSetOfTires)
{
    this->teamName = teamName;
    this->fuelTankCapacity = fuelTankCapacity;
    this->currentFuel = this->fuelTankCapacity;
    this->currentStintLaps = 0;
    this->currentTires = firstSetOfTires;
    // usedTires is automatically initialized as empty by vectors default constructor
    this->isDNF = false;
    this->totalRaceTime = 0.0f;
}

RaceCar::~RaceCar()
{
    delete this->currentTires;

    for (ITireCompound *t : this->usedTires) // foreach
    {
        delete t;
    }
}

std::string RaceCar::getTeamName()
{
    return this->teamName;
}

float RaceCar::getFuelTankCapacity()
{
    return this->fuelTankCapacity;
}

float RaceCar::getCurrentFuel()
{
    return this->currentFuel;
}

int RaceCar::getCurrentStintLaps()
{
    return this->currentStintLaps;
}

ITireCompound *RaceCar::getCurrentTires()
{
    return this->currentTires;
}

int RaceCar::getTireUsageCount(std::string tireName)
{
    int count = 0;
    if (this->currentTires != nullptr && this->currentTires->getName() == tireName)
    {
        count++;
    }

    for (ITireCompound *t : this->usedTires)
    {
        if (t != nullptr && t->getName() == tireName)
        {
            count++;
        }
    }

    return count;
}

bool RaceCar::getIsDNF()
{
    return this->isDNF;
}

int RaceCar::getLapsCompleted()
{
    return this->lapsCompleted;
}

float RaceCar::getTotalRaceTime()
{
    return this->totalRaceTime;
}

void RaceCar::executePitstop(float fuelAmount)
{
    this->currentFuel += fuelAmount;
    if (this->currentFuel > this->fuelTankCapacity)
        this->currentFuel = this->fuelTankCapacity;

    std::cout << this->teamName << " pits for fuel only (Double-stint)." << std::endl;
}

void RaceCar::executePitstop(float fuelAmount, ITireCompound *newTires)
{
    this->currentFuel += fuelAmount;
    if (this->currentFuel > this->fuelTankCapacity)
        this->currentFuel = this->fuelTankCapacity;

    this->usedTires.push_back(this->currentTires);
    this->currentTires = newTires;

    this->currentStintLaps = 0;

    std::cout << this->teamName << " pits for fuel and fresh " << newTires->getName() << " tires." << std::endl;
}

float RaceCar::completeLap()
{
    if (this->isDNF)
        return 0.0f;

    this->lapsCompleted++;
    // room for error
    int rng = rand() % 1000 + 1;
    if (rng == 1)
    {
        this->isDNF = true;
        std::cout << "CRITICAL FAILURE: " << this->teamName << " has suffered a catastrofic tire blowout and is OUT of the race!" << std::endl;
        return 0.0f;
    }

    // simulate Le Mans lap
    float currentGrip = this->currentTires->calculateGrip(this->currentStintLaps);

    float lapTime = 210.0f + ((1.0f - currentGrip) * 20.0f);

    // "human factor"
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(0.0f, 2.5f);

    lapTime += distrib(gen);

    this->currentFuel -= 6.5f;
    if (this->currentFuel < 0.0f)
        lapTime += 999.0f;
    this->currentStintLaps++;

    this->totalRaceTime += lapTime;

    // returning lap time
    return lapTime;
}
