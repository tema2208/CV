#include "SpaceshipBuilder.h"

void SpaceshipBuilder::CheckCargoHoldSize(int& cargoSize, const LivingModule& livingModule, const LandingModule& landingModule, const Armament& defensiveWeapon,
    const Armament& standardWeapon, const Armament& strategicWeapon)
{
    cargoSize -= livingModule.GetSize() * livingModulesCount + landingModulesCount * landingModule.GetSize();
    cargoSize -= defensiveWeapon.GetSize() * weaponsInfo[ArmamentTypes::DEFENSIVE] + standardWeapon.GetSize() * weaponsInfo[ArmamentTypes::STANDARD]
        + strategicWeapon.GetSize() * weaponsInfo[ArmamentTypes::STRATEGIC];
}

Spaceship SpaceshipBuilder::Build()
{
    Spaceship spaceship{};
    weaponsInfo[ArmamentTypes::DEFENSIVE];
    if (factory == nullptr) throw std::exception("Can't create spaceship without factory");
    if (destination == DestinationTypes::NOT_DEFINED || spaceshipType == ShipsTypes::NOT_DEFINED)
        throw std::exception("Can't create spaceship without necessary types");
    if (frameSize == 0 || radarCount == 0 || standardEngineSize == 0)
    {
        throw std::exception("Can't create spaceship without necessary modules");
    }

    Frame frame = factory->CreateFrame(frameSize);
    StandardEngine standardEngine = factory->CreateStandardEngine(standardEngineSize);
    SuperEngine superEngine = factory->CreateSuperEngine(superEngineSize);
    Radar radar = factory->CreateRadar();
    LivingModule livingModule = factory->CreateLivingModule();
    LandingModule landingModule = factory->CreateLandingModule();
    Armament defensiveWeapon = factory->CreateDefensiveWeapon();
    Armament standardWeapon = factory->CreateStandardWeapon();
    Armament strategicWeapon = factory->CreateStrategicWeapon();
    ArmamentInfo weaponsInfo1(weaponsInfo);

    if (!standardEngine.CheckEngine(frame)) throw std::exception("Standard engine and frame are incompatible");
    int cargoHoldSize = frame.GetSize() - standardEngineSize - radar.GetSize() * radarCount;
    if (cargoHoldSize > 0)
    {
        spaceship.SetFrame(frame);
        spaceship.SetStandardEngine(standardEngine);
        spaceship.SetRadar(radar, radarCount);
    }
    else throw std::exception("Frame is too small for standard engine");

    if (destination == DestinationTypes::INTERSTELLAR)
    {
        if (superEngineSize == 0) throw std::exception("Wrong information about interstellar spaceship");
        if (!superEngine.CheckEngine(frame)) {
            throw std::exception("Super engine and frame are incompatible");
        }
        if (cargoHoldSize - superEngineSize < 0) throw std::exception("Frame is too small for super engine");
        spaceship.SetSuperEngine(superEngine);
        cargoHoldSize -= superEngineSize;
    }
    spaceship.SetDestination(destination);

    CheckCargoHoldSize(cargoHoldSize, livingModule, landingModule, defensiveWeapon, standardWeapon, strategicWeapon);
    if (cargoHoldSize < 0) throw std::exception("Frame is overloaded");
    spaceship.SetCargoHold(cargoHoldSize);


    int defensiveWeaponCount = weaponsInfo[ArmamentTypes::DEFENSIVE];
    int strategicWeaponCount = weaponsInfo[ArmamentTypes::STRATEGIC];
    int standardWeaponCount = weaponsInfo[ArmamentTypes::STANDARD];

    switch (spaceshipType)
    {
    case ShipsTypes::RESEARCH:
        if (!WeaponsIsEmpty()) throw std::exception("Research spaceship can't have weapons");
        if (livingModulesCount != 0) spaceship.SetLivingModule(livingModule, livingModulesCount);
        if (landingModulesCount != 0) spaceship.SetLandingModule(landingModule, landingModulesCount);

        spaceship.SetSpaceshipType(ShipsTypes::RESEARCH);
        return spaceship;

    case ShipsTypes::PASSENGER:
        if (!WeaponsIsEmpty()) throw std::exception("Passenger spaceship can't have weapons");
        if (livingModulesCount == 0) throw std::exception("Passenger spaceship must have living modules");
        spaceship.SetLivingModule(livingModule, livingModulesCount);
        if (landingModulesCount != 0) spaceship.SetLandingModule(landingModule, landingModulesCount);

        spaceship.SetSpaceshipType(ShipsTypes::PASSENGER);
        return spaceship;

    case ShipsTypes::CARGO:
        if (cargoHoldSize == 0) throw std::exception("Cargo hold must be non-zero");
        if (livingModulesCount == 0) throw std::exception("Cargo spaceship must have living modules");
        spaceship.SetLivingModule(livingModule, livingModulesCount);

        if (!WeaponsIsEmpty() && defensiveWeaponCount != 0 && standardWeaponCount == 0 && strategicWeaponCount == 0)
        {
            if (cargoHoldSize * static_cast<double>(1) / 10 - static_cast<double>(defensiveWeaponCount) * defensiveWeapon.GetSize() > 0)
            {
                spaceship.SetWeaponsInfo(weaponsInfo1);
                spaceship.SetDefensiveWeapon(defensiveWeapon);
            }
            else throw std::exception("Not enough space for weapons");
        }
        else if (!WeaponsIsEmpty()) throw std::exception("You cannot create a cargo spaceship with non-defensive type weapons");

        if (landingModulesCount != 0) spaceship.SetLandingModule(landingModule, landingModulesCount);

        spaceship.SetSpaceshipType(ShipsTypes::CARGO);
        return spaceship;

    case ShipsTypes::COLONIZER:
        if (livingModulesCount == 0) throw std::exception("You cannot create a colonizer spaceship without living modules");
        spaceship.SetLivingModule(livingModule, livingModulesCount);

        if (!WeaponsIsEmpty() && strategicWeaponCount == 0 && standardWeaponCount == 0 && defensiveWeaponCount != 0)
        {
            int livingModuleSize = livingModulesCount * livingModule.GetSize();
            if (livingModuleSize * static_cast<double>(1) / 10 - static_cast<double>(defensiveWeapon.GetSize()) * defensiveWeaponCount > 0)
            {
                spaceship.SetWeaponsInfo(weaponsInfo1);
                spaceship.SetDefensiveWeapon(defensiveWeapon);
            }
            else throw std::exception("Not enough space for defensive weapons");
        }
        else if (!WeaponsIsEmpty()) throw std::exception("You cannot create a colonizer spaceship with non-defensive type weapons");

        if (landingModulesCount == 0) throw std::exception("You cannot create a colonizer spaceship without landing modules");
        spaceship.SetLandingModule(landingModule, landingModulesCount);
        spaceship.SetSpaceshipType(ShipsTypes::COLONIZER);
        return spaceship;

    case ShipsTypes::MILITARY_TRANSPORT:
        if (WeaponsIsEmpty() || frame.GetArmor() == 0) throw std::exception("You cannot create a military transport spaceship without armor or weapons");
        if (livingModulesCount == 0) throw std::exception("You cannot create a military transport spaceship without living modules");
        spaceship.SetLivingModule(livingModule, livingModulesCount);

        if (strategicWeaponCount != 0 && standardWeaponCount != 0 && defensiveWeaponCount == 0)
            throw std::exception("You can only create a military transport spaceship with defensive weapons");

        if (static_cast<double>(livingModulesCount) * livingModule.GetSize() * static_cast<double>(2) / 10 - static_cast<double>(defensiveWeapon.GetSize()) * defensiveWeaponCount > 0)
        {
            spaceship.SetWeaponsInfo(weaponsInfo1);
            spaceship.SetDefensiveWeapon(defensiveWeapon);
        }
        else
        {
            weaponsInfo1.at(ArmamentTypes::DEFENSIVE) = 1;
            spaceship.SetWeaponsInfo(weaponsInfo1);
            spaceship.SetDefensiveWeapon(defensiveWeapon);
        }

        if (landingModulesCount == 0) throw std::exception("You cannot create a military transport spaceship without landing modules");
        spaceship.SetLandingModule(landingModule, landingModulesCount);
        spaceship.SetSpaceshipType(ShipsTypes::COLONIZER);
        return spaceship;

    case ShipsTypes::MILITARY_GENERAL:
        if (frame.GetArmor() == 0) throw std::exception("You cannot create a military general spaceship without armor");
        if (livingModulesCount == 0) throw std::exception("You cannot create a military general spaceship without living modules");
        spaceship.SetLivingModule(livingModule, livingModulesCount);

        if (!WeaponsIsEmpty() && strategicWeaponCount == 0 && standardWeaponCount != 0 && defensiveWeaponCount != 0)
        {
            spaceship.SetWeaponsInfo(weaponsInfo1);
            spaceship.SetStandardWeapon(standardWeapon);
            spaceship.SetDefensiveWeapon(defensiveWeapon);
        }
        else throw std::exception("You cannot create a military general spaceship without appropriate weapons");

        if (landingModulesCount != 0) spaceship.SetLandingModule(landingModule, landingModulesCount);
        spaceship.SetSpaceshipType(ShipsTypes::MILITARY_GENERAL);
        return spaceship;

    case ShipsTypes::MILITARY_STRATEGIC:
        if (WeaponsIsEmpty()) throw std::exception("You cannot create a military strategic spaceship without weapons");
        if (livingModulesCount == 0) throw std::exception("You cannot create a military strategic spaceship without living modules");
        spaceship.SetLivingModule(livingModule, livingModulesCount);

        if (strategicWeaponCount != 0 && defensiveWeaponCount != 0)
        {
            spaceship.SetWeaponsInfo(weaponsInfo1);
            spaceship.SetStrategicWeapon(strategicWeapon);
            spaceship.SetDefensiveWeapon(defensiveWeapon);
            if (standardWeaponCount != 0) spaceship.SetStandardWeapon(standardWeapon);
        }
        else throw std::exception("You cannot create a military strategic spaceship without living strategic and defensive weapons");

        if (landingModulesCount != 0) spaceship.SetLandingModule(landingModule, landingModulesCount);
        spaceship.SetSpaceshipType(ShipsTypes::MILITARY_STRATEGIC);
        return spaceship;
    case ShipsTypes::NOT_DEFINED:
        return Spaceship{};
    }
    return Spaceship{};
}