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
	
	static void s_activateWave();

	void spawnWaveEnemies(std::vector<std::shared_ptr<Vector2D>>& enemyPath, Wave& wave, std::function<void(std::unique_ptr<Enemy>)> addEnemyCallback, float dT);
	void nextWave(Wave& wave);
	bool isFinalWave();

	void load();
	void clean();
	
	// getters and setters

	void setGameObjectData(GameObjectData<LoaderParams>& gameObjectdata);

	int getCurrentWaveID();

	std::vector<Wave*>& getWaves();

	bool getPressedPlayButton();

private:
	WaveManager();
	static std::shared_ptr<WaveManager> s_pInstance;
	static bool s_pressedPlayButton; // used to start wave spawning.

	int m_maxWave; // the maximum wave that we define in our data
	int m_currentWaveID; // which wave is currently played
	bool m_stoppedWaveAfterEnd; // flag for stopping wave after end. 
	std::vector<Wave*> m_waves;

	std::unique_ptr<GameObjectData<LoaderParams>> m_gameObjectData; // base enemy stats
};

typedef WaveManager TheWaveManager;

#endif // !__WaveManager__
