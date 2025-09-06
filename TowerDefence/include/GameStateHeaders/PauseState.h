#ifndef __PauseState__
#define __PauseState__

#include "GameState.h"

#include "../UIHeaders/PauseStateUIHeaders/PauseStateUI.h"

#include<memory>

/**
* GameState when pausing from PlayState.
*/
class PauseState : public GameState
{
public:
	PauseState();

	virtual void update() override;
	virtual void render() override;
	
	virtual bool onEnter() override;
	virtual bool onExit() override;

	void handleEvents() override;

	bool drawUnderneath() override;

private:
	std::unique_ptr<PauseStateUI> m_pauseStateUI;
};

#endif // !__PauseState__
