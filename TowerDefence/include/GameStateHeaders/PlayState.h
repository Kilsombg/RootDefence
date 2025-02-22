#ifndef __PlayState__
#define __PlayState__

#include "GameState.h"

#include "../EntitiesHeaders/GameObject.h"
#include "../EntitiesHeaders/SDLGameObject.h"
#include "../EntitiesHeaders/Enemy.h"

#include "../MapHeaders/Level.h"

#include "../WaveHeaders/WaveManager.h"
#include "../WaveHeaders/Wave.h"

#include<vector>
#include<memory>

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
	void handleEvents();

	std::shared_ptr<Level> pLevel;
	std::vector<std::unique_ptr<Enemy>> m_enemyObjects;

	std::shared_ptr<WaveManager> m_waveManager;
	Wave* m_currentWave;
};

#endif // !__PlayState__
