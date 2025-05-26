#include "../../include/WaveHeaders/WaveManager.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/GameStateHeaders/VictoryState.h"

#include "../../include/UtilsHeaders/GameObjectFactory.h"
#include "../../include/UtilsHeaders/LoaderParams.h"
#include "../../include/UtilsHeaders/Vector2D.h"

#include "../../include/Game.h"

#include<iostream>

std::shared_ptr<WaveManager> WaveManager::s_pInstance = nullptr;
bool WaveManager::s_pressedPlayButton = false;
bool WaveManager::s_hasNoEnemiesOnScreen = false;

int WaveManager::getCurrentWaveID()
{
	return m_currentWaveID;
}

WaveManager::WaveManager()
{
}

std::shared_ptr<WaveManager> WaveManager::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = std::shared_ptr<WaveManager>(new WaveManager);
		return s_pInstance;
	}
	return s_pInstance;
}

void WaveManager::spawnWaveEnemies(std::vector<std::shared_ptr<Vector2D>>& enemyPath, Wave& wave, std::function<void(std::unique_ptr<Enemy>)> addEnemyCallback, float dT)
{
	// update flag
	s_hasNoEnemiesOnScreen = m_enemyObjects->empty();

	// if not pressed play button, then return
	if (!s_pressedPlayButton) return;

	m_eClusters = &(wave.getEnemyClusters());
	Timer* spawnTimer = &(wave.getSpawnTimer());
	Timer* roundTimer = &(wave.getRoundTimer());

	spawnTimer->countDown(dT);

	//Check if the round needs to start.
	if (m_eClusters->empty())
	{
		// stop wave untill play button is pressed
		if (s_pressedPlayButton && !m_stoppedWaveAfterEnd)
		{
			s_pressedPlayButton = false;
			m_stoppedWaveAfterEnd = true;
			return;
		}

		// activate round timer and start wave if timer finish
		roundTimer->countDown(dT);
		if (roundTimer->timeSIsZero()) {
			nextWave(wave);
			if (&wave != NULL)
			{
				roundTimer->resetToMax();
				m_stoppedWaveAfterEnd = false;
			}
		}
	}
	else
	{

		//Add an enemy if needed.
		if (m_eClusters->begin()->count > 0 && spawnTimer->timeSIsZero()) {
			if (std::unique_ptr<GameObject> e = GameObjectFactory::Instance()->create(m_eClusters->begin()->enemyType))
			{
				if (std::unique_ptr<Enemy> en = std::unique_ptr<Enemy>(dynamic_cast<Enemy*>(e.release())))
				{
					std::shared_ptr<LoaderParams> pParams = m_gameObjectData->getData(m_eClusters->begin()->enemyType);
					if (!enemyPath.empty())
					{
						pParams->setAttribute(LoaderParamsConsts::x, enemyPath[0]->getX());
						pParams->setAttribute(LoaderParamsConsts::y, enemyPath[0]->getY());
						en->setPath(enemyPath);
					}
					en->load(pParams);

					//std::cout << "adding enemy.\n";
					addEnemyCallback(std::move(en));
				}
				else
				{
					e.reset();  // remove object to prevent memory leak
				}

				m_eClusters->begin()->count--;
				spawnTimer->resetToMax();
			}
		}
		else
		{
			// check if all of the enemies in the cluster are spawned
			if (m_eClusters->begin()->count == 0)
			{
				m_eClusters->erase(m_eClusters->begin());
			}
		}
	}
}

void WaveManager::nextWave(Wave& wave)
{
	if (!isFinalWave())
	{
		std::cout << "Changing wave.\n";
		wave = *(m_waves[++m_currentWaveID]);
	}
	else
	{
		// implement random generated wave
		std::cout << "final wave finished!\n";
	}
}

void WaveManager::setEnemyObjects(std::shared_ptr<std::vector<std::shared_ptr<Enemy>>> pEnemiesObjects)
{
	m_enemyObjects = pEnemiesObjects;
}

void WaveManager::handleEvents()
{
	// handle victory state
	if (isFinalWave() && s_hasNoEnemiesOnScreen && m_eClusters != nullptr && m_eClusters->empty())
	{
		std::shared_ptr<VictoryState> victoryState = std::make_shared<VictoryState>();
		victoryState->setCurrentWaveID(m_currentWaveID);
		TheGame::Instance()->getStateMachine()->pushState(victoryState);
	}
}

bool WaveManager::isActivePlayButton()
{
	return !s_pressedPlayButton && s_hasNoEnemiesOnScreen;
}

bool WaveManager::isFinalWave()
{
	return m_currentWaveID >= m_maxWave;
}

void WaveManager::setGameObjectData(GameObjectData<LoaderParams>& gameObjectdata)
{
	m_gameObjectData = std::make_unique<GameObjectData<LoaderParams>>(gameObjectdata);
}

void WaveManager::s_activateWave()
{
	if (isActivePlayButton())
	{
		s_pressedPlayButton = true;
	}
}


std::vector<Wave*>& WaveManager::getWaves()
{
	return m_waves;
}

void WaveManager::clean()
{
	// clean waves
	if (!m_waves.empty())
	{
		for (std::vector<Wave>::size_type i = 0; i < m_waves.size(); i++)
		{
			m_waves[i]->clean();
		}
		m_waves.clear();
		m_waves.shrink_to_fit();
	}

	// reset static variables
	s_pressedPlayButton = false;
	s_hasNoEnemiesOnScreen = false;

	// clean enemies clusters
	m_eClusters = nullptr;

	// clean pointer
	s_pInstance = nullptr;
}

void WaveManager::load()
{
	if (!m_waves.empty())
	{
		m_maxWave = m_waves.size() - 1;
		m_currentWaveID = 0;
	}
	else
	{
		std::cerr << "Couldn't find waves in WaveManager.\n";
	}
}

