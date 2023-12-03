#include "Simulation.h"

using namespace std;
using namespace unitop;
using namespace stream;
using namespace boost::numeric::odeint;

namespace simulation {

void Simulation::solve()
{
	if (!m_simulation_system)
		return;

	// ----  Steppers definition  ----
	// Basic stepper:
	// follows given timestep size "dt"
	typedef runge_kutta4<state_type> rk4;

	// Error stepper, used to create the controlled stepper
	typedef runge_kutta_cash_karp54< state_type > rkck54;

	std::cout << "==========  Test Simulation  =======" << std::endl;

	//Integration parameters
	double init_time = 0.0;
	double end_time = 10.0;
	double time_step = 0.1;

	size_t steps = (end_time - init_time) / time_step;

	m_simulation_system->initialize();

	rk4 stepper;
	state_type inout = m_simulation_system->initialize();

	m_simulation_system->outputColumnHeaders();

	for (size_t step = 0; step < steps; step++)
	{
		double current_time = init_time + step * time_step;
		stepper.do_step(*m_simulation_system, inout, init_time, time_step);
		
		m_simulation_system->transferValuesFromSolverToSimulation(inout);
		m_simulation_system->massAndEnergyBalance(current_time);

		m_simulation_system->outputCurrentConditions(current_time);
	}
}

void Simulation::createExampleSimulationSystem()
{
	m_simulation_system = make_unique<SimulationSystem>();

	//Storage Tank
	UniqueUnitOperation tank = UnitOperationFactory::createUnitOperation(UnitOperationType::StorageTank);
	tank->setName("Tank");

	//Inlet and Outlet Mass Stream connections to Storage Tank
	SharedMassStream tank_inlet_stream = make_shared<MassStream>("TankInlet");
	SharedMassStream tank_outlet_stream = make_shared<MassStream>("TankOutlet");

	tank_inlet_stream->setVolumetricFlowRate(5.0);
	tank_inlet_stream->setTemperature(293.0);
	tank_outlet_stream->setVolumetricFlowRate(5.0);
	tank_outlet_stream->setTemperature(293.0);

	tank->addInletMassStream(tank_inlet_stream);
	tank->addOutletMassStream(tank_outlet_stream);

	//Supply and Demand Mass Stream connections to Storage Tank (not used in the program currently)
	SharedMassStream tank_supply_stream = make_shared<MassStream>("TankSupply");
	SharedMassStream tank_demand_stream = make_shared<MassStream>("TankDemand");

	tank_supply_stream->setVolumetricFlowRate(1.0);
	tank_demand_stream->setTemperature(293.0);
	tank_supply_stream->setVolumetricFlowRate(1.0);
	tank_demand_stream->setTemperature(293.0);

	/*tank->addInletMassStream(tank_supply_stream);
	tank->addOutletMassStream(tank_demand_stream);*/

	//Solar Water Heater System
	UniqueUnitOperation solar_water_heater = UnitOperationFactory::createUnitOperation(UnitOperationType::SolarWaterHeater);
	solar_water_heater->setName("SolarWaterHeater");

	//Inlet heat collected by solar collector
	SharedEnergyStream solar_energy_stream = make_shared<EnergyStream>("HeatFromSolarCollector");
	solar_energy_stream->setHeatFlow(50.0);

	solar_water_heater->addInletEnergyStream(move(solar_energy_stream));

	//Oulet Mass Stream connection to the heater
	SharedMassStream solar_water_heater_outlet_stream = make_shared<stream::MassStream>("SWHOutlet");
	solar_water_heater_outlet_stream->setVolumetricFlowRate(5.0);
	solar_water_heater_outlet_stream->setTemperature(293.0);

	//Inlet to solar water heater is the outlet from storage tank
	solar_water_heater->addInletMassStream(tank_outlet_stream);
	solar_water_heater->addOutletMassStream(solar_water_heater_outlet_stream);

	//Pump unit operation
	UniqueUnitOperation pump = UnitOperationFactory::createUnitOperation(UnitOperationType::Pump);
	pump->setName("Pump");
	SharedEnergyStream pump_energy_stream = make_shared<EnergyStream>("PumpEnergyIn");
	pump_energy_stream->setHeatFlow(10.0);

	//Inlet and outlet Mass stream and inlet energy stream connection to pump
	pump->addInletEnergyStream(pump_energy_stream);
	pump->addInletMassStream(solar_water_heater_outlet_stream);
	pump->addOutletMassStream(tank_inlet_stream);

	//Add the unit operations to the simulation system
	m_simulation_system->addUnitOperation(tank);
	m_simulation_system->addUnitOperation(pump);
	m_simulation_system->addUnitOperation(solar_water_heater);
}



} //namespace simulation