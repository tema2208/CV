#include "Spaceship.h"

std::string Spaceship::DestinationTypeToString() const
{
    switch (destination)
    {
    case DestinationTypes::INTERSTELLAR:
        return "Interstellar";
    case DestinationTypes::SYSTEM:
        return "System";
    case DestinationTypes::NOT_DEFINED:
        return "undefined type";
    }
    return "undefined type";
}

std::string Spaceship::ShipTypeToString() const
{
    switch (type)
    {
    case ShipsTypes::PASSENGER:
        return "Passenger";
    case ShipsTypes::CARGO:
        return "Cargo";
    case ShipsTypes::COLONIZER:
        return "Colonizer";
    case ShipsTypes::MILITARY_GENERAL:
        return "Military general";
    case ShipsTypes::MILITARY_STRATEGIC:
        return "Military strategic";
    case ShipsTypes::MILITARY_TRANSPORT:
        return "Military transport";
    case ShipsTypes::RESEARCH:
        return "Research";
    case ShipsTypes::NOT_DEFINED:
        return "undefined type";
    }
    return "undefined type";
}

std::ostream& operator<<(std::ostream& os, const Spaceship& s)
{
    os << "Spaceship: destination = " << s.DestinationTypeToString() << " " << ", spaceship type = " << s.ShipTypeToString() << std::endl;
    os << s.frame << s.standardEngine << s.superEngine;
    s.CorrectPrint(os, s.livingModule, s.livingModulesCount);
    s.CorrectPrint(os, s.landingModule, s.landingModulesCount);
    s.CorrectPrint(os, s.radar, s.radarsCount);
    if(s.weaponsInfo.count(ArmamentTypes::STRATEGIC))
		s.CorrectPrint(os, s.strategicWeapon, s.weaponsInfo.at(ArmamentTypes::STRATEGIC));
	if (s.weaponsInfo.count(ArmamentTypes::DEFENSIVE))
		s.CorrectPrint(os, s.defensiveWeapon, s.weaponsInfo.at(ArmamentTypes::DEFENSIVE));
    if (s.weaponsInfo.count(ArmamentTypes::STANDARD))
		s.CorrectPrint(os, s.standardWeapon, s.weaponsInfo.at(ArmamentTypes::STANDARD));
    os << "cargo hold size = " << s.cargoHold << std::endl;
    os << "total cost = " << s.TotalCost() << std::endl;
    return os;
}


double Spaceship::TotalCost() const
{
    double result = 0;
    if (!frame.IsEmpty()) result += frame.GetCost(); 
    if (!standardEngine.IsEmpty()) result += standardEngine.GetCost();
    if (!superEngine.IsEmpty()) result += superEngine.GetCost();
    if (!radar.IsEmpty()) result += radar.GetCost() * radarsCount;
    if (!livingModule.IsEmpty()) result += livingModule.GetCost() * livingModulesCount;
    if (!landingModule.IsEmpty()) result += landingModule.GetCost() * landingModulesCount;
    if (!strategicWeapon.IsEmpty() && weaponsInfo.count(ArmamentTypes::STRATEGIC)) 
        result += strategicWeapon.GetCost() * weaponsInfo.at(ArmamentTypes::STRATEGIC);
    if (!defensiveWeapon.IsEmpty() && weaponsInfo.count(ArmamentTypes::DEFENSIVE)) 
        result += defensiveWeapon.GetCost() * weaponsInfo.at(ArmamentTypes::DEFENSIVE);
    if (!standardWeapon.IsEmpty() && weaponsInfo.count(ArmamentTypes::STANDARD))
        result += standardWeapon.GetCost() * weaponsInfo.at(ArmamentTypes::STANDARD);
    return result;
}

