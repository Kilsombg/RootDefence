#include "../../include/EntitiesHeaders/Carrot.h"

Carrot::Carrot() : Enemy()
{
}

void Carrot::draw()
{
	Enemy::draw();
}

void Carrot::update()
{
	Enemy::update();
}

void Carrot::clean()
{
	Enemy::clean();
}

void Carrot::load(const std::shared_ptr<LoaderParams> pParams)
{
	m_moveSpeed = 1.8;
	m_maxHealth = 5;
	m_defence = 1;

	Enemy::load(pParams);
}

std::unique_ptr<GameObject> CarrotCreator::createGameObject() const
{
	return std::make_unique<Carrot>();
}
