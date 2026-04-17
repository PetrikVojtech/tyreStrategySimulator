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
}