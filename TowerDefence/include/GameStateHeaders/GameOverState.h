#ifndef __GameOverState__
#define __GameOverState__

#include "MenuState.h"

#include "../EntitiesHeaders/GameObject.h"

#include<map>

class GameOverState : public MenuState
{
public:
	GameOverState();

	virtual void update() override;
	virtual void render() override;

	virtual bool onEnter() override;
	virtual bool onExit() override;

	bool drawUnderneath() override;

	virtual std::string getStateID() const;

private:
	static void s_gameOverToMain();
	static void s_restartPlay();
};

#endif // !__GameOverState__
