#ifndef __GameProgressRepository__
#define __GameProgressRepository__

#include "Repository.h"

#include "../DTOsHeaders/GameProgressDTO.h"

#include<sqlite3.h>
#include<memory>

/**
* Repository for game_progress table in SQLite.
*/
class GameProgressRepository : public Repository
{
public:
	/**
	* Load game progress from SQLite.
	*
	* @return game progress from database or nullptr if there are no DB rows.
	*/
	std::shared_ptr<GameProgressDTO> load(sqlite3* db);
	/**
	* Check if there is a row in table.
	*/
	bool exists(sqlite3* db);
	/**
	* Update game progress if exists, otherwise insert it.
	*/
	void upsert(sqlite3* db, GameProgressDTO gameProgress);
	/**
	* Update coins in game progress.
	*/
	void updateCoins(sqlite3* db, int id, int coins);
	/**
	* Delete game progress.
	*/
	void deleteProgress(sqlite3* db, int id);
};

#endif // !__GameProgressRepository__
