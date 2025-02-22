#include "../../include/GameStateHeaders/PlayState.h"
#include "../../include/GameStateHeaders/PauseState.h"
#include "../../include/GameStateHeaders/GameOverState.h"

#include "../../include/Constants/SettingsConsts.h"

#include "../../include/EntitiesHeaders/Enemy.h"
#include "../../include/EntitiesHeaders/Carrot.h"

#include "../../include/MapHeaders/LevelParser.h"
#include "../../include/MapHeaders/TileLayer.h"

#include "../../include/UtilsHeaders/TextureManager.h"
#include "../../include/UtilsHeaders/InputHandler.h"
#include "../../include/UtilsHeaders/StateParser.h"
#include "../../include/UtilsHeaders/GameObjectData.h"

#include "../../include/WaveHeaders/WaveParser.h"

#include "../../include/Game.h"

#include<iostream>

PlayState::PlayState()
{
	s_stateID = "PLAY";
}

void PlayState::update()
{
	handleEvents();

	if (!m_waveManager)
	{
		std::cerr << "waveManager is not defined.\n";
	}
	m_waveManager->spawnWaveEnemies(
		pLevel->getEnemyPath(),
		*m_currentWave,
		std::bind(&PlayState::addEnemy, this, std::placeholders::_1),
		(DELAY_TIME/1000.));

	for (std::vector<std::unique_ptr<Enemy>>::size_type i = 0; i < m_enemyObjects.size(); i++)
	{
			if (!m_enemyObjects[i]->isAlive())
			{
				m_enemyObjects[i]->clean();
				m_enemyObjects.erase(m_enemyObjects.begin() + i);
				continue;
			}
		
			m_enemyObjects[i]->update();
	}

	pLevel->update();
}

void PlayState::render()
{
	pLevel->render();

	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}

	for (std::vector<std::unique_ptr<Enemy>>::size_type i = 0; i < m_enemyObjects.size(); i++)
	{
		m_enemyObjects[i]->draw();
	}
}

bool PlayState::onEnter()
{
	loadData();

	std::cout << "entering PlayState\n";
	return true;
}

void PlayState::loadData()
{
	StateParser stateParser;
	stateParser.parseState("./src/test.xml", s_stateID, &m_gameObjects, &m_textureIDList);

	LevelParser levelParser;
	pLevel = levelParser.parseLevel("./src/assets/Map/test_map.tmx");
	pLevel->setSpawnPoint(*(pLevel->getEnemyPath()[0].get()));

	WaveParser waveParser;
	m_waveManager = TheWaveManager::Instance();
	waveParser.parseWaves("./src/res/waves.json", m_waveManager);
	if (!m_waveManager->getWaves().empty()) {
		m_currentWave = &(m_waveManager->getWaves()[0]);
	}

	GameObjectData gameObjectData;
	gameObjectData.parseGameOjbectsData("./src/res/gameObjectsData.json");
	m_waveManager->setGameObjectData(&gameObjectData);
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

void PlayState::addEnemy(std::unique_ptr<Enemy> enemy)
{
	m_enemyObjects.push_back(std::move(enemy));
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