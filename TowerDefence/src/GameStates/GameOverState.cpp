#include "../../include/GameStateHeaders/GameOverState.h"
#include "../../include/GameStateHeaders/MainMenuState.h"
#include "../../include/GameStateHeaders/PlayState.h"

#include "../../include/EntitiesHeaders/AnimatedGraphic.h"
#include "../../include/EntitiesHeaders/MenuButton.h"

#include "../../include/UtilsHeaders/StateParser.h"

#include "../../include/Game.h"

#include<iostream>
#include<memory>

GameOverState::GameOverState()
{
	s_stateID = "GAMEOVER";
}

void GameOverState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}
void GameOverState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

std::string GameOverState::getStateID() const
{
	return s_stateID;
}

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(std::make_shared<MainMenuState>());
}

void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(std::make_shared<PlayState>());
}

bool GameOverState::onEnter()
{
	StateParser stateParser;
	stateParser.parseState("./src/test.xml", s_stateID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_gameOverToMain);
	m_callbacks.push_back(s_restartPlay);
	
	setCallbacks(m_callbacks);
	std::cout << "entering GameOverState\n";
	return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (dynamic_cast<MenuButton*>(m_gameObjects[i].get()))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i].get());
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
			pButton = nullptr;
		}
	}
}

bool GameOverState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
		m_gameObjects[i] = nullptr;
	}

	m_gameObjects.clear();
	
	for (std::vector<std::string>::size_type i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}

	std::cout << "exiting GameOverState\n";
	return true;
}