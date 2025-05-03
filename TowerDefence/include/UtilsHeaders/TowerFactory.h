#ifndef __TowerFactory__
#define __TowerFactory__

//#include "GameObjectFactory.h"
#include "GameObjectData.h"

#include "../EntitiesHeaders/Tower.h"

#include<memory>

class TowerFactory
{
public:
	static std::shared_ptr<TowerFactory> Instance();

	std::unique_ptr<GameObject> createTower(std::string towerTypeID);
	std::unique_ptr<Tower> createShadowTower(std::string towerTypeID);

	void setGameObjectData(GameObjectData& gameObjectdata);

private:
	TowerFactory();
	static std::shared_ptr<TowerFactory> s_pInstance;

	std::unique_ptr<GameObjectData> m_towerObjectData; // base tower stats
};

typedef TowerFactory TheTowerFactory;

#endif // !__TowerFactory__