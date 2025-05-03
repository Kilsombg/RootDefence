#include "../../include/WaveHeaders/WaveManager.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/GameStateHeaders/GameOverState.h"

#include "../../include/UtilsHeaders/GameObjectFactory.h"
#include "../../include/UtilsHeaders/LoaderParams.h"
#include "../../include/UtilsHeaders/Vector2D.h"

#include "../../include/Game.h"

#include<iostream>

std::shared_ptr<WaveManager> WaveManager::s_pInstance = nullptr;

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
	std::vector<EnemyCluster>* eClusters = &(wave.getEnemyClusters());
	Timer* spawnTimer = &(wave.getSpawnTimer());
	Timer* roundTimer = &(wave.getRoundTimer());

	spawnTimer->countDown(dT);

	//Check if the round needs to start.
	if (eClusters->empty())
	{
		roundTimer->countDown(dT);
		if (roundTimer->timeSIsZero()) {
			nextWave(wave);
			if (&wave != NULL)
			{
				roundTimer->resetToMax();
			}
		}
	}
	else
	{
		
		//Add an enemy if needed.
		if (eClusters->begin()->count > 0 && spawnTimer->timeSIsZero()) {
			if (std::unique_ptr<GameObject> e = GameObjectFactory::Instance()->create(eClusters->begin()->enemyType))
			{
				if (std::unique_ptr<Enemy> en = std::unique_ptr<Enemy>(dynamic_cast<Enemy*>(e.release()))) 
				{
					std::shared_ptr<LoaderParams> pParams = m_gameObjectData->getData(eClusters->begin()->enemyType);
					if (!enemyPath.empty())
					{
						pParams->setAttribute(LoaderParamsConsts::x, enemyPath[0]->getX());
						pParams->setAttribute(LoaderParamsConsts::y, enemyPath[0]->getY());
						en->setPath(enemyPath);
					}
					en->load(pParams);

					std::cout << "adding enemy.\n";
					addEnemyCallback(std::move(en));
				}
				else
				{
					e.reset();  // remove object to prevent memory leak
				}
			
				eClusters->begin()->count--;
				spawnTimer->resetToMax();
			}
		}
		else
		{
			// check if all of the enemies in the cluster are spawned
			if (eClusters->begin()->count == 0)
			{
				eClusters->erase(eClusters->begin());
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
		//TheGame::Instance()->getStateMachine()->pushState(std::make_shared<GameOverState>());
	}
}

bool WaveManager::isFinalWave()
{
	return m_currentWaveID >= m_maxWave;
}

void WaveManager::setGameObjectData(GameObjectData& gameObjectdata)
{
	m_gameObjectData = std::make_unique<GameObjectData>(gameObjectdata);
}

std::vector<Wave*>& WaveManager::getWaves()
{
	return m_waves;
}

void WaveManager::clean()
{
	if (!m_waves.empty())
	{
		for (std::vector<Wave>::size_type i = 0; i < m_waves.size(); i++)
		{
			m_waves[i]->clean();
		}
		m_waves.clear();
		m_waves.shrink_to_fit();
	}
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

