#ifndef __TowerFactory__
#define __TowerFactory__

#include "GameObjectData.h"

#include "../EntitiesHeaders/Tower.h"

#include<memory>

class TowerFactory
{
public:
	static std::shared_ptr<TowerFactory> Instance();

	std::unique_ptr<GameObject> createTower(std::string towerTypeID);
	std::shared_ptr<Tower> createShadowTower(std::string towerTypeID);

	void setTowerObjectData(GameObjectData<LoaderParams>& gameObjectdata);
	void setTowerUpgradeObjectData(GameObjectData<ArrayOf2TowerUpgradesData>& towerUpgradeData);

private:
	TowerFactory();
	static std::shared_ptr<TowerFactory> s_pInstance;

	std::unique_ptr<GameObjectData<LoaderParams>> m_towerObjectData; // base tower stats
	std::unique_ptr<GameObjectData<ArrayOf2TowerUpgradesData>> m_towerUpgradeData; // tower upgrade stats
};

typedef TowerFactory TheTowerFactory;

#endif // !__TowerFactory__