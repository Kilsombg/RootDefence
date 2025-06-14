#ifndef __MapsProgressDTO__
#define __MapsProgressDTO__

#include<string>

/**
* DTO struct for storing map's information.
*/
struct MapDTO
{
	long id;
	std::string name;
};


/**
* DTO struct for storing map's progression.
*/
struct MapProgressDTO
{
	long mapID;
	long maxWave; // best wave achieved
};


#endif // !__MapsProgressDTO__
