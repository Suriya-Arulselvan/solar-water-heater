
#include "UnitOperation.h"

using namespace std;

namespace unitop
{

vector<double> UnitOperation::initialConditions() const
{
	vector<double> initial_conditions;

	for (const auto& stream : m_inlet_mass_streams)
		initial_conditions.emplace_back(stream->temperature().value());

	for (const auto& stream : m_inlet_mass_streams)
		initial_conditions.emplace_back(stream->volumetricFlowRate().value());

	for (const auto& stream : m_outlet_mass_streams)
		initial_conditions.emplace_back(stream->temperature().value());

	for (const auto& stream : m_inlet_mass_streams)
		initial_conditions.emplace_back(stream->volumetricFlowRate().value());

	return initial_conditions;
}

} //namespace unitop