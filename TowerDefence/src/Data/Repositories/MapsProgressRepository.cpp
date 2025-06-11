#include "../../../include/DataHeaders/RepositoriesHeaders/MapsProgressRepository.h"

#include "../../../include/DataHeaders/RJM_SQLite_HandlersHeaders/RJM_SQLite_Resultset.h"

#include<sstream>

std::shared_ptr<std::vector<MapProgressDTO>> MapsProgressRepository::load(sqlite3* db)
{
	const char* query = R"(
		SELECT map_id, max_wave FROM map_progress;
)";
	// validate result
	RJM_SQLite_Resultset* pRS = NULL;
	if (!validResult(query, pRS, db)) return nullptr;

	// get collumns
	int rc = pRS->GetRowCount();
	std::shared_ptr<std::vector<MapProgressDTO>> pMapsProgress = nullptr;
	if (rc != 0) pMapsProgress = std::make_shared<std::vector<MapProgressDTO>>();

	for (int r = 0; r < rc; r++)
	{
		MapProgressDTO mapProgress;
		pRS->GetColValueINTEGER(r, 0, &mapProgress.mapID);
		pRS->GetColValueINTEGER(r, 1, &mapProgress.maxWave);

		pMapsProgress->push_back(mapProgress);
	}

	SAFE_DELETE(pRS);
	return pMapsProgress;
}

bool MapsProgressRepository::exists(sqlite3* db, int mapID)
{
	std::ostringstream query;
	query.str("");
	query << "SELECT 1 FROM map_progress ";
	query << "WHERE map_id = " << mapID << " LIMIT 1;";

	// validate result
	RJM_SQLite_Resultset* pRS = NULL;
	if (!validResult(query.str().c_str(), pRS, db)) return false;

	// get rows count
	int rc = pRS->GetRowCount();
	return rc != 0;
}

void MapsProgressRepository::upsert(sqlite3* db, MapProgressDTO mapProgress)
{
	std::ostringstream query;
	query.str("");
	query << "INSERT INTO map_progress(map_id, max_wave) ";
	query << "VALUES(" << mapProgress.mapID << "," << mapProgress.maxWave << ") ";
	query << "ON CONFLICT(map_id) ";
	query << "DO UPDATE SET max_wave = excluded.max_wave;";

	// validate result
	RJM_SQLite_Resultset* pRS = NULL;
	if (!validResult(query.str().c_str(), pRS, db)) return;

	SAFE_DELETE(pRS);
}

void MapsProgressRepository::updateMaxWave(sqlite3* db, int mapID, int maxWave)
{
	std::ostringstream query;
	query.str("");
	query << "UPDATE map_progress ";
	query << "SET max_wave = " << maxWave << " ";
	query << "WHERE map_id = " << mapID << " AND max_wave < " << maxWave << ";";

	// validate result
	RJM_SQLite_Resultset* pRS = NULL;
	if (!validResult(query.str().c_str(), pRS, db)) return;

	SAFE_DELETE(pRS);
}

void MapsProgressRepository::deleteProgress(sqlite3* db)
{
	const char* query = "DELETE FROM map_progress;";

	// validate result
	RJM_SQLite_Resultset* pRS = NULL;
	if (!validResult(query, pRS, db)) return;

	SAFE_DELETE(pRS);
}
