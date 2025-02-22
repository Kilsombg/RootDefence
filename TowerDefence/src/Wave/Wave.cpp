#include "../../include/WaveHeaders/Wave.h"

Wave::Wave()
{
}

Wave::~Wave()
{
}

Timer& Wave::getSpawnTimer()
{
	return m_spawnTimer;
}

Timer& Wave::getRoundTimer()
{
	return m_roundTimer;
}

std::vector<EnemyCluster>& Wave::getEnemyClusters()
{
	return m_enemyClusters;
}

void Wave::clean()
{
}

void to_json(json& j, const EnemyCluster& ec)
{
	j = json{ {WaveConstans::enemyType, ec.enemyType}, {WaveConstans::count, ec.count} };
}

// parse EnemyCluster from nlohmann json
void from_json(const json& j, EnemyCluster& ec)
{
	if (j.contains(WaveConstans::enemyType)) j.at(WaveConstans::enemyType).get_to(ec.enemyType);
	if (j.contains(WaveConstans::count)) j.at(WaveConstans::count).get_to(ec.count);
}

// convert Wave into nlohmann json
void to_json(json& j, const Wave& w)
{
	j = json{
		{WaveConstans::spawnInterval, w.m_spawnInterval},
		{WaveConstans::roundInterval, w.m_roundInterval},
		{WaveConstans::enemyClusters, json::array()}
	};

	for (const auto& cluster : w.m_enemyClusters) {
		j[WaveConstans::enemyClusters].push_back(cluster);
	}
}

// parse Wave from nlohmann json
void from_json(const json& j, Wave& w)
{
	if (j.contains(WaveConstans::spawnInterval)) {
		j.at(WaveConstans::spawnInterval).get_to(w.m_spawnInterval);
		w.m_spawnTimer = Timer(w.m_spawnInterval, w.m_spawnInterval);
	}

	if (j.contains(WaveConstans::roundInterval)) {
		j.at(WaveConstans::roundInterval).get_to(w.m_roundInterval);
		w.m_roundTimer = Timer(w.m_roundInterval, w.m_roundInterval);
	}

	if (j.contains(WaveConstans::enemyClusters))
	{
		for (const auto& item : j.at(WaveConstans::enemyClusters)) {
			w.m_enemyClusters.push_back(item.get<EnemyCluster>());
		}
	}
}