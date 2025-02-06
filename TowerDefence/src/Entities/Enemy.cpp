#include "../../include/EntitiesHeaders/Enemy.h"

#include<SDL.h>

Enemy::Enemy() : SDLGameObject()
{
}

void Enemy::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);


	m_velocity.setY(2);
	m_velocity.setX(0.001);
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

	if (m_position.getY() < 0)
	{
		m_velocity.setY(2);
	}
	else if (m_position.getY() > 400)
	{
		m_velocity.setY(-2);
	}

	SDLGameObject::update();
}

void Enemy::clean()
{
	SDLGameObject::clean();
}

GameObject* EnemyCreator::createGameObject() const
{
	return new Enemy();
}
