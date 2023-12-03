// SolarWaterHeaterSimulator.cpp : Defines the entry point for the application.

#include "SolarWaterHeaterSimulator.h"
#include "Simulation/Simulation.h"

using namespace std;
using namespace simulation;

int main(int argc, char** argv)
{
	cout << "Simulating Solar Water Heater System" << endl;

	Simulation simulation;
	simulation.createExampleSimulationSystem();

	simulation.solve();

	cin.get();
	return 0;
}
