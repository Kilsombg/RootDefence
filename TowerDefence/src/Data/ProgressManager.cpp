#include "../../include/DataHeaders/ProgressManager.h"

#include "../../include/DataHeaders/UserProgressDBContextSeeder.h"

#include<iostream>

ProgressManager::ProgressManager(std::shared_ptr<GameProgressRepository> gameRepo,
	std::shared_ptr<MapsRepository> mapsRepo,
	std::shared_ptr<MapsProgressRepository> mapsProgressRepo,
	std::shared_ptr<UserProgressDBContext> dbContext) :
	m_gameRepo(gameRepo), m_mapsRepo(mapsRepo), m_mapsProgressRepo(mapsProgressRepo), m_dbContext(dbContext)
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
		// m_dbContext.createTables();
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

	return true;
}

void ProgressManager::deleteProgress()
{
	sqlite3* db = m_dbContext->getDB();

	// delete game progress
	if (m_gameProgress != nullptr) {
		m_gameRepo->upsert(db, GameProgressDTO{ 1, 0 });
		m_gameProgress = m_gameRepo->load(db);
	}

	// delete maps' progress
	if (!m_mapsProgress->empty())
	{
		for (const MapDTO& map : *m_maps) {
			if (m_mapsProgressRepo->exists(db, map.id)) {
				m_mapsProgressRepo->upsert(db, MapProgressDTO{ map.id, 0 });
			}
		}
		m_mapsProgress = m_mapsProgressRepo->load(db);
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
