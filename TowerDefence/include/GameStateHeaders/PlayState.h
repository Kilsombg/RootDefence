#ifndef __PlayState__
#define __PlayState__

#include "GameState.h"

#include "../EntitiesHeaders/GameObject.h"
#include "../EntitiesHeaders/SDLGameObject.h"

#include<vector>

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const;

	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

private:
	static const std::string s_playID;

	std::vector<GameObject*> m_gameObjects;
};

#endif // !__PlayState__
