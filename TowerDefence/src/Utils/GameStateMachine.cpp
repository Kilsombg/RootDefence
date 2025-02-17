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
	for (auto it = m_gameStates.begin(); it != m_gameStates.end(); ++it)
	{
		if (((*it)->getStateID() == pState->getStateID()) && ((*it)->onExit()))
		{
			m_gameStates.erase(it);
			break;
		}
	}

	m_gameStates.push_back(pState);

	if (!m_gameStates.back()->onEnter())
	{
		std::cout << "Fail to push_back State\n";
	}
}

void GameStateMachine::popStatePrivate()
{
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

		if (m_gameStates.back()->onExit())
		{
			m_gameStates.pop_back();
		}

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

	m_gameStates.push_back(pState);

	m_gameStates.back()->onEnter();
}

void GameStateMachine::changeState(std::shared_ptr<GameState> pState)
{
	std::cout << "change state flag activated\n";
	m_bChangeStateFlag = true;
	newState = pState;
}


void GameStateMachine::update()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->update();
	}

	if (m_bChangeStateFlag)
	{
		std::cout << "Going to change state\n";
		changeStatePrivate(newState);
		m_bChangeStateFlag = false;
	}
	else if (m_bPopStateFlag)
	{
		std::cout << "Going to pop state\n";
		popStatePrivate();
		m_bPopStateFlag = false;
	}
}

void GameStateMachine::render()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->render();
	}
}

void GameStateMachine::clean()
{
	while (!m_gameStates.empty())
	{
		if (m_gameStates.back()->onExit())
		{
			m_gameStates.pop_back();
		}
	}
}