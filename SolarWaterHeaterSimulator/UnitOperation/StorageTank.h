#pragma once
#include <iostream>
#include <cstdlib>

#include "Scalar/Scalar.h"
#include "UnitOperation.h"
#include "Stream/MassStream.h"

namespace unitop {

class StorageTank : public UnitOperation
{
	//Design parameters
	double m_volume = 20.0;
	double m_heat_loss_surface_area = 2;
	double m_coefficient_of_heat_transfer_ambient = 0.5;
	double m_ambient_temperature = 293;

public:

	StorageTank() : UnitOperation(UnitOperationType::StorageTank) {}

	StorageTank(const StorageTank&) = default;
	StorageTank(StorageTank&&) = default;

	StorageTank& operator=(const StorageTank&) = default;
	StorageTank& operator=(StorageTank&&) = default;

	~StorageTank() = default;

	StorageTank* clone() const override { return new StorageTank(*this); }

	double volume() const { return m_volume; }
	void setVolume(double volume) { m_volume = volume; }

	//Assumption is that water gets replenished every 
	void calculateMassBalance(double time) override {}

	//Representing the following equation
	//Density * Volume * Cp * dTout/dt = Density * Cp(qin * Tin - qout * Tout) - UA(Tout - Tambient)
	void calculateEnergyBalance(double time) override;

};

using UniqueStorageTank = std::unique_ptr<StorageTank>;

} //namespace unitop