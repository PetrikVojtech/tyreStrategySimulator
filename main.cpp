#include <iostream>
#include <ctime>
#include <cstdlib>

#include "enduranceSimulation.h"

using namespace std;

int main()
{
    srand(time(NULL));

    EnduranceSimulation enduranceSimulation = EnduranceSimulation();

    enduranceSimulation.start24hRace();

    return 0;
}