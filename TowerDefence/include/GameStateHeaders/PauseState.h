#ifndef __PauseState__
#define __PauseState__

#include "MenuState.h"

#include "../EntitiesHeaders/GameObject.h"

#include "../UIHeaders/PauseStateUIHeaders/PauseStateUI.h"

#include<memory>

class PauseState : public MenuState
{
public:
	PauseState();

	virtual void update() override;
	virtual void render() override;
	
	virtual bool onEnter() override;
	virtual bool onExit() override;

	void handleEvents() override;

	bool drawUnderneath() override;
	
	virtual std::string getStateID() const;

private:
	std::unique_ptr<PauseStateUI> m_pauseStateUI;
};

#endif // !__PauseState__
