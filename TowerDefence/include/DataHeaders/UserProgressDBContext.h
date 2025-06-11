#ifndef __UserProgressDBContext__
#define __UserProgressDBContext__

#include<sqlite3.h>
#include<string>
#include<memory>

/**
* DBContext for SQLite database.
*
* To use this context first you need to gather user from database.
* Invoke load() to load user progress from database.
*
* When you finish working with UserProgressDBContext, call clean().
*/
class UserProgressDBContext
{
public:
	/**
	* Open connection to database.
	*/
	bool open(const std::string dbPath);
	/**
	* Close connection to database.
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
