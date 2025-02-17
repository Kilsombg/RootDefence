#include "../../include/EntitiesHeaders/Cabbage.h"

Cabbage::Cabbage() : Enemy()
{
}

void Cabbage::draw()
{
	Enemy::draw();
}

void Cabbage::update()
{
	Enemy::update();
}

void Cabbage::clean()
{
	Enemy::clean();
}

void Cabbage::load(const std::shared_ptr<LoaderParams> pParams)
{
	m_moveSpeed = 1.2;
	m_maxHealth = 7;
	m_defence = 2;

	Enemy::load(pParams);
}

std::unique_ptr<GameObject> CabbageCreator::createGameObject() const
{
	return std::make_unique<Cabbage>();
}
