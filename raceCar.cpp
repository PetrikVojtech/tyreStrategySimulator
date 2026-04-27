#include "raceCar.h"

RaceCar::RaceCar(std::string teamName, float fuelTankCapacity, ITyreCompound *firstSetOfTyres)
{
    this->teamName = teamName;
    this->fuelTankCapacity = fuelTankCapacity;
    this->currentFuel = this->fuelTankCapacity;
    this->currentStintLaps = 0;
    this->currentTyres = firstSetOfTyres;
    // usedTyres is automatically initialized as empty by vectors default constructor
    this->isDNF = false;
    this->totalRaceTime = 0.0f;
}

RaceCar::~RaceCar()
{
    delete this->currentTyres;

    for (ITyreCompound *tyre : this->usedTyres) // foreach
    {
        delete tyre;
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

ITyreCompound *RaceCar::getCurrentTyres()
{
    return this->currentTyres;
}

int RaceCar::getTyreUsageCount(std::string tyreName)
{
    int count = 0;

    if (this->currentTyres != nullptr && this->currentTyres->getName() == tyreName)
    {
        count++;
    }
    for (ITyreCompound *t : this->usedTyres)
    {
        if (t != nullptr && t->getName() == tyreName)
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
    if (this->isDNF)
        return 0.0f;

    this->lapsCompleted++;
    // room for error
    int rng = rand() % 1000 + 1;
    if (rng == 1)
    {
        this->isDNF = true;
        std::cout << "CRITICAL FAILURE: " << this->teamName << " has suffered a catastrofic tyre blowout and is OUT of the race!" << std::endl;
        return 0.0f;
    }

    // simulate Le Mans lap
    float currentGrip = this->currentTyres->calculateGrip(this->currentStintLaps);

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
