#include "../../include/GameStateHeaders/MainMenuState.h"

#include "../../include/EntitiesHeaders/GameObject.h"

#include "../../include/UtilsHeaders/TextureManager.h"

#include "../../include/Game.h"

#include<iostream>
#include<vector>

MainMenuState::MainMenuState()
{
	s_stateID = "MENU";
}

void MainMenuState::update()
{
	GameState::update();

	// update UI
	m_mainMenuStateUI->update();
}

void MainMenuState::render()
{
	GameState::render();

	// draw UI
	m_mainMenuStateUI->draw();
}

bool MainMenuState::onEnter()
{
	// load UI
	m_mainMenuStateUI = std::make_unique<MainMenuStateUI>(s_stateID);
	m_mainMenuStateUI->load();
	
	std::cout << "entering MenuState\n";
	return true;
}

bool MainMenuState::onExit()
{
	GameState::onExit();

	// clean UI
	m_mainMenuStateUI->clean();

	std::cout << "exiting MenuState\n";
	return true;
}

void MainMenuState::handleEvents()
{
	// handle UI
	m_mainMenuStateUI->handleEvents();
}