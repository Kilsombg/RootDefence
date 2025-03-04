#include "../../include/EntitiesHeaders/Tower.h"

#include "../../include/Constants/LoaderParamsConsts.h"

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

	m_radius = pParams->getAttribute<float>(LoaderParamsConsts::radius);
}

std::unique_ptr<GameObject> TowerCreator::createGameObject() const
{
	return std::make_unique<Tower>();
}