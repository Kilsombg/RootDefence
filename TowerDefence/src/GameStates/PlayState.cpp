#include "../../include/GameStateHeaders/PlayState.h"
#include "../../include/GameStateHeaders/PauseState.h"
#include "../../include/GameStateHeaders/GameOverState.h"

#include "../../include/Constants/SettingsConsts.h"
#include "../../include/Constants/GameObjectConsts.h"
#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/EntitiesHeaders/Enemy.h"
#include "../../include/EntitiesHeaders/Carrot.h"
#include "../../include/EntitiesHeaders/TowerButton.h"

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
	if (!m_waveManager)
	{
		std::cerr << "waveManager is not defined.\n";
	}
	m_waveManager->spawnWaveEnemies(
		pLevel->getEnemyPath(),
		*m_currentWave,
		std::bind(&PlayState::addEnemy, this, std::placeholders::_1),
		(DELAY_TIME / 1000.));

	handleEvents();

	updateObjects();

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

	if (m_clickToPlaceTowerHandler->getShadowObject())
	{
		m_clickToPlaceTowerHandler->render();
	}
}

bool PlayState::onEnter()
{
	loadData();

	m_clickToPlaceTowerHandler = new ClickToPlaceTowerHandler();
	m_towerButtonCallbacks[LoaderParamsConsts::createTowerCallbackID] = std::bind(&ClickToPlaceTowerHandler::handleEvent, m_clickToPlaceTowerHandler, std::placeholders::_1);

	setTowerButtonCallbacks(m_towerButtonCallbacks);

	std::cout << "entering PlayState\n";
	return true;
}

void PlayState::loadData()
{
	// load state objects and textures
	StateParser stateParser;
	stateParser.parseState("./src/test.xml", s_stateID, &m_gameObjects, &m_textureIDList);

	// load level
	LevelParser levelParser;
	pLevel = levelParser.parseLevel("./src/assets/Map/test_map.tmx");
	pLevel->setSpawnPoint(*(pLevel->getEnemyPath()[0].get()));

	// load waves data
	WaveParser waveParser;
	m_waveManager = TheWaveManager::Instance();
	waveParser.parseWaves("./src/res/waves.json", m_waveManager);
	if (!m_waveManager->getWaves().empty()) {
		m_currentWave = m_waveManager->getWaves()[0];
	}

	// load enemies base data
	GameObjectData enemyObjectData;
	enemyObjectData.parseGameOjbectsData("./src/res/enemyObjectData.json", GameObjectConsts::enemyObjectData);
	m_waveManager->setGameObjectData(&enemyObjectData);

	// load tower base data
	GameObjectData towerObjectData;
	m_towerFactory = TheTowerFactory::Instance();
	towerObjectData.parseGameOjbectsData("./src/res/towerObjectData.json", GameObjectConsts::towerObjectData);
	m_towerFactory->setGameObjectData(&towerObjectData);
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

	if (m_currentWave != nullptr)
	{
		delete m_currentWave;
	}

	m_waveManager->clean();
	m_clickToPlaceTowerHandler->clear();

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
	m_clickToPlaceTowerHandler->update(m_gameObjects);

	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		if (TowerButton* towerButton = dynamic_cast<TowerButton*>(m_gameObjects[i].get()))
		{
			towerButton->handleEvent();
		}
	}

	if (TheInputHandler::Instance()->isKeyPressed(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->pushState(std::make_shared<PauseState>());
	}
}

void PlayState::updateObjects()
{
	// udpate enemies
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

	// update towers and buttons
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}

	// update shadow objects
	if (m_clickToPlaceTowerHandler->getShadowObject())
	{
		m_clickToPlaceTowerHandler->getShadowObject()->update();
	}
}

void PlayState::setTowerButtonCallbacks(const std::map<std::string, TowerButtonCallback>& towerButtonCallbacks)
{
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		if (dynamic_cast<TowerButton*>(m_gameObjects[i].get()))
		{
			TowerButton* pButton = dynamic_cast<TowerButton*>(m_gameObjects[i].get());
			pButton->setCallback(towerButtonCallbacks.at(pButton->getCallbackID()));
			pButton = nullptr;
		}
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