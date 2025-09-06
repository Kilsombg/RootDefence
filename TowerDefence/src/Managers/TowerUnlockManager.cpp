#include "../../include/ManagersHeaders/TowerUnlockManager.h"

#include "../../include/Game.h"

std::shared_ptr<TowerUnlockManager> TowerUnlockManager::s_pInstance = nullptr;

std::shared_ptr<TowerUnlockManager> TowerUnlockManager::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = std::shared_ptr<TowerUnlockManager>(new TowerUnlockManager);
		return s_pInstance;
	}
	return s_pInstance;
}

TowerUnlockManager::TowerUnlockManager()
{
	m_towerUnlocks = TheGame::Instance()->getProgressManager()->getTowerUnlocks();
}

std::string TowerUnlockManager::unlockTowerByLevelUp()
{
	if (!m_towerUnlocks.use_count()) return std::string();

	short curLVL = TheGame::Instance()->getProgressManager()->getGameProgress()->level;

	for (std::vector<TowerUnlocksDTO>::iterator it = m_towerUnlocks->begin(); it != m_towerUnlocks->end(); it++)
	{
		if (it->require_level == curLVL)
		{
			TheGame::Instance()->getProgressManager()->unlockTower(it->id);
			return it->name;
		}
	}

	return std::string();
}

bool TowerUnlockManager::isUnlocked(std::string towerName)
{
	for (std::vector<TowerUnlocksDTO>::iterator it = m_towerUnlocks->begin(); it != m_towerUnlocks->end(); it++)
	{
		if (it->name == towerName)
		{
			return it->unlocked;
		}
	}

	// if not found then return false
	return false;
}
