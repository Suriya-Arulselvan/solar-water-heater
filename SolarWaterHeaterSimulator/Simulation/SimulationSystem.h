#pragma once
#include "simulation_forward.h"
#include "UnitOperation/UnitOperation.h"
#include "Stream/MassStream.h"
#include "Stream/EnergyStream.h"

namespace simulation {

/*
* Contains the topology of the system and holds the callback function to update the derivatives
* at every time step.  
* The class also holds the functions that performs mass balance and energy balance each unit operation
*/
class SimulationSystem
{
	std::vector<unitop::UniqueUnitOperation> m_unit_operations;

public:

	SimulationSystem() = default;

	SimulationSystem(const SimulationSystem& other)
	{
		*this = other;
	}

	SimulationSystem(SimulationSystem&& other) = default;

	SimulationSystem& operator=(const SimulationSystem& other);

	SimulationSystem& operator=(SimulationSystem&& other) = default;

	~SimulationSystem() = default;

	void addUnitOperation(unitop::UniqueUnitOperation&& unit_operation) { m_unit_operations.emplace_back(std::move(unit_operation)); }

	void addUnitOperation(const unitop::UniqueUnitOperation& unit_operation)
	{
		if(unit_operation)
			m_unit_operations.emplace_back(unit_operation->clone());
	}                        

	//Callback function to update the derivates every time step
	void operator()(const state_type& x, state_type& dxdt, const double t);

	//Performs mass and energy balance after completion of each time step
	void massAndEnergyBalance(const double current_time);

	//Transfers current state values back to the unit operations and associated streams
	void transferValuesFromSolverToSimulation(const state_type& inout);

	//Returns the initial values of the variables being solved by ode solver
	state_type initialize();

	//Output the column headers
	void outputColumnHeaders() const;

	//Outputs current values of states in the system
	void outputCurrentConditions(double time) const;
};

}//namespace simulation