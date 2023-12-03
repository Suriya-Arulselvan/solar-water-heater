#pragma once
#include "UnitOperation.h"
#include "StorageTank.h"
#include "Pump.h"
#include "SolarWaterHeater.h"

namespace unitop
{
class UnitOperationFactory
{
public:
	static std::unique_ptr<UnitOperation> createUnitOperation(UnitOperationType unit_operation_type)
	{
		switch (unit_operation_type)
		{
		case UnitOperationType::StorageTank:
			return std::make_unique<StorageTank>();

		case UnitOperationType::Pump:
			return std::make_unique<Pump>();

		case UnitOperationType::SolarWaterHeater:
			return std::make_unique<SolarWaterHeater>();

		case UnitOperationType::Unknown:
			return nullptr;

		default:
			return nullptr;
		}
	}
};

} //namespace unitop