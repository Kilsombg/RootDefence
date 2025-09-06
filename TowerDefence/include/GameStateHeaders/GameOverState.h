#ifndef __GameOverState__
#define __GameOverState__

#include "GameState.h"

#include "../UIHeaders/GameOverUIHeaders/GameOverStateUI.h"

#include<map>

/**
* Game state that occurs on game defeat.
* 
* When game health point goes to 0, then GameOverState occurs.
*/
class GameOverState : public GameState
{
public:
	GameOverState();

	virtual void update() override;
	virtual void render() override;

	virtual bool onEnter() override;
	virtual bool onExit() override;

	void handleEvents() override;

	bool drawUnderneath() override;


	// getters and setters

	void setCurrentWaveID(int currentWaveID);

private:
	std::unique_ptr<GameOverStateUI> m_gameOverStateUI;

	int m_currentWaveID;
};

#endif // !__GameOverState__
