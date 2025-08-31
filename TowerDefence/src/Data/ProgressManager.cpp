#include "../../include/DataHeaders/ProgressManager.h"

#include "../../include/DataHeaders/UserProgressDBContextSeeder.h"

#include<iostream>
#include<thread>

ProgressManager::ProgressManager(std::shared_ptr<GameProgressRepository> gameRepo,
	std::shared_ptr<MapsRepository> mapsRepo,
	std::shared_ptr<MapsProgressRepository> mapsProgressRepo,
	std::shared_ptr<TowerUnlocksRepository> towerUnlocksRepo,
	std::shared_ptr<UserProgressDBContext> dbContext) :
	m_gameRepo(gameRepo), m_mapsRepo(mapsRepo), m_mapsProgressRepo(mapsProgressRepo), m_towerUnlocksRepo(towerUnlocksRepo), m_dbContext(dbContext)
{
}

bool ProgressManager::loadAll(const std::string& dbPath)
{
	// open database
	if (!m_dbContext->open(dbPath)) return false;

	// check if tables exists
	if (!m_dbContext->tableExists("game_progress") || !m_dbContext->tableExists("maps") || !m_dbContext->tableExists("map_progress"))
	{
		std::cout << "A table in db is not present.\n";
		// Create tables - rurn this only if tables doesn't exists
		// Uncomment ONLY if there are no tables present
		m_dbContext->createTables();
		//m_dbContext->seedProgressTables();
	}

	sqlite3* db = m_dbContext->getDB();

	// seed if needed
	UserProgressDBContextSeeder seeder(m_gameRepo, m_mapsRepo, m_mapsProgressRepo);
	seeder.seed(db);

	// load data from database
	m_gameProgress = m_gameRepo->load(db);
	m_maps = m_mapsRepo->load(db);
	m_mapsProgress = m_mapsProgressRepo->load(db);
	m_towerUnlocks = m_towerUnlocksRepo->loadAll(db);

	return true;
}

void ProgressManager::deleteProgress()
{
	sqlite3* db = m_dbContext->getDB();

	// delete game progress
	if (m_gameProgress != nullptr) {
		m_gameRepo->upsert(db, GameProgressDTO{ 1, 0 , 0, 1 });
		m_gameProgress = m_gameRepo->load(db);
	}

	// delete maps' progress
	if (!m_mapsProgress->empty())
	{
		m_mapsProgressRepo->resetProgress(db);
	}
	m_mapsProgress = m_mapsProgressRepo->load(db);

	// delete tower unlocks
	m_towerUnlocksRepo->resetUnlocks(db);
	for (std::vector<TowerUnlocksDTO>::size_type i = 1; i < m_towerUnlocks->size(); i++)
	{
		(*m_towerUnlocks)[i].unlocked = false;
	}
}

void ProgressManager::closeDB()
{
	m_dbContext->close();
}

std::shared_ptr<GameProgressDTO> ProgressManager::getGameProgress() const
{
	return m_gameProgress;
}

void ProgressManager::updateCoins(int id, int coins)
{
	// update loaded data
	m_gameProgress->coins = coins;

	// update database
	m_gameRepo->updateCoins(m_dbContext->getDB(), id, coins);
}

void ProgressManager::updateLoadedLevel(int id, long level_xp, int level)
{
	// update loaded data
	m_gameProgress->level_xp = level_xp;
	m_gameProgress->level = level;
}

void ProgressManager::updateLevelToDB(int id)
{
	m_gameRepo->updateLevel(m_dbContext->getDB(), id, m_gameProgress->level_xp, m_gameProgress->level);
}

std::shared_ptr<std::vector<MapDTO>> ProgressManager::getMaps() const
{
	return m_maps;
}

MapDTO ProgressManager::getMapByID(long id)
{
	return MapDTO();
}

void ProgressManager::upsertMap(MapDTO map)
{
	m_mapsRepo->upsert(m_dbContext->getDB(), map);
}

std::shared_ptr<std::vector<MapProgressDTO>> ProgressManager::getMapsProgress() const
{
	return m_mapsProgress;
}

void ProgressManager::updateMaxWave(int mapID, int maxWave)
{
	long currentMaxWave = (*m_mapsProgress)[mapID - 1].maxWave;

	if (currentMaxWave < maxWave)
	{
		// update loaded data
		(*m_mapsProgress)[mapID - 1].maxWave = maxWave;

		// update database
		m_mapsProgressRepo->updateMaxWave(m_dbContext->getDB(), mapID, maxWave);
	}
}

void ProgressManager::unlockTower(long id)
{
	(*m_towerUnlocks)[id - 1].unlocked = true;

	std::thread([this, id]() {
		m_towerUnlocksRepo->unlockTower(m_dbContext->getDB(), id);
		}).detach();
}

std::shared_ptr<std::vector<TowerUnlocksDTO>> ProgressManager::getTowerUnlocks()
{
	return m_towerUnlocks;
}
