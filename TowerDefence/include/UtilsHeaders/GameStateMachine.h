#ifndef __GameStateMachine__
#define __GameStateMachine__

#include "../GameStateHeaders/GameState.h"

#include<vector>
#include<memory>

/**
* GameStateMachine manages states.
* 
* It stores states in stack and manages changing to another state or 
* poping the current state.
*/
class GameStateMachine
{
public:
	static std::shared_ptr<GameStateMachine> Instance();
	std::string getCurrentState();
	/**
	* Push state and remove from stack if other instances exists.
	* 
	* @param pState - pushed state.
	*/
	void pushState(std::shared_ptr<GameState> pState);
	/**
	* Mark there is a change to be done.
	*/
	void changeState(std::shared_ptr<GameState> pState);
	/**
	* Mark that current state needs to be removed.
	*/
	void popState();
	/**
	* Handle current state if present.
	*/
	void handleEvents();
	/**
	* Update current state and stack if flag is set to true.
	*/
	void update();
	/**
	* Render all states that needs to be drawn.
	* 
	* Checks if current state needs to be rendered above previous state,
	* if it does, then check previous state untill it get's to the last one
	* or not set state::underneath() to true.
	*
	* When find the bottom state to be rendered it renders from it to the current one.
	*/
	void render();
	/**
	* Clears state stacks.
	* 
	* Before clearing a state it calls onExit().
	*/
	void clean();

private:
	GameStateMachine();
	static std::shared_ptr<GameStateMachine> s_pInstance;

	std::vector<std::shared_ptr<GameState>> m_gameStates;
	std::shared_ptr<GameState> newState;
	bool m_bPopStateFlag;
	bool m_bChangeStateFlag;

	/**
	* Pop current state and calls onExit().
	*/
	void popStatePrivate();
	/**
	* Change state with pState .
	* 
	* If other instance of that state presents in state stack
	* it removes them and calls onExit().
	*/
	void changeStatePrivate(std::shared_ptr<GameState> pState);
};

typedef GameStateMachine TheGameStateMachine;

#endif // !__GameStateMachine__
