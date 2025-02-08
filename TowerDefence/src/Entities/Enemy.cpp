#include "../../include/EntitiesHeaders/Enemy.h"

#include<SDL.h>

Enemy::Enemy() : SDLGameObject()
{
}

void Enemy::load(const std::shared_ptr<LoaderParams> pParams)
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
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

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

std::unique_ptr<GameObject> EnemyCreator::createGameObject() const
{
	return std::make_unique<Enemy>();
}
