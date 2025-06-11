#ifndef __MainMenuState__
#define __MainMenuState__

#include "GameState.h"

#include "../EntitiesHeaders/GameObject.h"

#include "../UIHeaders/MainMenuUIHeaders/MainMenuStateUI.h"

#include<memory>

class MainMenuState : public GameState
{
public:
	MainMenuState();

	virtual void update() override;
	virtual void render() override;

	virtual bool onEnter() override;
	virtual bool onExit() override;

	virtual void handleEvents() override;

	virtual std::string getStateID() const;

private:
	std::unique_ptr<MainMenuStateUI> m_mainMenuStateUI;
};

#endif // !__MainMenuState__
