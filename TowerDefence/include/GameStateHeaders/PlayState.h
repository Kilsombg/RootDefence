#ifndef __PlayState__
#define __PlayState__

#include "GameState.h"

#include "../DataHeaders/GameSessionData.h"

#include "../EntitiesHeaders/Enemy.h"

#include "../ManagersHeaders/PurchaseManager.h"
#include "../ManagersHeaders/SellManager.h"
#include "../ManagersHeaders/CollisionManager.h"

#include "../MapHeaders/Level.h"

#include "../UIHeaders/PlayStateUIHeaders/PlayStateUI.h"

#include "../UtilsHeaders/TowerFactory.h"
#include "../UtilsHeaders/ProjectileManager.h"

#include "../WaveHeaders/WaveManager.h"
#include "../WaveHeaders/Wave.h"

#include<vector>
#include<memory>
#include<string>

class PlayState : public GameState
{
public:
	PlayState();

	virtual void update() override;
	virtual void render() override;

	virtual bool onEnter() override;
	virtual bool onExit() override;

	/**
	* Load data needed for playstate
	*/
	void loadData();

	void addEnemy(std::unique_ptr<Enemy> enemy);

	void handleEvents() override;

	// getter and setters

	virtual std::string getStateID() const;

	static void setMapLevelPath(std::string mapLevelPath);

	static void setMapID(int mapID);

private:
	// update all objects
	void updateObjects();
	// update enemies
	void updateEnemyObjects();
	//create a blank session data
	void loadGameSessionData();
	// load needed data for towers
	void loadTowerData();	

	std::shared_ptr<Level> pLevel;
	static std::string	s_mapLevelPath; // path to level's map file
	static int s_mapID; // map's id that is played

	std::shared_ptr<std::vector<std::shared_ptr<Tower>>> m_towersObjects;

	std::shared_ptr<std::vector<std::shared_ptr<Enemy>>> m_enemyObjects;

	std::shared_ptr<WaveManager> m_waveManager;
	Wave* m_currentWave;

	std::shared_ptr<PurchaseManager> m_purchaseManager;

	std::shared_ptr<SellManager> m_sellManager;

	std::shared_ptr<CollisionManager> m_collisionManager;

	std::shared_ptr<TowerFactory> m_towerFactory;

	std::shared_ptr<ProjectileManager> m_projectileManager;

	std::unique_ptr<PlayStateUI> m_playStateUI;

	std::shared_ptr<GameSessionData> m_gameSessionData;
};

#endif // !__PlayState__
