#include "../../../include/DataHeaders/RepositoriesHeaders/GameProgressRepository.h"

#include "../../../include/DataHeaders/RJM_SQLite_HandlersHeaders/RJM_SQLite_Resultset.h"

#include<iostream>

std::shared_ptr<GameProgressDTO> GameProgressRepository::load(sqlite3* db)
{
	const char* query = "SELECT id, coins FROM game_progress;";
	// validate result
	RJM_SQLite_Resultset* pRS = NULL;
	if (!validResult(query, pRS, db)) return nullptr;

	// get collumns
	int rc = pRS->GetRowCount();
	std::shared_ptr<GameProgressDTO> pGameProgress = nullptr;
	if (rc != 0) pGameProgress = std::make_shared<GameProgressDTO>();

	for (int r = 0; r < rc; r++)
	{
		pRS->GetColValueINTEGER(r, 0, &pGameProgress->id);
		pRS->GetColValueINTEGER(r, 1, &pGameProgress->coins);
	}

	SAFE_DELETE(pRS);

	return pGameProgress;
}

void GameProgressRepository::deleteProgress(sqlite3* db, int id)
{
	std::ostringstream query;
	query.str("");
	query << "DELETE FROM game_progress ";
	query << "WHERE id = " << id << ";";

	// validate result
	RJM_SQLite_Resultset* pRS = NULL;
	if (!validResult(query.str().c_str(), pRS, db)) return;

	SAFE_DELETE(pRS);
}

void GameProgressRepository::updateCoins(sqlite3* db, int id, int coins)
{
	std::ostringstream query;
	query.str("");
	query << "UPDATE game_progress ";
	query << "SET coins = " << coins << " ";
	query << "WHERE id = " << id << ";";

	// validate result
	RJM_SQLite_Resultset* pRS = NULL;
	if (!validResult(query.str().c_str(), pRS, db)) return;

	SAFE_DELETE(pRS);
}

void GameProgressRepository::upsert(sqlite3* db, GameProgressDTO gameProgress)
{
	std::ostringstream query;
	query.str("");
	query << "INSERT INTO game_progress(id, coins)";
	query << "VALUES(" << gameProgress.id << ",'" << gameProgress.coins << "')";
	query << "ON CONFLICT(id)";
	query << "DO UPDATE SET coins = excluded.coins;";

	// validate result
	RJM_SQLite_Resultset* pRS = NULL;
	if (!validResult(query.str().c_str(), pRS, db)) return;

	SAFE_DELETE(pRS);
}


bool GameProgressRepository::exists(sqlite3* db)
{
	const char* query = "SELECT 1 FROM game_progress LIMIT 1;";
	// validate result
	RJM_SQLite_Resultset* pRS = NULL;
	if (!validResult(query, pRS, db)) return false;

	// get rows count
	int rc = pRS->GetRowCount();
	return rc != 0;
}