#include "../../include/ManagersHeaders/SellManager.h"

std::shared_ptr<SellManager> SellManager::s_pInstance = nullptr;

std::shared_ptr<SellManager> SellManager::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = std::shared_ptr<SellManager>(new SellManager);
		return s_pInstance;
	}
	return s_pInstance;
}


SellManager::SellManager() : m_baseSellPercentage(0.4)
{
}

void SellManager::clean()
{
	s_pInstance = nullptr;
}

void SellManager::setSelectedTower(std::shared_ptr<Tower> selectedTower)
{
	m_selectedTower = selectedTower;
}

void SellManager::setGameSessionData(std::shared_ptr<GameSessionData> gameSessionData)
{
	m_gameSessionData = gameSessionData;
}

float SellManager::getBaseSellPercentage()
{
	return m_baseSellPercentage;
}

void SellManager::sellSelectedTower()
{
	// if there is no activeTower, then return
	if (m_selectedTower.use_count() == 0) return;

	Resource towerSpentResources = m_selectedTower->getSpentResources();
	m_gameSessionData->resources[towerSpentResources.type].value += static_cast<int>(std::floor(m_baseSellPercentage * towerSpentResources.value));
}

void SellManager::updateSpentResources(Resource resource)
{
	// if there is no activeTower, then return
	if (m_selectedTower.use_count() == 0) return;

	// increase spent resources if resource's type is matching
	Resource towerSpentResources = m_selectedTower->getSpentResources();
	if (towerSpentResources.type == resource.type)
	{
		resource.value += towerSpentResources.value;
		m_selectedTower->setSpentResources(resource);
	}
}
