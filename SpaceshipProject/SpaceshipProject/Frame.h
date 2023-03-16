#pragma once
#include <string>

#include "Modules.h"

struct Frame : Modules
{
	Frame(int = 0, double = 0, double = 0);

	int GetSize() const override;
	double GetCost() const override;
	double GetArmor() const;
	std::string Description() const override;


private:
	const static int aCoef = 80;
	double armor = 0;
};

inline int Frame::GetSize() const
{
	return size;
}

inline double Frame::GetCost() const
{
	return cost;
}

inline double Frame::GetArmor() const
{
	return armor;
}

inline std::string Frame::Description() const
{
	return "Frame: armor = " + std::to_string(armor);
}

