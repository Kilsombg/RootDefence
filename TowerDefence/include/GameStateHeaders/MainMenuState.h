#ifndef __MainMenuState__
#define __MainMenuState__

#include"MenuState.h"

#include "../EntitiesHeaders/GameObject.h"

class MainMenuState : public MenuState
{
public:
	MainMenuState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const;

private:

	// call back functions for menu items
	static void s_menuToPlay();
	static void s_exitFromMenu();
};

#endif // !__MainMenuState__
