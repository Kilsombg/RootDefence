#include "../../include/EntitiesHeaders/Enemy.h"

#include<SDL.h>

#include<iostream>

Enemy::Enemy() : SDLGameObject()
{
}

void Enemy::load(const std::shared_ptr<LoaderParams> pParams)
{
	SDLGameObject::load(pParams);
	m_isAlive = true;
	m_moveSpeed = 1.5;
	m_movePathTileID = 0;
}

void Enemy::setPath(std::vector<std::shared_ptr<Vector2D>> pathPoints)
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
	if (m_path.size() >= 0 && m_movePathTileID < m_path.size())
	{
		std::shared_ptr<Vector2D> pathPoint = m_path[m_movePathTileID];
		m_velocity = (*pathPoint) - m_position;

		if (m_velocity.length() < m_moveSpeed)
		{
			m_movePathTileID++;
			return;
		}

		m_velocity.normalize();
		m_velocity *= m_moveSpeed;
	}
	else
	{
		m_isAlive = false;
	}
}


void Enemy::clean()
{
	m_path.clear();
	SDLGameObject::clean();
}

std::unique_ptr<GameObject> EnemyCreator::createGameObject() const
{
	return std::make_unique<Enemy>();
}
