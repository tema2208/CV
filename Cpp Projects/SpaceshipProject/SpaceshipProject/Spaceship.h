#pragma once
#include <map>

#include "Armament.h"
#include "ArmamentTypes.h"
#include "DestinationTypes.h"
#include "Frame.h"
#include "LandingModule.h"
#include "LivingModule.h"
#include "Radar.h"
#include "ShipsTypes.h"
#include "StandardEngine.h"
#include "SuperEngine.h"


struct Spaceship
{
    using WeaponsInfo = std::map<ArmamentTypes, int>;

    void SetFrame(const Frame & f);
    void SetStandardEngine(const StandardEngine& se);
    void SetSuperEngine(const SuperEngine& se);
    void SetRadar(const Radar& r, int count);
    void SetLivingModule(const LivingModule& lm, int count);
    void SetLandingModule(const LandingModule& lm, int count);
    void SetWeaponsInfo(const WeaponsInfo & i);
    void SetDestination(const DestinationTypes & d);
    void SetSpaceshipType(const ShipsTypes & t);
    void SetStrategicWeapon(const Armament & w);
    void SetDefensiveWeapon(const Armament & w);
    void SetStandardWeapon(const Armament & w);
    void SetCargoHold(int n);


private:
    friend std::ostream& operator<<(std::ostream&, const Spaceship&);

    static std::ostream& CorrectPrint(std::ostream& os, const Modules& m, int number);
    std::string ShipTypeToString() const;
    std::string DestinationTypeToString() const;
    double TotalCost() const;

	Frame frame{};
    StandardEngine standardEngine{};
    SuperEngine superEngine{};
    Radar radar{};
    int radarsCount = 0;
    LivingModule livingModule{};
    int livingModulesCount = 0;
    LandingModule landingModule{};
    int landingModulesCount = 0;
    Armament strategicWeapon{};
    Armament standardWeapon{};
    Armament defensiveWeapon{};
    WeaponsInfo weaponsInfo{};
    ShipsTypes type = ShipsTypes::NOT_DEFINED;
    DestinationTypes destination= DestinationTypes::NOT_DEFINED;
    int cargoHold = 0;
};
	

inline std::ostream& Spaceship::CorrectPrint(std::ostream& os, const Modules& m, int number)
{
    number ? os << "number: " << number << "; " << m : os << "This module is missing" << std::endl;
    return os;
}

inline void Spaceship::SetFrame(const Frame& f)
{
    frame = f;
}

inline void Spaceship::SetStandardEngine(const StandardEngine& se)
{
    standardEngine = se;
    standardEngine.SetSpeed(frame);
}

inline void Spaceship::SetSuperEngine(const SuperEngine& se)
{
    superEngine = se;
    superEngine.SetSpeed(frame);
}

inline void Spaceship::SetRadar(const Radar& r, int count)
{
    radarsCount = count;
    radar = r;
}

inline void Spaceship::SetLivingModule(const LivingModule& lm, int count)
{
    livingModule = lm;
    livingModulesCount = count;
}

inline void Spaceship::SetLandingModule(const LandingModule& lm, int count)
{
    landingModule = lm;
    landingModulesCount = count;
}

inline void Spaceship::SetWeaponsInfo(const WeaponsInfo& i)
{
    weaponsInfo = i;
}

inline void Spaceship::SetDestination(const DestinationTypes& d)
{
    destination = d;
}

inline void Spaceship::SetSpaceshipType(const ShipsTypes& t)
{
    type = t;
}

inline void Spaceship::SetStrategicWeapon(const Armament& w)
{
    strategicWeapon = w;
}

inline void Spaceship::SetDefensiveWeapon(const Armament& w)
{
    defensiveWeapon = w;
}

inline void Spaceship::SetStandardWeapon(const Armament& w)
{
    standardWeapon = w;
}

inline void Spaceship::SetCargoHold(int n)
{
    cargoHold = n;
}

