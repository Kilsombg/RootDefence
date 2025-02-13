#include "../../include/GameStateHeaders/PlayState.h"
#include "../../include/GameStateHeaders/PauseState.h"
#include "../../include/GameStateHeaders/GameOverState.h"

#include "../../include/EntitiesHeaders/Enemy.h"

#include "../../include/MapHeaders/LevelParser.h"
#include "../../include/MapHeaders/TileLayer.h"

#include "../../include/UtilsHeaders/TextureManager.h"
#include "../../include/UtilsHeaders/InputHandler.h"
#include "../../include/UtilsHeaders/StateParser.h"

#include "../../include/Game.h"

#include<iostream>

PlayState::PlayState()
{
	s_stateID = "PLAY";
}

void PlayState::update()
{
	handleEvents();

	for (std::vector<std::unique_ptr<GameObject>>::size_type  i = 0; i < m_gameObjects.size(); i++)
	{
		if (Enemy* enemy = dynamic_cast<Enemy*>(m_gameObjects[i].get()))
		{
			if (!enemy->isAlive())
			{
				m_gameObjects[i]->clean();
				m_gameObjects.erase(m_gameObjects.begin() + i);
				continue;
			}
		}
		m_gameObjects[i]->update();
	}

	/*
	if (m_gameObjects.size() >= 2)
	{
		if (checkCollision(dynamic_cast<SDLGameObject*> (m_gameObjects[0].get()), dynamic_cast<SDLGameObject*> (m_gameObjects[1].get())))
		{
			TheGame::Instance()->getStateMachine()->pushState(std::make_shared<GameOverState>());
		}
	}*/

	pLevel->update();
}

void PlayState::render()
{
	pLevel->render();
	
	for (std::vector<std::unique_ptr<GameObject>>::size_type  i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}

}

bool PlayState::onEnter()
{
	
	StateParser stateParser;
	stateParser.parseState("./src/test.xml", s_stateID, &m_gameObjects, &m_textureIDList);
	

	LevelParser levelParser;
	pLevel = levelParser.parseLevel("./src/assets/Map/test_map.tmx");

	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		if (Enemy* enemy = dynamic_cast<Enemy*>(m_gameObjects[i].get()))
		{
			enemy->setPath(pLevel->getEnemyPath());
		}
	}

	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit()
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

	std::cout << "exiting PlayState\n";
	return true;
}

std::string PlayState::getStateID() const
{
	return s_stateID;
}

void PlayState::handleEvents()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->pushState(std::make_shared<PauseState>());
	}
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	//Calculate the sides of rect B
	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();

	//If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }

	return true;
}