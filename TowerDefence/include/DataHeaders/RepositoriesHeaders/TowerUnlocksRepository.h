#ifndef __TowerUnlocksRepository__
#define __TowerUnlocksRepository__

#include "Repository.h"

#include "../DTOsHeaders/TowerUnlocksDTO.h"

#include<sqlite3.h>
#include<memory>
#include<vector>

/**
* Repository for tower unlocks.
*/
class TowerUnlocksRepository : public Repository
{
public:
	/**
	* Load all tower unlocks.
	*/
	std::shared_ptr<std::vector<TowerUnlocksDTO>> loadAll(sqlite3 * db);
	/**
	* Unlock tower when leveling up.
	*/
	void unlockTower(sqlite3* db, long id);
	/**
	* reset unlocks.
	*/
	void resetUnlocks(sqlite3* db);
};

#endif // !__TowerUnlocksRepository__
