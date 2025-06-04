#include "../../../include/DataHeaders/RepositoriesHeaders/MapsRepository.h"

#include "../../../include/DataHeaders/RJM_SQLite_HandlersHeaders/RJM_SQLite_Resultset.h"

#include<iostream>
#include<sstream>

std::shared_ptr<std::vector<MapDTO>> MapsRepository::load(sqlite3* db)
{
	const char* query = "SELECT id, name FROM maps;";
	// validate result
	RJM_SQLite_Resultset* pRS = NULL;
	if (!validResult(query, pRS, db)) return nullptr;

	// get collumns
	int rc = pRS->GetRowCount();
	std::shared_ptr<std::vector<MapDTO>> pMaps = nullptr;
	if (rc != 0) pMaps = std::make_shared<std::vector<MapDTO>>();

	for (int r = 0; r < rc; r++)
	{
		MapDTO map;
		pRS->GetColValueINTEGER(r, 0, &map.id);
		pRS->GetColValueVARCHAR(r, 1, &map.name);

		pMaps->push_back(map);
	}

	SAFE_DELETE(pRS);
	return pMaps;
}

MapDTO MapsRepository::getMapByID(sqlite3* db, long id)
{
	std::ostringstream query;
	query << "SELECT id, name FROM maps WHERE id =" << id << ";";
	// validate result
	RJM_SQLite_Resultset* pRS = NULL;
	if (!validResult(query.str().c_str(), pRS, db)) return MapDTO();

	// get collumns
	int rc = pRS->GetRowCount();

	// project data into map
	MapDTO map;
	pRS->GetColValueINTEGER(0, 0, &map.id);
	pRS->GetColValueVARCHAR(0, 1, &map.name);

	SAFE_DELETE(pRS);
	return map;
}

void MapsRepository::upsert(sqlite3* db, MapDTO map)
{
	std::ostringstream query;
	query.str("");
	query << "INSERT INTO maps(id, name) ";
	query << "VALUES(" << map.id << ",'" << map.name << "') ";
	query << "ON CONFLICT(id) ";
	query << "DO UPDATE SET name = excluded.name;";

	// validate result
	RJM_SQLite_Resultset* pRS = NULL;
	if (!validResult(query.str().c_str(), pRS, db)) return;

	SAFE_DELETE(pRS);
}

int MapsRepository::count(sqlite3* db)
{
	const char* query = "SELECT COUNT(*) FROM maps;";

	// validate result
	RJM_SQLite_Resultset* pRS = NULL;
	if (!validResult(query, pRS, db)) return 0;

	// get maps count
	int rc = pRS->GetRowCount();
	long count;
	pRS->GetColValueINTEGER(0, 0, &count);

	SAFE_DELETE(pRS);
	return (int)count;
}
