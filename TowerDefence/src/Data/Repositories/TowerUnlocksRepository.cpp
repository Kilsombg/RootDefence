#include "../../../include/DataHeaders/RepositoriesHeaders/TowerUnlocksRepository.h"

#include "../../../include/DataHeaders/RJM_SQLite_HandlersHeaders/RJM_SQLite_Resultset.h"

#include<sstream>

std::shared_ptr<std::vector<TowerUnlocksDTO>> TowerUnlocksRepository::loadAll(sqlite3* db)
{
	const char* query = "SELECT id, name, require_level, unlocked FROM tower_unlocks;";
	// validate result
	RJM_SQLite_Resultset* pRS = NULL;
	if (!validResult(query, pRS, db)) return nullptr;

	// get collumns
	int rc = pRS->GetRowCount();
	std::shared_ptr<std::vector<TowerUnlocksDTO>> pTowerUnlocks = nullptr;
	if (rc) pTowerUnlocks = std::make_shared<std::vector<TowerUnlocksDTO>>();

	for (int r = 0; r < rc; r++)
	{
		TowerUnlocksDTO pEl;
		long reqLVLLong, unlockedLong;

		pRS->GetColValueINTEGER(r, 0, &pEl.id);
		pRS->GetColValueVARCHAR(r, 1, &pEl.name);
		pRS->GetColValueINTEGER(r, 2, &reqLVLLong);
		pEl.require_level = (short)reqLVLLong;
		pRS->GetColValueINTEGER(r, 3, &unlockedLong);
		pEl.unlocked = (bool)unlockedLong;

		pTowerUnlocks->push_back(pEl);
	}

	SAFE_DELETE(pRS);

	return pTowerUnlocks;
}

void TowerUnlocksRepository::unlockTower(sqlite3* db, long id)
{
	std::ostringstream query;
	query.str("");
	query << "UPDATE tower_unlocks ";
	query << "SET unlocked = 1 ";
	query << "WHERE id = " << id << ";";

	// validate result
	RJM_SQLite_Resultset* pRS = NULL;
	if (!validResult(query.str().c_str(), pRS, db)) return;

	SAFE_DELETE(pRS);
}

void TowerUnlocksRepository::resetUnlocks(sqlite3* db)
{
	const char* query = "UPDATE tower_unlocks SET unlocked = 0 where unlocked = 1 and id != 1;";

	// validate result
	RJM_SQLite_Resultset* pRS = NULL;
	if (!validResult(query, pRS, db)) return;

	SAFE_DELETE(pRS);
}
