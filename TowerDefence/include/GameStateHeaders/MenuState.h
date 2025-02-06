#ifndef __MenuState__
#define __MenuState__

#include "GameState.h"

#include<vector>

class MenuState : public GameState
{
protected:
	typedef void(*Callback)();
	
	virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;
	
	std::vector<Callback> m_callbacks;

	std::vector<std::string> m_textureIDList;
};

#endif // !__MenuState__
