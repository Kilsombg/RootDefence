#ifndef __Repository__
#define __Repository__

#include "../RJM_SQLite_HandlersHeaders/RJM_SQLite_Resultset.h"

#include<sqlite3.h>

/**
* Base repository class.
*/
class Repository
{
protected:
	/**
	* Validates sqlite query.
	*/
	bool validResult(const char* query, RJM_SQLite_Resultset*& pRS, sqlite3* db);
};

#endif // !__Repository__
