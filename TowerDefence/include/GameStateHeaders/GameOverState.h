#ifndef __GameOverState__
#define __GameOverState__

#include "GameState.h"

#include "../EntitiesHeaders/GameObject.h"

#include<vector>

class GameOverState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const;

private:
	static void s_gameOverToMain();
	static void s_restartPlay();
	
	static const std::string s_gameOverID;
	
	std::vector<GameObject*> m_gameObjects;
};

#endif // !__GameOverState__
