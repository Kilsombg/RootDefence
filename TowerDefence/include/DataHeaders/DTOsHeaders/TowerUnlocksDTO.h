#ifndef __TowerUnlocksDTO__
#define __TowerUnlocksDTO__

#include<string>

struct TowerUnlocksDTO
{
	long id;
	std::string name;
	short require_level;
	bool unlocked;
};

#endif // !__TowerUnlocksDTO__
