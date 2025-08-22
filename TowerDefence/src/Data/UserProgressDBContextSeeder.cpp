#include "../../include/DataHeaders/UserProgressDBContextSeeder.h"

UserProgressDBContextSeeder::UserProgressDBContextSeeder(
	std::shared_ptr<GameProgressRepository> gameRepo,
	std::shared_ptr<MapsRepository> mapsRepo,
	std::shared_ptr<MapsProgressRepository> mapsProgressRepo) :
	m_gameRepo(gameRepo), m_mapsRepo(mapsRepo), m_mapsProgressRepo(mapsProgressRepo)
{
}

void UserProgressDBContextSeeder::seed(sqlite3* db)
{
	// Seed maps if not present
	if (m_mapsRepo->count(db) == 0) {
		m_mapsRepo->upsert(db, { 1, "Pondside path" });
		m_mapsRepo->upsert(db, { 2, "Crescent cliff" });
		m_mapsRepo->upsert(db, { 3, "Looping turn" });
	}

	// Seed game_progress for user
	if (!m_gameRepo->exists(db)) {
		m_gameRepo->upsert(db, GameProgressDTO{ 1, 0, 0, 1 });
	}

	// Seed map_progress for each map
	std::shared_ptr<std::vector<MapDTO>> maps = m_mapsRepo->load(db);
	for (const MapDTO& map : *maps) {
		if (!m_mapsProgressRepo->exists(db, map.id)) {
			m_mapsProgressRepo->upsert(db, MapProgressDTO{ map.id, 0 });
		}
	}
}
