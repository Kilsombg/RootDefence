#ifndef __PlayState__
#define __PlayState__

#include "MenuState.h"

#include "../EntitiesHeaders/GameObject.h"
#include "../EntitiesHeaders/SDLGameObject.h"
#include "../EntitiesHeaders/Enemy.h"
#include "../EntitiesHeaders/Button.h"

#include "../MapHeaders/Level.h"

#include "../UIHeaders/PlayStateUIHeaders/PlayStateUI.h"

#include "../UtilsHeaders/TowerFactory.h"
#include "../UtilsHeaders/ProjectileManager.h"
#include "../UtilsHeaders/Vector2D.h"

#include "../WaveHeaders/WaveManager.h"
#include "../WaveHeaders/Wave.h"

#include<vector>
#include<memory>

class PlayState : public MenuState
{
public:
	PlayState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	/**
	* Load data needed for playstate
	*/
	void loadData();

	virtual std::string getStateID() const;

	void addEnemy(std::unique_ptr<Enemy> enemy);
	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

	void handleEvents() override;
private:
	void updateObjects();

	std::shared_ptr<std::vector<std::shared_ptr<Tower>>> m_towersObjects;

	std::shared_ptr<Level> pLevel;

	std::vector<std::shared_ptr<Enemy>> m_enemyObjects;

	std::shared_ptr<WaveManager> m_waveManager;
	Wave* m_currentWave;

	std::shared_ptr<TowerFactory> m_towerFactory;

	std::shared_ptr<ProjectileManager> m_projectileManager;

	std::unique_ptr<PlayStateUI> m_playStateUI;
};

#endif // !__PlayState__
