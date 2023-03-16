#include "Armament.h"

std::string Armament::TypeToSting() const
{
	switch (type)
	{
	case ArmamentTypes::STANDARD:
		return "Standard";
	case ArmamentTypes::STRATEGIC:
		return "Strategic";
	case ArmamentTypes::DEFENSIVE:
		return "Defensive";
	case ArmamentTypes::NOT_DEFINED:
		return "undefined type";
	}
	return "undefined type";
}

Armament::Armament(int size_, double cost_, double range_, double rT_, double damage_, ArmamentTypes type_)
{
	if (size_ >= 0 && cost_ >= 0 && range_ >= 0 && rT_ >= 0 && damage_ >= 0)
	{
		size = size_;
		cost = cost_;
		range = range_;
		rechargeTime = rT_;
		damage = damage_;
		type = type_;
	}
	else throw std::exception("Wrong arguments");
}