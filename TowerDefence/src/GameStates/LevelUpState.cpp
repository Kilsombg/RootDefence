#include "../../include/GameStateHeaders/LevelUpState.h"

#include "../../include/EntitiesHeaders/GameObject.h"

#include "../../include/UtilsHeaders/TextureManager.h"

#include "../../include/Game.h"

#include "../../include/UtilsHeaders/TextureManager.h"

#include<iostream>

LevelUpState::LevelUpState()
{
	s_stateID = "LEVELUP";
}

void LevelUpState::update()
{
	GameState::update();

	// update UI
	m_levelUpStateUI->update();
}

void LevelUpState::render()
{
	GameState::render();

	// dim background
	TheTextureManager::Instance()->dimBackground(TheGame::Instance()->getWindow(), TheGame::Instance()->getRenderer());

	// draw UI
	m_levelUpStateUI->draw();
}

bool LevelUpState::onEnter()
{
	// load UI
	m_levelUpStateUI = std::make_unique<LevelUpStateUI>(s_stateID);
	m_levelUpStateUI->setTowerUnlockID(m_towerUnlockedID);
	m_levelUpStateUI->load();

	std::cout << "entering LevelUpState\n";
	return true;
}

bool LevelUpState::onExit()
{
	GameState::onExit();

	// clean UI
	m_levelUpStateUI->clean();

	std::cout << "exiting LevelUpState\n";
	return true;
}

void LevelUpState::handleEvents()
{
	// handle UI
	m_levelUpStateUI->handleEvents();
}

bool LevelUpState::drawUnderneath()
{
	return true;
}

void LevelUpState::setTowerUnlockedID(std::string name)
{
	m_towerUnlockedID = name;
}
