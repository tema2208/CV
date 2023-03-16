#pragma once
#include "Factory.h"

struct ModulesFactory1 : Factory
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

inline std::shared_ptr<Factory> ModulesFactory1::Clone() const
{
	return std::make_shared<ModulesFactory1>(*this);
}

inline Frame ModulesFactory1::CreateFrame(int n)
{
	return { n, 100, 10 };
}

inline StandardEngine ModulesFactory1::CreateStandardEngine(int size)
{
	return { size, 550 };
}

inline SuperEngine ModulesFactory1::CreateSuperEngine(int size)
{
	return { size, 200 };
}

inline LivingModule ModulesFactory1::CreateLivingModule()
{
	return { 40, 18 };
}

inline LandingModule ModulesFactory1::CreateLandingModule()
{
	return { 30,15 };
}

inline Armament ModulesFactory1::CreateStrategicWeapon()
{
	return { 5, 15, 1000, 15, 100, ArmamentTypes::STRATEGIC };
}

inline Armament ModulesFactory1::CreateStandardWeapon()
{
	return { 5, 19, 700, 12, 120, ArmamentTypes::STANDARD };
}

inline Armament ModulesFactory1::CreateDefensiveWeapon()
{
	return { 15, 21, 400, 10, 115, ArmamentTypes::DEFENSIVE };
}

inline Radar ModulesFactory1::CreateRadar()
{
	return { 10, 10, 100, 150 };
}
