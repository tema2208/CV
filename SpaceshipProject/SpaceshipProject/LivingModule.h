#pragma once
#include "Modules.h"

struct LivingModule : Modules
{
	LivingModule() = default;
	LivingModule(int, double);

	int GetSize() const override;
	double GetCost() const override;
	std::string Description() const override;
};

inline int LivingModule::GetSize() const
{
	return size;
}

inline double LivingModule::GetCost() const
{
	return cost;
}

inline std::string LivingModule::Description() const
{
	return "Living module: ";
}


