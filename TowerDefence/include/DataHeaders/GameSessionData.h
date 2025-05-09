#ifndef __GameSessionData__
#define __GameSessionData__

#include<array>
#include<string>
#include<iostream>

/**
* ResourceType constants
*/
namespace ResourceTypeConst {
	constexpr char green[] = "GREEN";
	constexpr char yellow[] = "YELLOW";
	constexpr char red[] = "RED";
}

/**
* Resource is used in buying towers and tower upgrades.
* Drops from corresponding color enemies.
*/
enum ResourceType
{
	GREEN = 0,
	YELLOW = 1,
	RED = 2,
	NOT_RESOURCE_TYPE
};


inline ResourceType getResourceTypeByString(std::string resourceType)
{
	if (resourceType == ResourceTypeConst::green) return ResourceType::GREEN;
	if (resourceType == ResourceTypeConst::yellow) return ResourceType::YELLOW;
	if (resourceType == ResourceTypeConst::red) return ResourceType::RED;

	std::cout << "ResourceType: " << resourceType << " not found.\n";
	return NOT_RESOURCE_TYPE;
}


/**
* Resource keeps track of the type and value of the resource.
*/
struct Resource
{
	ResourceType type;
	int value;
};


/**
* ArrayOfResources is a type that can hold all of the ResourceTypes data.
*/
typedef std::array<Resource, 3> ArrayOfResources;


/**
* GameSessionData is used to store data for a game session
*/
struct GameSessionData
{
	// health
	int gameHealth;
	// keep track of all the resources in the session
	ArrayOfResources resources;
	// current wave level
	int currentWaveLevel;
};



#endif // !__GameSessionData__
