#pragma once
#include "IBuilder.h"

struct SpaceshipBuilder : IBuilder
{
	using ArmamentInfo = std::map<ArmamentTypes, int>;
	using Factory_ptr = std::shared_ptr<Factory>;

	IBuilder* SetFactory(const Factory& f) override;
	IBuilder* SetFrameSize(int n) override;
	IBuilder* SetStandardEngineSize(int n) override;
	IBuilder* SetSuperEngineSize(int size) override;
	IBuilder* SetRadarCount(int count) override;
	IBuilder* SetLivingModulesCount(int count) override;
	IBuilder* SetLandingModulesCount(int count) override;
	IBuilder* SetArmamentInfo(ArmamentTypes type, int count) override;
	IBuilder* SetSpaceshipType(ShipsTypes type) override;
	IBuilder* SetDestination(DestinationTypes type) override;
	Spaceship Build() override;


private:
    bool WeaponsIsEmpty() const;
	void CheckCargoHoldSize(int&, const LivingModule&, const LandingModule&, const Armament&, const Armament&, const Armament&);

	Factory_ptr factory = nullptr;
	int frameSize = 0;
	int standardEngineSize = 0;
	int superEngineSize = 0;
	int radarCount = 0;
	int livingModulesCount = 0;
	int landingModulesCount = 0;
	ArmamentInfo weaponsInfo;
	ShipsTypes spaceshipType = ShipsTypes::NOT_DEFINED;
	DestinationTypes destination = DestinationTypes::NOT_DEFINED;
};

inline IBuilder* SpaceshipBuilder::SetFactory(const Factory& f)
{
	factory = f.Clone();
	return this;
}

inline IBuilder* SpaceshipBuilder::SetFrameSize(int n)
{
	frameSize = n;
	return this;
}

inline IBuilder* SpaceshipBuilder::SetStandardEngineSize(int n)
{
	standardEngineSize = n;
	return this;
}

inline IBuilder* SpaceshipBuilder::SetSuperEngineSize(int size)
{
	superEngineSize = size;
	return this;
}

inline IBuilder* SpaceshipBuilder::SetRadarCount(int count)
{
	radarCount = count;
	return this;
}

inline IBuilder* SpaceshipBuilder::SetLivingModulesCount(int count)
{
	livingModulesCount = count;
	return this;
}

inline IBuilder* SpaceshipBuilder::SetLandingModulesCount(int count)
{
	landingModulesCount = count;
	return this;
}

inline IBuilder* SpaceshipBuilder::SetArmamentInfo(ArmamentTypes type, int count)
{
	weaponsInfo.emplace(type, count);
	return this;
}

inline IBuilder* SpaceshipBuilder::SetSpaceshipType(ShipsTypes type)
{
	spaceshipType = type;
	return this;
}

inline IBuilder* SpaceshipBuilder::SetDestination(DestinationTypes type)
{
	destination = type;
	return this;
}

inline bool SpaceshipBuilder::WeaponsIsEmpty() const
{
	int strategicCount = weaponsInfo.count(ArmamentTypes::STRATEGIC) ? weaponsInfo.at(ArmamentTypes::STRATEGIC) : 0;
	int standardCount = weaponsInfo.count(ArmamentTypes::STANDARD) ? weaponsInfo.at(ArmamentTypes::STANDARD) : 0;
	int defensiveCount = weaponsInfo.count(ArmamentTypes::DEFENSIVE) ? weaponsInfo.at(ArmamentTypes::DEFENSIVE) : 0;
	if (strategicCount == 0 && standardCount == 0 && defensiveCount == 0)
		return true;
    return false;
}

