#ifndef __TowerObject__
#define __TowerObject__

#include "SDLGameObject.h"
#include "../UtilsHeaders/BaseCreator.h"

class Tower : public SDLGameObject
{
public:
	enum TowerType { fede };

	Tower();
	float getRadius();
	TowerType getTowerType();

	void load(const std::shared_ptr<LoaderParams> pParams);

private:
	enum priceType {};

	float m_attackSpeed;
	float m_damage;
	float m_radius;
	int m_baseCost;
	priceType m_priceType;
	TowerType m_towerType;
};

class TowerCreator : public BaseCreator
{
	std::unique_ptr<GameObject> createGameObject() const;
};

#endif // !__TowerObject__