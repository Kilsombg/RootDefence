#ifndef __MapsProgressDTO__
#define __MapsProgressDTO__

#include<string>

struct MapDTO
{
	long id;
	std::string name;
};



struct MapProgressDTO
{
	long mapID;
	long maxWave;
};


#endif // !__MapsProgressDTO__
