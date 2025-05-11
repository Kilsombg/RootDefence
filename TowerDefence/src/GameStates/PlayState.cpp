#include "../../include/GameStateHeaders/PlayState.h"
#include "../../include/GameStateHeaders/PauseState.h"
#include "../../include/GameStateHeaders/GameOverState.h"

#include "../../include/Constants/SettingsConsts.h"
#include "../../include/Constants/GameObjectConsts.h"
#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/EntitiesHeaders/Enemy.h"
#include "../../include/EntitiesHeaders/TowerButton.h"

#include "../../include/MapHeaders/LevelParser.h"
#include "../../include/MapHeaders/TileLayer.h"

#include "../../include/UIHeaders/PlayStateUIHeaders/TowerUpgradePanel.h"
#include "../../include/UIHeaders/PlayStateUIHeaders/TowersPanel.h"

#include "../../include/UtilsHeaders/InputHandler.h"
#include "../../include/UtilsHeaders/GameObjectData.h"
#include "../../include/UtilsHeaders/ProjectileManager.h"

#include "../../include/WaveHeaders/WaveParser.h"

#include "../../include/Game.h"

#include<iostream>
#include<functional>

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

	updateObjects();

	pLevel->update();
}

void PlayState::render()
{
	// render map
	pLevel->render();

	// render enemies
	for (std::vector<std::shared_ptr<Enemy>>::size_type i = 0; i < m_enemyObjects.size(); i++)
	{
		m_enemyObjects[i]->draw();
	}

	// render towers
	for (std::vector<std::shared_ptr<Tower>>::size_type i = 0; i < m_towersObjects->size(); i++)
	{
		(*m_towersObjects)[i]->draw();
	}

	// render projectiles
	TheProjectileManager::Instance()->render();

	// render UI
	m_playStateUI->draw();
}

bool PlayState::onEnter()
{
	m_towersObjects = std::make_shared<std::vector<std::shared_ptr<Tower>>>();

	loadData();

	std::cout << "entering PlayState\n";
	return true;
}

void PlayState::loadData()
{
	// load level
	LevelParser levelParser;
	pLevel = levelParser.parseLevel("./src/assets/Map/test_map.tmx");
	//pLevel = levelParser.parseLevel("./src/assets/map1.tmx");
	if (!pLevel->getEnemyPath().empty())
	{
		pLevel->setSpawnPoint(*(pLevel->getEnemyPath()[0].get()));
	}


	// load waves data
	WaveParser waveParser;
	m_waveManager = TheWaveManager::Instance();
	waveParser.parseWaves("./src/res/waves.json", m_waveManager);
	if (!m_waveManager->getWaves().empty()) {
		m_currentWave = m_waveManager->getWaves()[0];
	}

	// load enemies base data
	GameObjectData<LoaderParams> enemyObjectData;
	enemyObjectData.parseGameOjbectsData("./src/res/enemyObjectData.json", GameObjectConsts::enemyObjectData);
	m_waveManager->setGameObjectData(enemyObjectData);

	// load tower data
	loadTowerData();

	// load gameSession data
	loadGameSessionData();

	// loading purchase manager
	m_purchaseManager = ThePurchaseManager::Instance();
	m_purchaseManager->setGameSessionData(m_gameSessionData);

	// load sell manager
	m_sellManager = TheSellManager::Instance();
	m_sellManager->setGameSessionData(m_gameSessionData);

	/* load UI */
	m_playStateUI = std::make_unique<PlayStateUI>(s_stateID);
	m_playStateUI->setPlayStateTowers(m_towersObjects);
	m_playStateUI->setLevel(pLevel);
	m_playStateUI->setGameSessionData(m_gameSessionData);
	m_playStateUI->load();
}

bool PlayState::onExit()
{
	// cleaning towers
	for (std::vector<std::shared_ptr<Tower>>::size_type i = 0; i < m_towersObjects->size(); i++)
	{
		(*m_towersObjects)[i]->clean();
		(*m_towersObjects)[i] = nullptr;
	}

	m_towersObjects->clear();

	// clean level
	pLevel->clean();

	// cleaning projectiles
	m_projectileManager->clean();

	// cleaning UI
	m_playStateUI->clean();

	// cleaning current waves
	if (m_currentWave != nullptr)
	{
		delete m_currentWave;
	}
	m_waveManager->clean();

	// clean purchase manager
	m_purchaseManager->clean();

	// clean sell manager
	m_sellManager->clean();

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
	// handle game over
	if (m_gameSessionData->gameHealth <= 0)
	{
		TheGame::Instance()->getStateMachine()->pushState(std::make_shared<GameOverState>());
	}

	// handle buttons
	MenuState::handleEvents();

	// handle UI
	m_playStateUI->handleEvents();

	// handle towers
	for (std::vector<std::shared_ptr<Tower>>::size_type i = 0; i < m_towersObjects->size(); i++)
	{
		(*m_towersObjects)[i]->handleEvent();
	}

	// handle input
	if (TheInputHandler::Instance()->isKeyPressed(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->pushState(std::make_shared<PauseState>());
	}
}

void PlayState::updateObjects()
{
	// udpate enemies
	updateEnemyObjects();

	// update towers
	for (std::vector<std::shared_ptr<Tower>>::size_type i = 0; i < m_towersObjects->size(); i++)
	{
		(*m_towersObjects)[i]->update();

		(*m_towersObjects)[i]->targetEnemy(m_enemyObjects);
	}

	// update UI
	m_playStateUI->update();

	// update projectiles
	TheProjectileManager::Instance()->update();
}

void PlayState::updateEnemyObjects()
{
	for (std::vector<std::shared_ptr<Enemy>>::size_type i = 0; i < m_enemyObjects.size(); i++)
	{
		// remove defeated enemies or enemy crossed to the end of path
		if (!m_enemyObjects[i]->isAlive() || m_enemyObjects[i]->isCrossEndOfPath())
		{
			// remove health point if enemy crosses to the end of path
			if (m_enemyObjects[i]->isCrossEndOfPath())
			{
				m_gameSessionData->gameHealth--;
			}
			else // defeated enemy
			{
				// increase gameSession resources
				Resource drop = m_enemyObjects[i]->getDrop();
				m_gameSessionData->resources[drop.type].value += drop.value;
			}

			// remove enemy
			m_enemyObjects[i]->clean();
			m_enemyObjects.erase(m_enemyObjects.begin() + i);
			continue;
		}

		// update enemy
		m_enemyObjects[i]->update();
	}
}

void PlayState::loadGameSessionData()
{
	m_gameSessionData = std::make_shared<GameSessionData>();

	m_gameSessionData->gameHealth= 5;
	m_gameSessionData->resources = { Resource {ResourceType {GREEN}, 5},
					Resource {ResourceType {YELLOW}, 0},
					Resource {ResourceType {RED}, 0} };
	m_gameSessionData->currentWaveLevel = 0;
}

void PlayState::loadTowerData()
{
	// load tower base data
	GameObjectData<LoaderParams> towerObjectData;
	m_towerFactory = TheTowerFactory::Instance();
	towerObjectData.parseGameOjbectsData("./src/res/towerObjectData.json", GameObjectConsts::towerObjectData);
	m_towerFactory->setTowerObjectData(towerObjectData);

	// load tower upgrade data
	GameObjectData<ArrayOf2TowerUpgradesData> towerUpgradeData;
	towerUpgradeData.parseGameOjbectsData("./src/res/towerUpgradesData.json", GameObjectConsts::towerUpgradesData);
	m_towerFactory->setTowerUpgradeObjectData(towerUpgradeData);

	// load tower projectiles data
	GameObjectData<LoaderParams> projectilesData;
	m_projectileManager = TheProjectileManager::Instance();
	projectilesData.parseGameOjbectsData("./src/res/projectilesData.json", GameObjectConsts::projectilesData);
	m_projectileManager->setGameObjectData(projectilesData);
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