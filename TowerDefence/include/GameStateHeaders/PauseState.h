#ifndef __PauseState__
#define __PauseState__

#include "MenuState.h"

#include "../EntitiesHeaders/GameObject.h"

#include<vector>

class PauseState : public MenuState
{
public:
	virtual void update();
	virtual void render();
	
	virtual bool onEnter();
	virtual bool onExit();
	
	virtual std::string getStateID() const;
	virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
	static void s_pauseToMain();
	static void s_resumePlay();
	
	static const std::string s_pauseID;
	
	std::vector<GameObject*> m_gameObjects;
};

#endif // !__PauseState__
