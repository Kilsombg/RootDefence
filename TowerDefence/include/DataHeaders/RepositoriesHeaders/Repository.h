#ifndef __Repository__
#define __Repository__

#include "../RJM_SQLite_HandlersHeaders/RJM_SQLite_Resultset.h"

#include<sqlite3.h>

/**
* Base repository class.
* 
* After writing querry to the databse, you should call validResult() to execute and validate it.
*/
class Repository
{
protected:
	/**
	* Execute and validates sqlite query.
	* 
	* @return true if querry is executed without errors.
	*/
	bool validResult(const char* query, RJM_SQLite_Resultset*& pRS, sqlite3* db);
};

#endif // !__Repository__
