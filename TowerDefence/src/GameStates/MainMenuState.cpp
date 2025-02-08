#include "../../include/GameStateHeaders/MainMenuState.h"
#include "../../include/GameStateHeaders/PlayState.h"

#include "../../include/EntitiesHeaders/MenuButton.h"

#include "../../include/UtilsHeaders/TextureManager.h"
#include "../../include/UtilsHeaders/StateParser.h"

#include "../../include/Game.h"

#include<iostream>

MainMenuState::MainMenuState()
{
	s_stateID = "MENU";
}

void MainMenuState::update()
{
	for (std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}
void MainMenuState::render()
{
	for (std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool MainMenuState::onEnter()
{	
	StateParser stateParser;
	stateParser.parseState("./src/test.xml", s_stateID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);

	setCallbacks(m_callbacks);
	std::cout << "entering MenuState\n";
	return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
	for (std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		if (dynamic_cast<MenuButton*>(m_gameObjects[i].get()))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i].get());
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
			pButton = nullptr;
		}
	}
}

bool MainMenuState::onExit()
{
	for (std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
		m_gameObjects[i] = nullptr;
	}

	m_gameObjects.clear();

	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}

	std::cout << "exiting MenuState\n";
	return true;
}

std::string MainMenuState::getStateID() const
{
	return s_stateID;
}

void MainMenuState::s_menuToPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
	TheGame::Instance()->quit();
}