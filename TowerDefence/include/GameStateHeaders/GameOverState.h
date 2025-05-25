#ifndef __GameOverState__
#define __GameOverState__

#include "MenuState.h"

#include "../EntitiesHeaders/GameObject.h"

#include "../UIHeaders/GameOverUIHeaders/GameOverStateUI.h"

#include<map>

class GameOverState : public MenuState
{
public:
	GameOverState();

	virtual void update() override;
	virtual void render() override;

	virtual bool onEnter() override;
	virtual bool onExit() override;

	void handleEvents() override;

	bool drawUnderneath() override;

	virtual std::string getStateID() const override;


	// getters and setters

	void setCurrentWaveID(int currentWaveID);

private:
	std::unique_ptr<GameOverStateUI> m_gameOverStateUI;

	int m_currentWaveID;
};

#endif // !__GameOverState__
