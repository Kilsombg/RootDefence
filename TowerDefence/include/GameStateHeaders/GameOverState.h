#ifndef __GameOverState__
#define __GameOverState__

#include "MenuState.h"

#include "../EntitiesHeaders/GameObject.h"

#include<vector>

class GameOverState : public MenuState
{
public:
	GameOverState();

	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const;

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
	static void s_gameOverToMain();
	static void s_restartPlay();
};

#endif // !__GameOverState__
