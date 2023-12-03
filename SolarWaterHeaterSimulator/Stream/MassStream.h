#pragma once
#include <iostream>

#include "Scalar/Scalar.h"
#include "Stream.h"

namespace stream {

class MassStream : public Stream
{
	scalar::Scalar m_volumetric_flow_rate = 0.0;
	scalar::Scalar m_temperature = 293.0;

	//Physical properties
	double m_specific_heat_capacity = 3.0;
	double m_density = 1.0;

public:
	MassStream() = default;

	MassStream(const MassStream&) = default;
	MassStream(MassStream&&) = default;

	MassStream& operator=(const MassStream&) = default;
	MassStream& operator=(MassStream&&) = default;

	~MassStream() = default;

	MassStream(const std::string& name) : Stream(name) {};
	MassStream(std::string&& name) : Stream(name) {};

	scalar::Scalar& volumetricFlowRate() { return m_volumetric_flow_rate; }
	const scalar::Scalar& volumetricFlowRate() const { return m_volumetric_flow_rate; }
	void setVolumetricFlowRate(const scalar::Scalar& volumetric_flow_rate) { m_volumetric_flow_rate = volumetric_flow_rate; }
	void setVolumetricFlowRate(scalar::Scalar&& volumetric_flow_rate) { m_volumetric_flow_rate = std::move(volumetric_flow_rate); }

	scalar::Scalar& temperature() { return m_temperature; }
	const scalar::Scalar& temperature() const { return m_temperature; }
	void setTemperature(const scalar::Scalar& temperature) { m_temperature = temperature; }
	void setTemperature(scalar::Scalar&& temperature) { m_temperature = std::move(temperature); }

	double specificHeatCapacity() const { return m_specific_heat_capacity; }
	void setSpecificHeatCapacity(double specific_heat_capacity) { m_specific_heat_capacity = specific_heat_capacity; }

	double density() const { return m_density; }
	void setDensity(double density) { m_density = density; }
};

using SharedMassStream = std::shared_ptr<MassStream>;
} //namespace stream
