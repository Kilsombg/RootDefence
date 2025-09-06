#include "../../include/GameStateHeaders/GameOverState.h"

#include "../../include/UtilsHeaders/TextureManager.h"

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
	GameState::update();

	// update UI
	m_gameOverStateUI->update();
}

void GameOverState::render()
{
	GameState::render();

	// dimming underneath
	TheTextureManager::Instance()->dimBackground(TheGame::Instance()->getWindow(), TheGame::Instance()->getRenderer());

	// draw UI
	m_gameOverStateUI->draw();
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
	GameState::onExit();

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
