#ifndef __MapsProgressRepository__
#define __MapsProgressRepository__

#include "Repository.h"

#include "../DTOsHeaders/MapsProgressDTO.h"

#include<memory>
#include<vector>
#include<sqlite3.h>

/**
* Repository for map_progress table in SQLite.
*/
class MapsProgressRepository : public Repository
{
public:
	/**
	* Load map progress from SQLite.
	*
	* @return map progress from database or nullptr if there are no DB rows.
	*/
	std::shared_ptr<std::vector<MapProgressDTO>> load(sqlite3* db);
	/**
	* Checks if progression for the map exists.
	*/
	bool exists(sqlite3* db, int mapID);
	/**
	* Update map's progression if exists, otherwise insert it.
	* 
	* @param mapProgress - map's prgoression to be updated. If id of MapProgress is not in table, then it will be inserted.
	*/
	void upsert(sqlite3* db, MapProgressDTO mapProgress);
	/**
	* Update max wave for a map.
	* 
	* @param mapID - map's id that was played.
	* @param maxWave - best wave achieved on that map.
	*/
	void updateMaxWave(sqlite3* db, int mapID, int maxWave);
	/**
	* Delete maps' progress.
	*/
	void deleteProgress(sqlite3* db);
};

#endif // !__MapsProgressRepository__
