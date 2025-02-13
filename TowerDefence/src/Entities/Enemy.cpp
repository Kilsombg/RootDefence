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
	m_isAlive = true;
}

void Enemy::setPath(std::shared_ptr<std::vector<std::shared_ptr<Vector2D>>> pathPoints)
{
	m_path = pathPoints;
}

bool Enemy::isAlive()
{
	return m_isAlive;
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

	move();

	SDLGameObject::update();
}

void Enemy::move()
{
	if (m_path->size() >= 0)
	{
		std::shared_ptr<Vector2D> pathPoint = m_path.get()[0][0];
	}
}


void Enemy::clean()
{
	SDLGameObject::clean();
}

std::unique_ptr<GameObject> EnemyCreator::createGameObject() const
{
	return std::make_unique<Enemy>();
}
