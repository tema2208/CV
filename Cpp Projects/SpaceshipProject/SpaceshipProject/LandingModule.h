#pragma once
#include "Modules.h"

struct LandingModule : Modules
{
	LandingModule() = default;
	LandingModule(int, double);

	int GetSize() const override;
	double GetCost() const override;
	std::string Description() const override;
};

inline int LandingModule::GetSize() const
{
	return size;
}

inline double LandingModule::GetCost() const
{
	return cost;
}

inline std::string LandingModule::Description() const
{
	return "Landing module: ";
}
