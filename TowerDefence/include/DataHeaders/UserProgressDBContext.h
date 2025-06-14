#ifndef __UserProgressDBContext__
#define __UserProgressDBContext__

#include<sqlite3.h>
#include<string>
#include<memory>

/**
* DBContext for SQLite database.
*
* ProgressManager::loadAll() automatically calls open() to open the connection to the databse.
* You don't need to call it outside.
*
* When you finish working with UserProgressDBContext, call clean() or call ProgressManager::closeDB().
*/
class UserProgressDBContext
{
public:
	/**
	* Open connection to database.
	* 
	* @return false if failed to open DB.
	*/
	bool open(const std::string dbPath);
	/**
	* Close connection to database if not already.
	*/
	void close();
	/**
	* Return database.
	*/
	sqlite3* getDB() const;
	/**
	* Check if a table exists.
	*
	* @param name of the table.
	*
	* @return true if tables exists.
	*/
	bool tableExists(const std::string& tableName);
	/**
	* Create tables if there are not present.
	*/
	void createTables();

private:
	sqlite3* m_db = nullptr;
};

#endif // !__UserProgressDBContext__
