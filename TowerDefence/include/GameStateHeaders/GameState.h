#ifndef __GameState__
#define __GameState__

#include "../EntitiesHeaders/GameObject.h"

#include<string>
#include<vector>
#include<memory>

/**
* Base class for game state.
*
* Represent a state of a game that GameStateMachine manages.
*
* When game state appears it is called onEnter() method to initiate the state.
* When game state is popped, then onExit() is called to clean state's memory.
*
* drawUnderneath() is false by default. Override if you need the gameState to be drawn
* on top of another state.
*/
class BaseGameState
{
public:
	virtual void handleEvents() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual std::string getStateID() const = 0;

	/**
	* Show if there is state underneath that should be drawn.
	*
	* @return true if there is a state to be drawn underneath.
	*/
	virtual bool drawUnderneath() { return false; };

protected:
	std::string s_stateID;

	std::vector<std::unique_ptr<GameObject>> m_gameObjects;
	std::vector<std::string> m_textureIDList;
};


/**
* Definition for base methods.
*
* When game state appears it is called onEnter() method to initiate the state.
* When game state is popped, then onExit() is called to clean state's memory.
*/
class GameState : public BaseGameState
{
public:
	virtual void update() override;
	virtual void render() override;

	virtual bool onExit() override;

	virtual std::string getStateID() const override;
};

#endif // !__GameState__
