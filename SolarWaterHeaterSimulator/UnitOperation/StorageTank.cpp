#include "StorageTank.h"

using namespace stream;
using namespace std;

namespace unitop
{
void StorageTank::calculateEnergyBalance(double time)
{
	//Density * Volume * Cp * dTout/dt = Density * Cp(qin * Tin - qout * Tout) - UA(Tout - Tambient)

	double dToutdt = 0.0;

	SharedMassStream inlet_mass_stream = *m_inlet_mass_streams.begin();
	SharedMassStream outlet_mass_stream = *m_outlet_mass_streams.begin();

	if (!inlet_mass_stream || !outlet_mass_stream)
		return;

	double specific_heat_capacity = inlet_mass_stream->specificHeatCapacity();
	double density = inlet_mass_stream->density();

	double inlet_heat = density * specific_heat_capacity * inlet_mass_stream->volumetricFlowRate().value()*inlet_mass_stream->temperature().value();
	double outlet_heat = density * specific_heat_capacity * outlet_mass_stream->volumetricFlowRate().value()*outlet_mass_stream->temperature().value();

	double heat_loss_to_ambient = m_coefficient_of_heat_transfer_ambient * m_heat_loss_surface_area * (outlet_mass_stream->temperature().value() - m_ambient_temperature);

	dToutdt = (inlet_heat - outlet_heat - heat_loss_to_ambient) / (m_volume * specific_heat_capacity * density);

	outlet_mass_stream->temperature().setDerivative(dToutdt);
}

} //namespace unitop