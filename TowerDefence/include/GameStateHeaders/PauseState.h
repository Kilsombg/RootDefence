#ifndef __PauseState__
#define __PauseState__

#include "MenuState.h"

#include "../EntitiesHeaders/GameObject.h"

#include<vector>

class PauseState : public MenuState
{
public:
	PauseState();

	virtual void update();
	virtual void render();
	
	virtual bool onEnter();
	virtual bool onExit();
	
	virtual std::string getStateID() const;
	virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
	static void s_pauseToMain();
	static void s_resumePlay();
};

#endif // !__PauseState__
