#include "SimulationSystem.h"

using namespace std;
using namespace unitop;

namespace simulation {

SimulationSystem& SimulationSystem::operator=(const SimulationSystem& other)
{
	m_unit_operations.clear();
	m_unit_operations.reserve(other.m_unit_operations.size());

	for (const UniqueUnitOperation& unit_operation : other.m_unit_operations)
	{
		if (unit_operation)
			m_unit_operations.emplace_back(unit_operation->clone());
	}

	return *this;
}

void SimulationSystem::operator()(const state_type& x, state_type& dxdt, const double t)
{
	int count = 0;

	for (const auto& unit_op : m_unit_operations)
	{
		for (const auto& stream : unit_op->inletMassStreams())
		{
			dxdt[count++] = stream->temperature().derivative();
			dxdt[count++] = stream->volumetricFlowRate().derivative();
		}

		for (const auto& stream : unit_op->outletMassStreams())
		{
			dxdt[count++] = stream->temperature().derivative();
			dxdt[count++] = stream->volumetricFlowRate().derivative();
		}
	}
}

void SimulationSystem::massAndEnergyBalance(const double current_time)
{
	for (const auto& unit_op : m_unit_operations)
	{
		unit_op->calculateMassBalance(current_time);
		unit_op->calculateEnergyBalance(current_time);
	}
}

void SimulationSystem::transferValuesFromSolverToSimulation(const state_type& inout)
{
	int count = 0;
	for (auto& unit_op : m_unit_operations)
	{
		for (auto& stream : unit_op->inletMassStreams())
		{
			stream->temperature().setValue(inout[count++]);
			stream->volumetricFlowRate().setValue(inout[count++]);
		}

		for (auto& stream : unit_op->outletMassStreams())
		{
			stream->temperature().setValue(inout[count++]);
			stream->volumetricFlowRate().setValue(inout[count++]);
		}
	}
}

state_type SimulationSystem::initialize()
{
	state_type init_conditions;
	for (auto& unit_op : m_unit_operations)
	{
		state_type unit_op_initial_conditions = unit_op->initialConditions();
		init_conditions.insert(init_conditions.end(), unit_op_initial_conditions.begin(), unit_op_initial_conditions.end());
	}

	return init_conditions;
}

void SimulationSystem::outputColumnHeaders() const
{
	cout << "Time\t";
	for (const auto& unit_op : m_unit_operations)
	{
		for (const auto& stream : unit_op->inletMassStreams())
		{
			cout << stream->name().c_str() << "Temperature\t";
			cout << stream->name().c_str() << "Flow\t";
		}
			

		for (const auto& stream : unit_op->inletEnergyStreams())
			cout << stream->name().c_str() << "EnergyFlow\t";

		for (const auto& stream : unit_op->outletMassStreams())
		{
			cout << stream->name().c_str() << "Temperature\t";
			cout << stream->name().c_str() << "Flow\t";
		}

		for (const auto& stream : unit_op->outletEnergyStreams())
			cout << stream->name().c_str() << "EnergyFlow\t";
	}

	cout << endl;
}
void SimulationSystem::outputCurrentConditions(double time) const
{
	cout << time << "\t";
	for (const auto& unit_op : m_unit_operations)
	{
		for (const auto& stream : unit_op->inletMassStreams())
		{
			cout << stream->temperature().value() << "\t";
			cout << stream->volumetricFlowRate().value() << "\t";
		}

		for (const auto& stream : unit_op->inletEnergyStreams())
			cout << stream->heatFlow().value() << "\t";

		for (const auto& stream : unit_op->outletMassStreams())
		{
			cout << stream->temperature().value() << "\t";
			cout << stream->volumetricFlowRate().value() << "\t";
		}

		for (const auto& stream : unit_op->outletEnergyStreams())
			cout << stream->heatFlow().value() << "\t";

	}
	cout << endl;
}


} //namespace simulation