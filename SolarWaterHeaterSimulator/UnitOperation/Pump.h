#pragma once
#include <iostream>
#include <cstdlib>

#include "Scalar/Scalar.h"
#include "UnitOperation.h"
#include "Stream/MassStream.h"

namespace unitop {

class Pump : public UnitOperation
{
	//Design parameters
	double m_efficiency = 0.75;
	double m_pressure_differential = 10.0;

public:
	Pump() : UnitOperation(UnitOperationType::Pump) {}

	Pump(const Pump&) = default;
	Pump(Pump&&) = default;

	Pump& operator=(const Pump&) = default;
	Pump& operator=(Pump&&) = default;

	~Pump() = default;

	Pump* clone() const override { return new Pump(*this); }

	void initialize() override;

	//Mass balance should be called every step
	void calculateMassBalance(double time) override {}

	void calculateEnergyBalance(double tiem) override;
};

} //namespace unitop