#include "../../include/UtilsHeaders/TowerFactory.h"
#include "../../include/UtilsHeaders/GameObjectData.h"
#include "../../include/UtilsHeaders/GameObjectFactory.h"
#include "../../include/UtilsHeaders/LoaderParams.h"
#include "../../include/UtilsHeaders/InputHandler.h"


#include "../../include/Constants/LoaderParamsConsts.h"
#include "../../include/Constants/GameObjectConsts.h"

#include "../../include/ManagersHeaders/DifficultyManager.h"

std::shared_ptr<TowerFactory> TowerFactory::s_pInstance = nullptr;

int TowerFactory::getTowerCost(int baseCost)
{
	float costMulti = DifficultyManager::Instance()->getTowerPriceMultiplayer();

	return std::floor(baseCost * costMulti);;
}

TowerFactory::TowerFactory() {}

void TowerFactory::modifyTower(std::shared_ptr<Tower> tower, std::shared_ptr<LoaderParams> params)
{
	float costMulti = DifficultyManager::Instance()->getTowerPriceMultiplayer();

	// modify cost
	int towerBaseCost = params->getAttribute<int>(LoaderParamsConsts::costValue);
	params->setAttribute(LoaderParamsConsts::costValue, getTowerCost(towerBaseCost));

	// modify upgrades
	for (auto& towerUpgrade : tower->getTowerUpgradesData())
	{
		for (auto& costUpgrade : towerUpgrade.costs)
		{
			costUpgrade = std::floor(costUpgrade * costMulti);
		}
	}
}


std::shared_ptr<TowerFactory> TowerFactory::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = std::shared_ptr<TowerFactory>(new TowerFactory);
		return s_pInstance;
	}
	return s_pInstance;
}

std::unique_ptr<GameObject> TowerFactory::createTower(std::string towerTypeID)
{
	return std::unique_ptr<GameObject>();
}

std::shared_ptr<Tower> TowerFactory::createShadowTower(std::string towerTypeID, std::string color)
{
	if (std::unique_ptr<GameObject>	towerObject = TheGameObjectFactory::Instance()->create(towerTypeID))
	{
		if (std::shared_ptr<Tower> shadowObject = std::shared_ptr<Tower>(dynamic_cast<Tower*>(towerObject.release())))
		{
			// get base params from towerObject data
			std::shared_ptr<LoaderParams> params = m_towerObjectData->getData(towerTypeID);

			// set param attributes
			// set towerUpgrades data
			if (m_towerUpgradeData->getData(towerTypeID))
			{
				shadowObject->setTowerUpgradesData(*m_towerUpgradeData->getData(towerTypeID).get());
			}

			// set additional position
			std::shared_ptr<Vector2D> mousePos = InputHandler::Instance()->getMousePosition();
			params->setAttribute(LoaderParamsConsts::x, mousePos->getX());
			params->setAttribute(LoaderParamsConsts::y, mousePos->getY());
			params->setAttribute(LoaderParamsConsts::costType, color);
			params->setAttribute(LoaderParamsConsts::color, color);


			// set tower modifications
			modifyTower(shadowObject, params);

			// load params into the shadow object and return it
			shadowObject->load(params);
			return shadowObject;
		}
		else {
			towerObject.reset();  // remove object to prevent memory leak
		}
	}
	return nullptr;
}

bool TowerFactory::canTowerBeColored(std::string colorType)
{
	return colorType == TowerTypeConsts::green || colorType == TowerTypeConsts::yellow || colorType == TowerTypeConsts::red;
}

std::shared_ptr<LoaderParams> TowerFactory::getTowerData(std::string towerTypeID)
{
	return m_towerObjectData->getData(towerTypeID);
}

std::map<std::string, int> TowerFactory::getTowersCostValue()
{
	std::map<std::string, int> towersCost;

	// get all data for towers
	std::map<std::string, std::shared_ptr<LoaderParams>> towersData = m_towerObjectData->getObjectsData();

	for (std::map<std::string, std::shared_ptr<LoaderParams>>::iterator it = towersData.begin(); it != towersData.end(); it++)
	{
		towersCost[it->first] = it->second->getAttribute<int>(LoaderParamsConsts::costValue);
	}

	return towersCost;
}

void TowerFactory::setTowerObjectData(GameObjectData<LoaderParams>& gameObjectdata)
{
	m_towerObjectData = std::make_unique<GameObjectData<LoaderParams>>(gameObjectdata);
}

void TowerFactory::setTowerUpgradeObjectData(GameObjectData<ArrayOf2TowerUpgradesData>& towerUpgradeData)
{
	m_towerUpgradeData = std::make_unique<GameObjectData<ArrayOf2TowerUpgradesData>>(towerUpgradeData);
}
