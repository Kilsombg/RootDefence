#ifndef __Wave__
#define __Wave__

#include "../Constants/WaveConstans.h"

#include "../UtilsHeaders/Timer.h"

#include<string>
#include<vector>
#include<memory>

#include<nlohmann\json.hpp>
using json = nlohmann::json;

struct EnemyCluster
{
	std::string enemyType;
	int count;
};

class Wave
{
public:
	Wave();
	~Wave();

	Timer& getSpawnTimer();
	Timer& getRoundTimer();

	std::vector<EnemyCluster>& getEnemyClusters();

	void clean();

private:
	Timer m_spawnTimer, m_roundTimer;
	float m_spawnInterval, m_roundInterval;
	std::vector<EnemyCluster> m_enemyClusters;

	friend void to_json(json& j, const Wave& w);
	friend void from_json(const json& j, Wave& w);
};


void to_json(json& j, const EnemyCluster& ec);
void from_json(const json& j, EnemyCluster& ec);

void to_json(json& j, const Wave& w);
void from_json(const json& j, Wave& w);

void to_json(json& j, const std::vector<Wave*>& waves);
void from_json(const json& j, std::vector<Wave*>& waves);

#endif // !__Wave__
