#ifndef __GameState__
#define __GameState__

#include "../EntitiesHeaders/GameObject.h"

#include<string>
#include<vector>
#include<memory>

class GameState
{
public:
	virtual void update() = 0;
	virtual void render() = 0;
	
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	
	virtual std::string getStateID() const = 0;

protected:
	std::string s_stateID;

	std::vector<std::unique_ptr<GameObject>> m_gameObjects;
	std::vector<std::string> m_textureIDList;
};

#endif // !__GameState__
