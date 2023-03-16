#pragma once
#include "Frame.h"
#include "StandardEngine.h"
#include "SuperEngine.h"
#include "LivingModule.h"
#include "LandingModule.h"
#include "Armament.h"
#include "Radar.h"


struct Factory
{
	virtual ~Factory() = default;

	virtual Frame CreateFrame(int n) = 0;
	virtual StandardEngine CreateStandardEngine(int size) = 0;
	virtual SuperEngine CreateSuperEngine(int size) = 0;
	virtual LivingModule CreateLivingModule() = 0;
	virtual LandingModule CreateLandingModule() = 0;
	virtual Armament CreateStrategicWeapon() = 0;
	virtual Armament CreateStandardWeapon() = 0;
	virtual Armament CreateDefensiveWeapon() = 0;
	virtual Radar CreateRadar() = 0;

	virtual std::shared_ptr<Factory> Clone() const = 0;
};
