#ifndef __TowerFactory__
#define __TowerFactory__

#include "GameObjectData.h"

#include "../EntitiesHeaders/Tower.h"

#include<string>
#include<map>
#include<memory>

/**
* Factory class for creating towers.
* 
* It sets tower upgrades if exists.
*/
class TowerFactory
{
public:
	static std::shared_ptr<TowerFactory> Instance();

	std::unique_ptr<GameObject> createTower(std::string towerTypeID);
	/**
	* Creates tower and loads with base attributes.
	* 
	* @param towerTypeId - id of towers to be created.
	* @param color - type of tower.
	*/
	std::shared_ptr<Tower> createShadowTower(std::string towerTypeID, std::string color);
	/**
	* Check the prefix from textureID of towers if it color type.
	*/
	bool canTowerBeColored(std::string colorType);

	// getters and setters.

	/**
	* Get data for a specific tower.
	*/
	std::shared_ptr<LoaderParams> getTowerData(std::string towerTypeID);
	/**
	* Get all tower's cost.
	*/
	std::map<std::string, int> getTowersCostValue();
	/**
	* Set all towerObjects data.
	*/
	void setTowerObjectData(GameObjectData<LoaderParams>& gameObjectdata);
	/**
	* Set all tower upgrades data.
	*/
	void setTowerUpgradeObjectData(GameObjectData<ArrayOf2TowerUpgradesData>& towerUpgradeData);
	/**
	* Get current tower cost.
	*/
	int getTowerCost(int baseCost);

private:
	TowerFactory();
	static std::shared_ptr<TowerFactory> s_pInstance;

	void modifyTower(std::shared_ptr<Tower> tower, std::shared_ptr<LoaderParams> params);

	std::unique_ptr<GameObjectData<LoaderParams>> m_towerObjectData; // base tower stats
	std::unique_ptr<GameObjectData<ArrayOf2TowerUpgradesData>> m_towerUpgradeData; // tower upgrade stats
};

typedef TowerFactory TheTowerFactory;

#endif // !__TowerFactory__