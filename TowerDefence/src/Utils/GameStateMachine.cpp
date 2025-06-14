#include "../../include/UtilsHeaders/GameStateMachine.h"

std::shared_ptr<GameStateMachine> GameStateMachine::s_pInstance = nullptr;

GameStateMachine::GameStateMachine() : m_bPopStateFlag(false), m_bChangeStateFlag(false)
{
}

std::shared_ptr<GameStateMachine> GameStateMachine::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = std::shared_ptr<GameStateMachine>(new GameStateMachine);
		return s_pInstance;
	}
	return s_pInstance;
}

std::string GameStateMachine::getCurrentState()
{
	return m_gameStates.back()->getStateID();
}

void GameStateMachine::pushState(std::shared_ptr<GameState> pState)
{
	// remove same state in the state stack if present
	for (auto it = m_gameStates.begin(); it != m_gameStates.end(); ++it)
	{
		if (((*it)->getStateID() == pState->getStateID()) && ((*it)->onExit()))
		{
			m_gameStates.erase(it);
			break;
		}
	}

	// push given state in the stack
	m_gameStates.push_back(pState);

	if (!m_gameStates.back()->onEnter())
	{
		std::cout << "Fail to push_back State\n";
	}
}

void GameStateMachine::popStatePrivate()
{
	// removes current state from state stack
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->onExit())
		{
			m_gameStates.pop_back();
		}
	}
}

void GameStateMachine::popState()
{
	m_bPopStateFlag = true;
}

void GameStateMachine::changeStatePrivate(std::shared_ptr<GameState> pState)
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->getStateID() == pState->getStateID())
		{
			return;
		}

		// remove current state
		if (m_gameStates.back()->onExit())
		{
			m_gameStates.pop_back();
		}

		// remove same state in the state stack if present
		for (auto it = m_gameStates.begin(); it != m_gameStates.end(); ++it)
		{
			if (((*it)->getStateID() == pState->getStateID()) && ((*it)->onExit()))
			{
				std::cout << "Detected unneeded state: " << pState->getStateID() << "\n";
				m_gameStates.erase(it);
				break;
			}
		}
	}

	// push state on top of state stack
	m_gameStates.push_back(pState);

	m_gameStates.back()->onEnter();
}

void GameStateMachine::changeState(std::shared_ptr<GameState> pState)
{
	std::cout << "change state flag activated\n";
	m_bChangeStateFlag = true;
	newState = pState;
}


void GameStateMachine::handleEvents()
{
	// handle current state
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->handleEvents();
	}
}

void GameStateMachine::update()
{
	// update current state
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->update();
	}

	if (m_bChangeStateFlag)
	{
		// change state if needed
		std::cout << "Going to change state\n";
		changeStatePrivate(newState);
		m_bChangeStateFlag = false;
	}
	else if (m_bPopStateFlag)
	{
		// pop state if needed
		std::cout << "Going to pop state\n";
		popStatePrivate();
		m_bPopStateFlag = false;
	}
}

void GameStateMachine::render()
{
	// Start from the last state and go backwards
	int startIndex = m_gameStates.size() - 1;

	// Find the first state that should be rendered
	while (startIndex > 0 && m_gameStates[startIndex]->drawUnderneath()) {
		--startIndex;
	}

	// Render from that state up to the top of the stack
	for (int i = startIndex; i < m_gameStates.size(); ++i) {
		m_gameStates[i]->render();
	}
}

void GameStateMachine::clean()
{
	// clean each state from state stack
	while (!m_gameStates.empty())
	{
		if (m_gameStates.back()->onExit())
		{
			m_gameStates.pop_back();
		}
	}
}