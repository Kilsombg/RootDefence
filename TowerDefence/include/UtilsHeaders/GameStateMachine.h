#ifndef __GameStateMachine__
#define __GameStateMachine__

#include "../GameStateHeaders/GameState.h"

#include<vector>
#include<memory>

class GameStateMachine
{
public:
	static std::shared_ptr<GameStateMachine> Instance();
	std::string getCurrentState();

	void pushState(std::shared_ptr<GameState> pState);
	void changeState(std::shared_ptr<GameState> pState);
	void popState();

	void update();
	void render();
	void clean();

private:
	GameStateMachine();
	static std::shared_ptr<GameStateMachine> s_pInstance;

	std::vector<std::shared_ptr<GameState>> m_gameStates;
	std::shared_ptr<GameState> newState;
	bool m_bPopStateFlag;
	bool m_bChangeStateFlag;

	void popStatePrivate();
	void changeStatePrivate(std::shared_ptr<GameState> pState);
};

typedef GameStateMachine TheGameStateMachine;

#endif // !__GameStateMachine__
