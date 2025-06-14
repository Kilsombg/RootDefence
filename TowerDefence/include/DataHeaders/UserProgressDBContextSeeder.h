#ifndef __UserProgressDBContextSeeder__
#define __UserProgressDBContextSeeder__

#include "RepositoriesHeaders/GameProgressRepository.h"
#include "RepositoriesHeaders/MapsProgressRepository.h"
#include "RepositoriesHeaders/MapsRepository.h"

#include<memory>
#include<sqlite3.h>

/**
* Seeder class to seed user progress database.
*/
class UserProgressDBContextSeeder
{
public:
	UserProgressDBContextSeeder(
		std::shared_ptr<GameProgressRepository> gameRepo,
		std::shared_ptr<MapsRepository> mapsRepo,
		std::shared_ptr<MapsProgressRepository> mapsProgressRepo
	);

	/**
	* Call this when you want to seed the database. If table has rows it won't seed the table.
	*/
	void seed(sqlite3* db);

private:
	std::shared_ptr<GameProgressRepository> m_gameRepo;
	std::shared_ptr<MapsRepository> m_mapsRepo;
	std::shared_ptr<MapsProgressRepository> m_mapsProgressRepo;
};

#endif // !__UserProgressDBContextSeeder__
