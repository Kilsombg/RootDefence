#include "../../include/GameStateHeaders/GameOverState.h"
#include "../../include/GameStateHeaders/MainMenuState.h"
#include "../../include/GameStateHeaders/PlayState.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/EntitiesHeaders/AnimatedGraphic.h"
#include "../../include/EntitiesHeaders/MenuButton.h"

#include "../../include/UtilsHeaders/StateParser.h"

#include "../../include/Game.h"

#include<iostream>
#include<vector>
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

	// update UI
	m_gameOverStateUI->update();
}

void GameOverState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}

	// dimming underneath
	TheTextureManager::Instance()->dimBackground(TheGame::Instance()->getWindow(), TheGame::Instance()->getRenderer());

	// draw UI
	m_gameOverStateUI->draw();
}

std::string GameOverState::getStateID() const
{
	return s_stateID;
}

void GameOverState::setCurrentWaveID(int currentWaveID)
{
	m_currentWaveID = currentWaveID;
}

bool GameOverState::onEnter()
{
	// load UI
	m_gameOverStateUI = std::make_unique<GameOverStateUI>(s_stateID);
	m_gameOverStateUI->setCurrentWaveID(m_currentWaveID);
	m_gameOverStateUI->load();

	std::cout << "entering GameOverState\n";
	return true;
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

	// clean UI
	m_gameOverStateUI->clean();

	std::cout << "exiting GameOverState\n";
	return true;
}

void GameOverState::handleEvents()
{
	// handle UI
	m_gameOverStateUI->handleEvents();
}

bool GameOverState::drawUnderneath()
{
	return true;
}
