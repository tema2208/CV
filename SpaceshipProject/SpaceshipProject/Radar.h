#pragma once
#include <string>

#include "Modules.h"

struct Radar : Modules
{
	Radar() = default;
	Radar(int, double, double, double);

	int GetSize() const override;
	double GetCost() const override;
	double GetRange() const;
	double GetDetectionForce() const;
	std::string Description() const override;


private:
	double range = 0;
	double detectionForce = 0;
};

inline int Radar::GetSize() const
{
	return size;
}

inline double Radar::GetCost() const
{
	return cost;
}

inline double Radar::GetRange() const
{
	return range;
}

inline double Radar::GetDetectionForce() const
{
	return detectionForce;
}

inline std::string Radar::Description() const
{
	return "Radar: range = " + std::to_string(range) + ", detection force = " + std::to_string(detectionForce);
}
