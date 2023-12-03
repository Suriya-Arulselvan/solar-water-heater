#pragma once
#include <iostream>

#include "Scalar/Scalar.h"
#include "Stream.h"

namespace stream {

class EnergyStream : public Stream
{
	scalar::Scalar m_heat_flow = 0.0;

public:
	EnergyStream() = default;

	EnergyStream(const EnergyStream&) = default;
	EnergyStream(EnergyStream&&) = default;

	EnergyStream& operator=(const EnergyStream&) = default;
	EnergyStream& operator=(EnergyStream&&) = default;

	~EnergyStream() = default;

	EnergyStream(const std::string& name) : Stream(name) {};
	EnergyStream(std::string&& name) : Stream(name) {};

	scalar::Scalar& heatFlow() { return m_heat_flow; }
	const scalar::Scalar& heatFlow() const { return m_heat_flow; }
	void setHeatFlow(const scalar::Scalar& heat_flow) { m_heat_flow = heat_flow; }
	void setHeatFlow(scalar::Scalar&& heat_flow) { m_heat_flow = std::move(heat_flow); }
};

using SharedEnergyStream = std::shared_ptr<EnergyStream>;

} //namespace stream
