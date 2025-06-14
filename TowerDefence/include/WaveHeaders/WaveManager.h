#ifndef __WaveManager__
#define __WaveManager__

#include "Wave.h"

#include "../EntitiesHeaders/Enemy.h"

#include "../UtilsHeaders/GameObjectData.h"
#include "../UtilsHeaders/Timer.h"

#include<vector>
#include<memory>
#include<functional>

/**
* Manages waves.
* 
* Calls current wave and spawns enemies.
* When wave finished it calls next wave.
* 
* When waves finished it calls GameStateMachine to switch state.
*/
class WaveManager
{
public:
	static std::shared_ptr<WaveManager> Instance();
	/**
	* Activates wave if there is not current wave playing.
	*/
	static void s_activateWave();
	/**
	* @return true if play button is ready to be clicked.
	*/
	static bool isActivePlayButton();
	/**
	* Spawn enemies from wave.
	* Calls nextWave() when wave finished and clicked on start button.
	*/
	void spawnWaveEnemies(std::vector<std::shared_ptr<Vector2D>>& enemyPath, Wave& wave, std::function<void(std::unique_ptr<Enemy>)> addEnemyCallback, float dT);
	/**
	* Change wave.
	*/
	void nextWave(Wave& wave);
	/**
	* Cheks if current wave is final.
	*/
	bool isFinalWave();
	/**
	* Loads manager.
	*/
	void load();
	/**
	* Clean manager.
	*/
	void clean();
	/**
	* Handles victory state.
	*/
	void handleEvents();

	// getters and setters

	void setGameObjectData(GameObjectData<LoaderParams>& gameObjectdata);

	void setEnemyObjects(std::shared_ptr<std::vector<std::shared_ptr<Enemy>>> pEnemiesObjects);

	int getCurrentWaveID();

	std::vector<Wave*>& getWaves();

	void setMapID(int mapID);

private:
	WaveManager();
	static std::shared_ptr<WaveManager> s_pInstance;
	static bool s_pressedPlayButton; // used to start wave spawning.
	static bool s_hasNoEnemiesOnScreen; // flag for checking if there are any enemies in PlayState. True if there is enemies, otherwise - false.

	int m_maxWave; // the maximum wave that we define in our data
	int m_currentWaveID; // which wave is currently played
	bool m_stoppedWaveAfterEnd; // flag for stopping wave after end. 
	std::vector<Wave*> m_waves;
	std::vector<EnemyCluster>* m_eClusters; // waves' enemies clusters

	int m_mapID; // map's id that is played
	std::unique_ptr<GameObjectData<LoaderParams>> m_gameObjectData; // base enemy stats
	std::shared_ptr<std::vector<std::shared_ptr<Enemy>>> m_enemyObjects; // pointer to enemies in playState
};

typedef WaveManager TheWaveManager;

#endif // !__WaveManager__
