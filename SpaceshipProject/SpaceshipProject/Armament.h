#pragma once
#include <string>

#include "Modules.h"
#include "ArmamentTypes.h"

struct Armament: Modules
{
	Armament() = default;
	Armament(int, double, double, double, double, ArmamentTypes);

	int GetSize() const override;
	double GetCost() const override;
	std::string Description() const override;

private:
	std::string TypeToSting() const;

	double range = 0;
	double rechargeTime= 0;
	double damage = 0;
	ArmamentTypes type = ArmamentTypes::NOT_DEFINED;
};

inline int Armament::GetSize() const
{
	return size;
}

inline double Armament::GetCost() const
{
	return cost;
}

inline std::string Armament::Description() const
{
	return "Armament: range = " + std::to_string(range) + ", recharge time = " + std::to_string(rechargeTime) +
		", damage = " + std::to_string(damage) + ", armament type = " + TypeToSting();
}

