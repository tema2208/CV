#pragma once
#include "Factory.h"

struct ModulesFactory2 : Factory
{
	Frame CreateFrame(int n) override;
	StandardEngine CreateStandardEngine(int size) override;
	SuperEngine CreateSuperEngine(int size) override;
	LivingModule CreateLivingModule() override;
	LandingModule CreateLandingModule() override;
	Armament CreateStrategicWeapon() override;
	Armament CreateStandardWeapon() override;
	Armament CreateDefensiveWeapon() override;
	Radar CreateRadar() override;

	std::shared_ptr<Factory> Clone() const override;
};

inline std::shared_ptr<Factory> ModulesFactory2::Clone() const
{
	return std::make_shared<ModulesFactory2>(*this);
}

inline Frame ModulesFactory2::CreateFrame(int n)
{
	return { n, 150, 15 };
}

inline StandardEngine ModulesFactory2::CreateStandardEngine(int size)
{
	return { size, 400 };
}

inline SuperEngine ModulesFactory2::CreateSuperEngine(int size)
{
	throw std::exception("This factory can't create super engine");
}

inline LivingModule ModulesFactory2::CreateLivingModule()
{
	return { 45, 25 };
}

inline LandingModule ModulesFactory2::CreateLandingModule()
{
	return { 28,13 };
}

inline Armament ModulesFactory2::CreateStrategicWeapon()
{
	return { 3, 20, 1200, 17, 120, ArmamentTypes::STRATEGIC };
}

inline Armament ModulesFactory2::CreateStandardWeapon()
{
	return { 5, 19, 700, 12, 120, ArmamentTypes::STANDARD };
}

inline Armament ModulesFactory2::CreateDefensiveWeapon()
{
	return { 15, 21, 400, 10, 115, ArmamentTypes::DEFENSIVE };
}

inline Radar ModulesFactory2::CreateRadar()
{
	return { 12, 3, 200, 400 };
}

