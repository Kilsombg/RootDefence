#ifndef __TowerFactory__
#define __TowerFactory__

#include "GameObjectData.h"

#include "../EntitiesHeaders/Tower.h"

#include<string>
#include<map>
#include<memory>

class TowerFactory
{
public:
	static std::shared_ptr<TowerFactory> Instance();

	std::unique_ptr<GameObject> createTower(std::string towerTypeID);
	std::shared_ptr<Tower> createShadowTower(std::string towerTypeID, std::string color);


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

private:
	TowerFactory();
	static std::shared_ptr<TowerFactory> s_pInstance;

	std::unique_ptr<GameObjectData<LoaderParams>> m_towerObjectData; // base tower stats
	std::unique_ptr<GameObjectData<ArrayOf2TowerUpgradesData>> m_towerUpgradeData; // tower upgrade stats
};

typedef TowerFactory TheTowerFactory;

#endif // !__TowerFactory__