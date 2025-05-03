#ifndef __WaveManager__
#define __WaveManager__

#include "Wave.h"

#include "../EntitiesHeaders/Enemy.h"

#include "../UtilsHeaders/GameObjectData.h"
#include "../UtilsHeaders/Timer.h"

#include<vector>
#include<memory>
#include<functional>

class WaveManager
{
public:
	static std::shared_ptr<WaveManager> Instance();

	void spawnWaveEnemies(std::vector<std::shared_ptr<Vector2D>>& enemyPath, Wave& wave, std::function<void(std::unique_ptr<Enemy>)> addEnemyCallback, float dT);
	void nextWave(Wave& wave);
	bool isFinalWave();

	void load();
	void setGameObjectData(GameObjectData& gameObjectdata);

	std::vector<Wave*>& getWaves();
	void clean();

private:
	WaveManager();
	static std::shared_ptr<WaveManager> s_pInstance;

	int m_maxWave; // the maximum wave that we define in our data
	int m_currentWaveID;
	std::vector<Wave*> m_waves;

	std::unique_ptr<GameObjectData> m_gameObjectData; // base enemy stats
};

typedef WaveManager TheWaveManager;

#endif // !__WaveManager__
