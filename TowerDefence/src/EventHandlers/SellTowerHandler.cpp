#include "../../include/EventHandlersHeaders/SellTowerHandler.h"

#include "../../include/ManagersHeaders/SellManager.h"

void SellTowerHandler::handleSellTowerEvent(std::shared_ptr<Tower> selectedTower)
{
	// if tower not passed, then return
	if (!selectedTower) return;

	// erase from towers' vector
	TheSellManager::Instance()->sellSelectedTower();
	for (auto it = m_playStateTowers->begin(); it != m_playStateTowers->end(); it++)
	{
		if (*it == selectedTower)
		{
			m_playStateTowers->erase(it);
			return;
		}
	}
}

void SellTowerHandler::setPlayStateTowers(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> playStateTowers)
{
	m_playStateTowers = playStateTowers;
}

void SellTowerHandler::setLevel(std::shared_ptr<Level> level)
{
	pLevel = level;
}
