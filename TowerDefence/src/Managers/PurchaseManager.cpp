#include "../../include/ManagersHeaders/PurchaseManager.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/ManagersHeaders/SellManager.h"

#include "../../include/UtilsHeaders/LoaderParams.h"
#include "../../include/UtilsHeaders/TowerFactory.h"

std::shared_ptr<PurchaseManager> PurchaseManager::s_pInstance = nullptr;

std::shared_ptr<PurchaseManager> PurchaseManager::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = std::shared_ptr<PurchaseManager>(new PurchaseManager);
		return s_pInstance;
	}
	return s_pInstance;
}

PurchaseManager::PurchaseManager()
{
}

void PurchaseManager::clean()
{
	s_pInstance = nullptr;
}

void PurchaseManager::setGameSessionData(std::shared_ptr<GameSessionData> gameSessionData)
{
	m_gameSessionData = gameSessionData;
}

bool PurchaseManager::canPurchaseTower(std::string towerName, std::string towerColor)
{
	// get the tower cost and resourceType
	int towerCost = getTowerCostByName(towerName);
	ResourceType resourceType = getResourceTypeByString(towerColor);
	if (resourceType == NOT_RESOURCE_TYPE) return false;

	// check if there are enough resources
	return towerCost <= m_gameSessionData->resources[resourceType].value;
}

void PurchaseManager::purchaseTower(Resource towerCostResource)
{
	m_gameSessionData->resources[towerCostResource.type].value -= towerCostResource.value;
	TheSellManager::Instance()->updateSpentResources(towerCostResource);
}

int PurchaseManager::getTowerCostByName(std::string towerName)
{
	std::map<std::string, int>::iterator it = m_towerCosts.find(towerName);

	if (it == m_towerCosts.end())
	{
		// not found in map, get the data from towerFactory
		std::shared_ptr<LoaderParams> pParams = TheTowerFactory::Instance()->getTowerData(towerName);
		m_towerCosts[towerName] = pParams->getAttribute<int>(LoaderParamsConsts::costValue);
		return m_towerCosts[towerName];
	}

	return it->second;
}


bool PurchaseManager::canPurchaseUpgrade(TowerUpgradeData towerUpgradeData, std::string towerColor)
{
	// if already on max level, then no need to purchase
	if (towerUpgradeData.nextLevel >= towerUpgradeData.maxLevel) return false;

	// check if there are enough resources
	ResourceType resourceType = getResourceTypeByString(towerColor);
	if (resourceType == NOT_RESOURCE_TYPE) return false;

	return towerUpgradeData.costs[towerUpgradeData.nextLevel] <= m_gameSessionData->resources[resourceType].value;
}

void PurchaseManager::purchaseUpgrade(int upgradeCost, std::string towerColor)
{
	ResourceType resourceType = getResourceTypeByString(towerColor);
	if (resourceType == NOT_RESOURCE_TYPE) return;

	m_gameSessionData->resources[resourceType].value -= upgradeCost;
	TheSellManager::Instance()->updateSpentResources(Resource{ getResourceTypeByString(towerColor), upgradeCost });
}
