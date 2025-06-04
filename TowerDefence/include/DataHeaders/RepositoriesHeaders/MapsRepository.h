#ifndef __MapsRepository__
#define __MapsRepository__

#include "Repository.h"

#include "../DTOsHeaders/MapsProgressDTO.h"

#include<memory>
#include<vector>
#include<sqlite3.h>

/**
* Repository for maps table in SQLite.
*/
class MapsRepository : public Repository
{
public:
	/**
	* Load all maps from SQLite.
	*
	* @return maps from database or nullptr if there are no DB rows.
	*/
	std::shared_ptr<std::vector<MapDTO>> load(sqlite3* db);
	/**
	* Get single map by id.
	*/
	MapDTO getMapByID(sqlite3* db, long id);
	/**
	* Update map if exists, otherwise insert it.
	*/
	void upsert(sqlite3* db, MapDTO map);
	/**
	* Counts maps in table.
	*/
	int count(sqlite3* db);
};

#endif // !__MapsRepository__
