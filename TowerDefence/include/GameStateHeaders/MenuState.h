#ifndef __MenuState__
#define __MenuState__

#include "GameState.h"

#include<string>
#include<map>

class MenuState : public GameState
{
protected:
	typedef void(*Callback)();
	
	virtual void setCallbacks(const std::map<std::string, Callback>& callbacks);

	virtual void handleEvents() override;

	bool drawUnderneath() override;
	
	std::map<std::string, Callback> m_callbacks;
};

#endif // !__MenuState__