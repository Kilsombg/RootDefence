#ifndef __PlayState__
#define __PlayState__

#include "GameState.h"

#include "../EntitiesHeaders/GameObject.h"
#include "../EntitiesHeaders/SDLGameObject.h"
#include "../EntitiesHeaders/Enemy.h"
#include "../EntitiesHeaders/Button.h"

#include "../MapHeaders/Level.h"

#include "../../include/UtilsHeaders/TowerFactory.h"
#include "../../include/EventHandlersHeaders/ClickToPlaceTowerHandler.h"

#include "../WaveHeaders/WaveManager.h"
#include "../WaveHeaders/Wave.h"

#include<vector>
#include<memory>
#include<functional>

class PlayState : public GameState
{
public:
	PlayState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	void loadData();

	virtual std::string getStateID() const;

	void addEnemy(std::unique_ptr<Enemy> enemy);
	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);


private:
	void updateObjects();
	void handleEvents();

	typedef std::function<void(Button*)> TowerButtonCallback;
	void setTowerButtonCallbacks(const std::map<std::string, TowerButtonCallback>& towerButtonCallbacks);

	std::map<std::string, TowerButtonCallback> m_towerButtonCallbacks;

	std::shared_ptr<Level> pLevel;
	std::vector<std::unique_ptr<Enemy>> m_enemyObjects;

	std::shared_ptr<WaveManager> m_waveManager;
	Wave* m_currentWave;

	std::shared_ptr<TowerFactory> m_towerFactory;
	ClickToPlaceTowerHandler* m_clickToPlaceTowerHandler;
};

#endif // !__PlayState__
