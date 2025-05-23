#include "../../include/GameStateHeaders/MainMenuState.h"
#include "../../include/GameStateHeaders/PlayState.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/EntitiesHeaders/MenuButton.h"

#include "../../include/UtilsHeaders/TextureManager.h"
#include "../../include/UtilsHeaders/StateParser.h"

#include "../../include/Game.h"

#include<iostream>
#include<memory>
#include<vector>

MainMenuState::MainMenuState()
{
	s_stateID = "MENU";
}

void MainMenuState::update()
{
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}

	// update UI
	m_mainMenuStateUI->update();
}

void MainMenuState::render()
{
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}

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
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();

	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}

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


std::string MainMenuState::getStateID() const
{
	return s_stateID;
}