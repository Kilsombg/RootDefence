#include "../../include/EntitiesHeaders/Tower.h"

Tower::Tower() : SDLGameObject(), m_attackSpeed(0), m_damage(0), m_radius(0), m_baseCost(0)
{
}

float Tower::getRadius()
{
	return m_radius;
}

Tower::TowerType Tower::getTowerType()
{
	return m_towerType;
}

void Tower::load(const std::shared_ptr<LoaderParams> pParams)
{
	SDLGameObject::load(pParams);
}

std::unique_ptr<GameObject> TowerCreator::createGameObject() const
{
	return std::unique_ptr<GameObject>();
}