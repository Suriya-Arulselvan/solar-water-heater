#pragma once
#include <iostream>
#include <cstdlib>

#include "Scalar/Scalar.h"
#include "UnitOperation.h"
#include "Stream/MassStream.h"

namespace unitop {

class SolarWaterHeater : public UnitOperation
{
	//Design parameter
	double m_peak_solar_heat_influx = 10.0;

	double m_volume = 10.0;
	double m_efficiency = 0.8;
	double m_heat_loss_surface_area = 5.0;
	double m_coefficient_of_heat_transfer_ambient = 0.5;
	double m_ambient_temperature = 293.0;

public:
	SolarWaterHeater() : UnitOperation(UnitOperationType::SolarWaterHeater) {}

	SolarWaterHeater(const SolarWaterHeater&) = default;
	SolarWaterHeater(SolarWaterHeater&&) = default;

	SolarWaterHeater& operator=(const SolarWaterHeater&) = default;
	SolarWaterHeater& operator=(SolarWaterHeater&&) = default;

	~SolarWaterHeater() = default;

	SolarWaterHeater* clone() const override { return new SolarWaterHeater(*this); }

	void calculateMassBalance(double time) override {}

	void calculateEnergyBalance(double time) override;

};
}