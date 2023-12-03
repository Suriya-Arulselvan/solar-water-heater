#include "SolarWaterHeater.h"

using namespace stream;

namespace unitop {

void SolarWaterHeater::calculateEnergyBalance(double time)
{
	const SharedMassStream& inlet_mass_stream = *m_inlet_mass_streams.begin();
	const SharedMassStream& outlet_mass_stream = *m_outlet_mass_streams.begin();
	const SharedEnergyStream& inlet_energy_stream = *m_inlet_energy_streams.begin();

	if (!inlet_mass_stream || !outlet_mass_stream || !inlet_energy_stream)
		return;

	//Calculate input heat flow which is a function of time
	double sine_function_parameter = 3.14 / (2.0);
	inlet_energy_stream->heatFlow().setValue(m_peak_solar_heat_influx * (sin(sine_function_parameter * time) + 1.0));

	//Determine outlet T derivative from energy balance
	double dToutdt = 0.0;

	double specific_heat_capacity = inlet_mass_stream->specificHeatCapacity();
	double density = inlet_mass_stream->density();

	double inlet_heat = density * specific_heat_capacity * inlet_mass_stream->volumetricFlowRate().value()*inlet_mass_stream->temperature().value();
	double outlet_heat = density * specific_heat_capacity * outlet_mass_stream->volumetricFlowRate().value()*outlet_mass_stream->temperature().value();

	double heat_loss_to_ambient = m_coefficient_of_heat_transfer_ambient * m_heat_loss_surface_area * (outlet_mass_stream->temperature().value() - m_ambient_temperature);
	double solar_energy = inlet_energy_stream->heatFlow().value();

	dToutdt = (solar_energy + inlet_heat - outlet_heat - heat_loss_to_ambient) / (m_volume * density * specific_heat_capacity);

	outlet_mass_stream->temperature().setDerivative(dToutdt);
}

} //namespace unitop