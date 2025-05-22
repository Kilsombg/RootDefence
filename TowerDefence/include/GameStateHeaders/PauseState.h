#ifndef __PauseState__
#define __PauseState__

#include "MenuState.h"

#include "../EntitiesHeaders/GameObject.h"

class PauseState : public MenuState
{
public:
	PauseState();

	virtual void update() override;
	virtual void render() override;
	
	virtual bool onEnter() override;
	virtual bool onExit() override;

	bool drawUnderneath() override;
	
	virtual std::string getStateID() const;

private:
	static void s_pauseToMain();
	static void s_resumePlay();
};

#endif // !__PauseState__
