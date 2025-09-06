#ifndef __MainMenuState__
#define __MainMenuState__

#include "GameState.h"

#include "../UIHeaders/MainMenuUIHeaders/MainMenuStateUI.h"

#include<memory>

/**
* GameState when you are in main menu screen.
* 
* MainMenu handles exiting the game and manages persistent game logic.
*/
class MainMenuState : public GameState
{
public:
	MainMenuState();

	virtual void update() override;
	virtual void render() override;

	virtual bool onEnter() override;
	virtual bool onExit() override;

	virtual void handleEvents() override;

private:
	std::unique_ptr<MainMenuStateUI> m_mainMenuStateUI;
};

#endif // !__MainMenuState__
