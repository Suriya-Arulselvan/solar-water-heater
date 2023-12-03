#include "Pump.h"

using namespace stream;

namespace unitop {

void Pump::initialize()
{
	//Work * Efficiency = (P2 - P1) * flow rate
	const SharedMassStream& inlet_mass_stream = *m_inlet_mass_streams.begin();
	const SharedEnergyStream& inlet_energy_stream = *m_inlet_energy_streams.begin();

	if (!inlet_mass_stream || inlet_energy_stream)
		return;

	inlet_mass_stream->setVolumetricFlowRate({ inlet_energy_stream->heatFlow().value() * m_efficiency / m_pressure_differential, 0.0 });
}

void Pump::calculateEnergyBalance(double time)
{
	const SharedMassStream& inlet_mass_stream = *m_inlet_mass_streams.begin();
	const SharedMassStream& outlet_mass_stream = *m_outlet_mass_streams.begin();

	if(!inlet_mass_stream || !outlet_mass_stream)
		return;

	outlet_mass_stream->setTemperature(inlet_mass_stream->temperature());
}


}//namespace unitop