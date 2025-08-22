#include "../../include/DataHeaders/UserProgressDBContext.h"

#include "../../include/DataHeaders/RJM_SQLite_HandlersHeaders/RJM_SQLite_Resultset.h"

#include<iostream>
#include<sstream>

bool UserProgressDBContext::open(const std::string dbPath)
{
	if (sqlite3_open(dbPath.c_str(), &m_db) != SQLITE_OK)
	{
		std::cout << "Failed to open DB: " << sqlite3_errmsg(m_db) << "\n";
		sqlite3_close(m_db);
		return false;
	}
	return true;
}

void UserProgressDBContext::close()
{
	if (m_db) {
		sqlite3_close(m_db);
		m_db = nullptr;
	}
}

sqlite3* UserProgressDBContext::getDB() const
{
	return m_db;
}

bool UserProgressDBContext::tableExists(const std::string& tableName)
{
	std::string query = "SELECT name FROM sqlite_master WHERE type='table' AND name=?;";
	sqlite3_stmt* stmt = nullptr;
	if (sqlite3_prepare_v2(m_db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
	{
		return false;
	}

	sqlite3_bind_text(stmt, 1, tableName.c_str(), -1, SQLITE_STATIC);

	bool exists = (sqlite3_step(stmt) == SQLITE_ROW);
	sqlite3_finalize(stmt);
	return exists;
}

void UserProgressDBContext::createTables()
{
	if (!m_db) return;

	const char* query = R"(
        CREATE TABLE IF NOT EXISTS game_progress (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            coins INTEGER DEFAULT 0,
			level_xp INTEGER NOT NULL DEFAULT 0,
			level INTEGER NOT NULL DEFAULT 1
        );

        CREATE TABLE IF NOT EXISTS maps (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT UNIQUE NOT NULL
        );

        CREATE TABLE IF NOT EXISTS map_progress (
            map_id INTEGER NOT NULL PRIMARY KEY,
            max_wave INTEGER DEFAULT 0,
            FOREIGN KEY(map_id) REFERENCES maps(id)
        );
    )";

	// validate result
	RJM_SQLite_Resultset* pRS = NULL;
	pRS = SQL_Execute(query, m_db);
	if (!pRS->Valid()) {
		std::cout << "Invalid result set returned " << pRS->GetLastError() << '\n';
		SAFE_DELETE(pRS);
		sqlite3_close(m_db);
		return;
	};

	SAFE_DELETE(pRS);
}