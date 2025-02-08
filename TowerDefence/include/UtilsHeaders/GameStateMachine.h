#ifndef __GameStateMachine__
#define __GameStateMachine__

#include "../GameStateHeaders/GameState.h"

#include<vector>
#include<memory>

class GameStateMachine
{
public:
	void pushState(std::shared_ptr<GameState> pState);
	void changeState(std::shared_ptr<GameState> pState);
	void popState();

	void update();
	void render();

private:
	std::vector<std::shared_ptr<GameState>> m_gameStates;
};

#endif // !__GameStateMachine__
