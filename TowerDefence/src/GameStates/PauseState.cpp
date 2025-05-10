#include "../../include/GameStateHeaders/PauseState.h"
#include "../../include/GameStateHeaders/MainMenuState.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/UtilsHeaders/TextureManager.h"
#include "../../include/UtilsHeaders/InputHandler.h"
#include "../../include/UtilsHeaders/StateParser.h"

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

void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(std::make_shared<MainMenuState>());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::update()
{
	for (std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void PauseState::render()
{
	for (std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PauseState::onEnter()
{
	StateParser stateParser;
	//stateParser.parseState("./src/test.xml", s_stateID, &m_gameObjects, &m_textureIDList);
	
	m_callbacks[LoaderParamsConsts::mainbuttonCallbackID] = s_pauseToMain;
	m_callbacks[LoaderParamsConsts::resumebuttonCallbackID] = s_resumePlay;
	
	setCallbacks(m_callbacks);
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

	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}
	
	// reset the mouse button states to false
	TheInputHandler::Instance()->reset();
	
	std::cout << "exiting PauseState\n";
	return true;
}