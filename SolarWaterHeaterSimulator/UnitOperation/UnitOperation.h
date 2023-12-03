#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Stream/MassStream.h"
#include "Stream/EnergyStream.h"

namespace unitop {

enum class UnitOperationType
{
	Unknown,
	StorageTank,
	Pump,
	SolarWaterHeater
};

class UnitOperation
{
	UnitOperationType m_unit_operation_type = UnitOperationType::Unknown;
	std::string m_name;

protected:
	std::vector<stream::SharedMassStream> m_inlet_mass_streams;
	std::vector<stream::SharedMassStream> m_outlet_mass_streams;

	std::vector<stream::SharedEnergyStream> m_inlet_energy_streams;
	std::vector<stream::SharedEnergyStream> m_outlet_energy_streams;

public:
	UnitOperation() = default;

	UnitOperation(UnitOperationType unit_operation_type) : m_unit_operation_type(unit_operation_type) {}

	UnitOperation(const UnitOperation&) = default;
	UnitOperation(UnitOperation&&) = default;

	UnitOperation& operator=(const UnitOperation&) = default;
	UnitOperation& operator=(UnitOperation&&) = default;

	virtual ~UnitOperation() = default;

	virtual UnitOperation* clone() const = 0;
	
	const std::string& name() const { return m_name; }
	void setName(const std::string& name) { m_name = name; }
	void setName(std::string&& name) { m_name = std::move(name); }

	UnitOperationType unitOperationType() const { return m_unit_operation_type; }
	void setUnitOperationType(UnitOperationType unit_operation_type) { m_unit_operation_type = unit_operation_type; }

	void addInletMassStream(const stream::SharedMassStream& mass_stream) { m_inlet_mass_streams.emplace_back(mass_stream); }
	void addInletMassStream(stream::SharedMassStream&& mass_stream) { m_inlet_mass_streams.emplace_back(std::move(mass_stream)); }

	const std::vector<stream::SharedMassStream>& inletMassStreams() const { return m_inlet_mass_streams; }

	void addOutletMassStream(const stream::SharedMassStream& mass_stream) { m_outlet_mass_streams.emplace_back(mass_stream); }
	void addOutletMassStream(stream::SharedMassStream&& mass_stream) { m_outlet_mass_streams.emplace_back(std::move(mass_stream)); }

	const std::vector<stream::SharedMassStream>& outletMassStreams() const { return m_outlet_mass_streams; }

	void addInletEnergyStream(const stream::SharedEnergyStream& energy_stream) { m_inlet_energy_streams.emplace_back(energy_stream); }
	void addInletEnergyStream(stream::SharedEnergyStream&& energy_stream) { m_inlet_energy_streams.emplace_back(std::move(energy_stream)); }

	const std::vector<stream::SharedEnergyStream>& inletEnergyStreams() const { return m_inlet_energy_streams; }

	void addOutletEnergyStream(const stream::SharedEnergyStream& energy_stream) { m_outlet_energy_streams.emplace_back(energy_stream); }
	void addOutletEnergyStream(stream::SharedEnergyStream&& energy_stream) { m_outlet_energy_streams.emplace_back(std::move(energy_stream)); }

	const std::vector<stream::SharedEnergyStream>& outletEnergyStreams() const { return m_outlet_energy_streams; }

	virtual void initialize() {};

	virtual void calculateMassBalance(double time) {};

	virtual void calculateEnergyBalance(double time) {};

	virtual std::vector<double> initialConditions() const;

};



using UniqueUnitOperation = std::unique_ptr<UnitOperation>;

} //namespace unitop