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
    float raceDurationSeconds = this->totalRaceHours * 3600.0f;
    this->currentRaceHours = 0.0f;

    bool isAnyoneRacing = true;

    int lap = 1;

    std::vector<RaceCar *> standings = this->grid;

    while (isAnyoneRacing && this->currentRaceHours < this->totalRaceHours)
    {
        isAnyoneRacing = false;
        bool headerPrinted = false;
        float bestTime = 9999.0f;

        TrackEnvironment::getInstance().updateWeather();
        float currentWetness = TrackEnvironment::getInstance().getCurrentWetness();
        bool isNight = TrackEnvironment::getInstance().checkIsNight();
        int rainIntensity = TrackEnvironment::getInstance().getRainIntensity();
        int remainingRainLaps = TrackEnvironment::getInstance().getRemainingRainLaps();
        // team can never be 100% sure of how many laps will be raining
        remainingRainLaps += rand() % 5;
        remainingRainLaps -= rand() % 5;

        float currentTrackTmp = TrackEnvironment::getInstance().getTrackTemp();

        for (RaceCar *car : this->grid)
        {

            if (!car->getIsDNF() && car->getTotalRaceTime() < raceDurationSeconds)
            {
                float time = car->completeLap();
                isAnyoneRacing = true;

                if (!headerPrinted)
                {
                    if (isNight)
                        std::cout << "---------- LAP " << lap << ": Night | Track Tmp - " << currentTrackTmp << " | Wetness: " << currentWetness << " | Rain Intenstiy: " << rainIntensity << " ----------" << std::endl;
                    else
                        std::cout << "---------- LAP " << lap << ":  Day  | Track Tmp - " << currentTrackTmp << " | Wetness: " << currentWetness << " | Rain Intenstiy: " << rainIntensity << " ----------" << std::endl;
                    headerPrinted = true;
                }

                if (time < bestTime)
                    bestTime = time;

                // pitstops logic

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
                    else if (currentWetness >= 0.3f && remainingRainLaps > 5 && car->getCurrentTyres()->getName() != "Wet")
                    {
                        car->executePitstop(75.0f - currentFuel, new WetTyre());
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
                        if (currentWetness >= 0.3f && car->getCurrentTyres()->getName() != "Wet")
                        {
                            // emergency pitstop - wet
                            car->executePitstop(fuelCapacity - currentFuel, new WetTyre());
                        }
                        else if (currentWetness < 0.3f && car->getCurrentTyres()->getName() == "Wet")
                        {
                            // emergency pitstop - slick
                            if (isNight)
                            {
                                car->executePitstop(fuelCapacity - currentFuel, new SoftCompound());
                            }
                            else
                            {
                                car->executePitstop(fuelCapacity - currentFuel, new HardCompound());
                            }
                        }
                        else if (currentFuel <= fuelCapacity * 0.15f)
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
                            } // pitstop wet
                            else if (car->getCurrentTyres()->getName() == "Wet")
                            {
                                if (currentStintLaps >= 35 || tyreWear > 0.40f)
                                {
                                    car->executePitstop(fuelCapacity - currentFuel, new WetTyre());
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

        std::sort(standings.begin(), standings.end(), [](RaceCar *a, RaceCar *b)
                  {
            if (a->getLapsCompleted() != b->getLapsCompleted())
            {
                return a->getLapsCompleted() > b->getLapsCompleted(); 
            }
            return a->getTotalRaceTime() < b->getTotalRaceTime(); });

        this->currentRaceHours += bestTime / 3600.0f;
        TrackEnvironment::getInstance().advanceTime(bestTime / 3600.0f);

        lap++;
    }

    std::cout
        << "----- THE 24 HOURS OF LE MANS HAS ENDED -----" << std::endl
        << std::endl;

    std::cout << "--- STANDINGS ---" << std::endl;
    int i = 1;
    for (RaceCar *car : standings)
    {
        std::cout << i << ". " << car->getTeamName() << " | Laps Completed: " << car->getLapsCompleted() << " | Total Time: " << std::fixed << std::setprecision(3) << car->getTotalRaceTime() << "s" << std::endl;
        i++;
    }
}