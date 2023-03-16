#include <iostream>
#include "ModulesFactory1.h"
#include "ModulesFactory2.h"
#include "ShipsTypes.h"
#include "Spaceship.h"
#include "SpaceshipBuilder.h"


int main()
{
    ModulesFactory1 factory;
    SpaceshipBuilder builder;
	Spaceship spaceshipResearch = builder.SetFactory(factory)->SetFrameSize(3)->SetRadarCount(3)->SetStandardEngineSize(15)->
		SetSpaceshipType(ShipsTypes::RESEARCH)->SetDestination(DestinationTypes::SYSTEM)->Build();
    std::cout << spaceshipResearch;

    std::cout << "--------------------------------------------------------------------" << std::endl;
    SpaceshipBuilder builder1;
    Spaceship spaceship_military_strategic = builder1.SetFactory(factory)->SetSpaceshipType(ShipsTypes::MILITARY_STRATEGIC)->SetFrameSize(5)->
		SetDestination(DestinationTypes::SYSTEM)->SetStandardEngineSize(50)->SetRadarCount(1)->SetLivingModulesCount(2)->SetArmamentInfo(ArmamentTypes::DEFENSIVE, 2)->
		SetArmamentInfo(ArmamentTypes::STRATEGIC, 1)->Build();

    std::cout << spaceship_military_strategic;

    std::cout << "--------------------------------------------------------------------" << std::endl;
    SpaceshipBuilder builder3;
    Spaceship spaceship_colonizer = builder3.SetFactory(factory)->SetSpaceshipType(ShipsTypes::COLONIZER)->SetFrameSize(6)->SetStandardEngineSize(50)->SetRadarCount(1)->
		SetLivingModulesCount(5)->SetLandingModulesCount(1)->SetSuperEngineSize(50)->SetArmamentInfo(ArmamentTypes::DEFENSIVE, 1)->
		SetDestination(DestinationTypes::INTERSTELLAR)->Build();
    std::cout << spaceship_colonizer ;

    std::cout << "--------------------------------------------------------------------" << std::endl;

    try
    {
	    SpaceshipBuilder builder4;
	    ModulesFactory2 factory2;
	    builder4.SetFactory(factory2)->SetSpaceshipType(ShipsTypes::COLONIZER)->SetFrameSize(6)->SetStandardEngineSize(50)->SetRadarCount(1)->SetLivingModulesCount(5)->
	             SetLandingModulesCount(1)->SetSuperEngineSize(50)->SetArmamentInfo(ArmamentTypes::DEFENSIVE, 1)->SetDestination(DestinationTypes::INTERSTELLAR)->Build();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
	return 0;
}
