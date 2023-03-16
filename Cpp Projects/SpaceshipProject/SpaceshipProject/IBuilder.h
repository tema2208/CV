#pragma once
#include "DestinationTypes.h"
#include "Factory.h"
#include "ShipsTypes.h"
#include "Spaceship.h"

struct IBuilder
{
	virtual ~IBuilder() = default;
	virtual IBuilder* SetFactory(const Factory& f) = 0;
	virtual IBuilder* SetFrameSize(int n) = 0;
    virtual IBuilder* SetStandardEngineSize(int n) = 0;
    virtual IBuilder* SetSuperEngineSize(int size) = 0;
    virtual IBuilder* SetRadarCount(int count) = 0;
    virtual IBuilder* SetLivingModulesCount(int count) = 0;
    virtual IBuilder* SetLandingModulesCount(int count) = 0;
    virtual IBuilder* SetArmamentInfo(ArmamentTypes type, int count) = 0;
    virtual IBuilder* SetSpaceshipType(ShipsTypes type) = 0;
    virtual IBuilder* SetDestination(DestinationTypes type) = 0;
    virtual Spaceship Build() = 0;
};
