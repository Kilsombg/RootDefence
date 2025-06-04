#include "../../../include/DataHeaders/RepositoriesHeaders/Repository.h"

#include<iostream>

bool Repository::validResult(const char* query, RJM_SQLite_Resultset*& pRS, sqlite3* db)
{
	pRS = SQL_Execute(query, db);
	if (!pRS->Valid()) {
		std::cout << "Invalid result set returned " << pRS->GetLastError() << '\n';
		SAFE_DELETE(pRS);
		sqlite3_close(db);
		return false;
	};
	return true;
}
