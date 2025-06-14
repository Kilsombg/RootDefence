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
	* 
	* @param gameProgress - game progress you want to upsert. If gameProgress' id is not in table, then it will be inserted.
	*/
	void upsert(sqlite3* db, GameProgressDTO gameProgress);
	/**
	* Update coins in game progress.
	* 
	* @param id - id of the gmaeProgress row in database.
	* @param coins - amount of coins to be updated.
	*/
	void updateCoins(sqlite3* db, int id, int coins);
	/**
	* Delete game progress.
	* 
	* @param id - id of the gmaeProgress row in database.
	*/
	void deleteProgress(sqlite3* db, int id);
};

#endif // !__GameProgressRepository__
