#pragma once
#include <boost/numeric/odeint.hpp>
#include "UnitOperation/UnitOperationFactory.h"
#include "simulation_forward.h"
#include "SimulationSystem.h"

using namespace std;
using namespace boost::numeric::odeint;

namespace simulation {

class SimulationSystem;

/*
* Contains the pointer to the simulation system that the odeint solver uses for callbacks
*/
class Simulation
{
	std::unique_ptr<SimulationSystem> m_simulation_system;

public:

	void createExampleSimulationSystem();

	void solve();
};

} //namespace simulation
