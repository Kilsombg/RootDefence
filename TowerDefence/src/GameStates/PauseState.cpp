#include "../../include/GameStateHeaders/PauseState.h"

#include "../../include/EntitiesHeaders/GameObject.h"

#include "../../include/UtilsHeaders/TextureManager.h"
#include "../../include/UtilsHeaders/InputHandler.h"

#include "../../include/Game.h"

#include<iostream>	
#include<vector>
#include<memory>

PauseState::PauseState()
{
	s_stateID = "PAUSE";
}

std::string PauseState::getStateID() const
{
	return s_stateID;
}

void PauseState::update()
{
	for (std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}

	// update UI
	m_pauseStateUI->update();
}

void PauseState::render()
{
	for (std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}

	// dimming underneath
	TheTextureManager::Instance()->dimBackground(TheGame::Instance()->getWindow(), TheGame::Instance()->getRenderer());

	// draw UI
	m_pauseStateUI->draw();
}

bool PauseState::onEnter()
{
	// load UI
	m_pauseStateUI = std::make_unique<PauseStateUI>(s_stateID);
	m_pauseStateUI->load();

	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
		m_gameObjects[i] = nullptr;
	}
	m_gameObjects.clear();

	// clean textures
	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}
	
	// reset the mouse button states to false
	TheInputHandler::Instance()->reset();

	// clean UI
	m_pauseStateUI->clean();
	
	std::cout << "exiting PauseState\n";
	return true;
}

void PauseState::handleEvents()
{
	// handle UI
	m_pauseStateUI->handleEvents();
}

bool PauseState::drawUnderneath()
{
	return true;
}
