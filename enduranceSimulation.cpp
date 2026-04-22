#include "enduranceSimulation.h"

EnduranceSimulation::EnduranceSimulation()
{
    int fuelTank = rand() % 11 + 85;
    this->grid.push_back(new RaceCar("Toyota Racing #7", fuelTank, new HardCompound()));
    this->grid.push_back(new RaceCar("Toyota Racing #8", fuelTank, new HardCompound()));

    fuelTank = rand() % 11 + 85;
    this->grid.push_back(new RaceCar("Ferrari AF Corse #50", fuelTank, new SoftCompound()));
    this->grid.push_back(new RaceCar("Ferrari AF Corse #51", fuelTank, new SoftCompound()));
    this->grid.push_back(new RaceCar("AF Corse #83", fuelTank, new HardCompound()));

    fuelTank = rand() % 11 + 85;
    this->grid.push_back(new RaceCar("Cadillac Hertz Team JOTA #12", fuelTank, new SoftCompound()));
    this->grid.push_back(new RaceCar("Cadillac Hertz Team JOTA #38", fuelTank, new SoftCompound()));

    fuelTank = rand() % 11 + 85;
    this->grid.push_back(new RaceCar("BMW M Team WRT #15", fuelTank, new HardCompound()));
    this->grid.push_back(new RaceCar("BMW M Team WRT #20", fuelTank, new HardCompound()));

    fuelTank = rand() % 11 + 85;
    this->grid.push_back(new RaceCar("Aston Martin THOR Team #007", fuelTank, new SoftCompound()));
    this->grid.push_back(new RaceCar("Aston Martin THOR Team #009", fuelTank, new HardCompound()));

    fuelTank = rand() % 11 + 85;
    this->grid.push_back(new RaceCar("Genesis Magma Racing #17", fuelTank, new HardCompound()));
    this->grid.push_back(new RaceCar("Genesis Magma Racing #19", fuelTank, new SoftCompound()));

    fuelTank = rand() % 11 + 85;
    this->grid.push_back(new RaceCar("Alpine Endurance Team #35", fuelTank, new SoftCompound()));
    this->grid.push_back(new RaceCar("Alpine Endurance Team #36", fuelTank, new HardCompound()));

    fuelTank = rand() % 11 + 85;
    this->grid.push_back(new RaceCar("Peugeot TotalEnergies #93", fuelTank, new HardCompound()));
    this->grid.push_back(new RaceCar("Peugeot TotalEnergies #94", fuelTank, new HardCompound()));

    this->totalRaceHours = 24.0f;
}

EnduranceSimulation::~EnduranceSimulation()
{
    for (RaceCar *car : this->grid) // foreach
    {
        delete car;
    }
}

void EnduranceSimulation::start24hRace()
{
    std::cout << "----- THE 24 HOURS OF LE MANS HAS STARTED -----" << std::endl;
    this->currentRaceHours = 0.0f;

    int lap = 1;

    while (this->currentRaceHours < this->totalRaceHours)
    {
        std::cout << "---------- LAP " << lap << " ----------" << std::endl;

        float bestTime = 9999.0f;

        for (RaceCar *car : this->grid)
        {
            if (!car->getIsDNF())
            {
                float time = car->completeLap();
                if (time < bestTime)
                    bestTime = time;

                // pitstops logic
                bool isNight = TrackEnvironment::getInstance().checkIsNight();
                float tyreWear = car->getCurrentTyres()->getWear();
                int currentStintLaps = car->getCurrentStintLaps();
                float currentFuel = car->getCurrentFuel();
                float fuelCapacity = car->getFuelTankCapacity();

                // little time left -> splash and dash
                if (this->totalRaceHours - this->currentRaceHours < 0.5f)
                {
                    // fuel you need to have to finish in 30 mins
                    if (currentFuel <= fuelCapacity * 0.15f)
                    {
                        car->executePitstop(75.0f - currentFuel);
                    }
                }
                else
                {
                    // normal time
                    int rng = rand() % 1000 + 1;
                    if (rng == 265)
                    {
                        // error pitstop
                        car->executePitstop(fuelCapacity - currentFuel, new WetTyre());
                    }
                    else
                    {
                        // good pitstop
                        if (currentFuel <= fuelCapacity * 0.15f)
                        {
                            // pitstop soft
                            if (car->getCurrentTyres()->getName() == "Soft")
                            {
                                if (currentStintLaps >= 12 || tyreWear > 0.55f)
                                {
                                    if (isNight)
                                    {
                                        car->executePitstop(fuelCapacity - currentFuel, new SoftCompound());
                                    }
                                    else
                                    {
                                        car->executePitstop(fuelCapacity - currentFuel, new HardCompound());
                                    }
                                }
                                else
                                {
                                    car->executePitstop(fuelCapacity - currentFuel);
                                }
                            } // pitstop hard
                            else if (car->getCurrentTyres()->getName() == "Hard")
                            {
                                if (currentStintLaps >= 35 || tyreWear > 0.40f)
                                {
                                    if (isNight)
                                    {
                                        car->executePitstop(fuelCapacity - currentFuel, new SoftCompound());
                                    }
                                    else
                                    {
                                        car->executePitstop(fuelCapacity - currentFuel, new HardCompound());
                                    }
                                }
                                else
                                {
                                    car->executePitstop(fuelCapacity - currentFuel);
                                }
                            }
                        }
                    }
                }
            }
        }
        this->currentRaceHours += bestTime / 3600.0f;
        TrackEnvironment::getInstance().advanceTime(bestTime / 3600.0f);
        lap++;
    }
    std::cout << "----- THE 24 HOURS OF LE MANS HAS ENDED -----" << std::endl;
}