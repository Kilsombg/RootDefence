#include "../../include/EntitiesHeaders/Enemy.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include<SDL.h>

#include<iostream>

Enemy::Enemy()
{
}

Enemy::Enemy(const Enemy& e) : SDLGameObject(e)
{
	m_moveSpeed = e.m_moveSpeed;
	m_maxHealth = e.m_maxHealth;
	m_health = e.m_health;
	m_defence = e.m_defence;
	m_path = e.m_path;
	m_movePathTileID = e.m_movePathTileID;
}

void Enemy::load(const std::shared_ptr<LoaderParams> pParams)
{
	m_moveSpeed = pParams->getAttribute<float>(LoaderParamsConsts::moveSpeed) ? pParams->getAttribute<float>(LoaderParamsConsts::moveSpeed) : 0;
	m_maxHealth = pParams->getAttribute<float>(LoaderParamsConsts::maxHealth) ? pParams->getAttribute<float>(LoaderParamsConsts::maxHealth) : 0;
	m_health = m_maxHealth;
	m_defence = pParams->getAttribute<float>(LoaderParamsConsts::defence) ? pParams->getAttribute<float>(LoaderParamsConsts::defence) : 0;
	m_movePathTileID = 0;
	SDLGameObject::load(pParams);
}

void Enemy::setPath(const std::vector<std::shared_ptr<Vector2D>>& pathPoints)
{
	m_path = pathPoints;
}

bool Enemy::isAlive()
{
	return m_health > 0;
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
		m_velocity = *(pathPoint) - m_position;

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
		m_health = 0;
	}
}


void Enemy::clean()
{
	m_path.clear();
	SDLGameObject::clean();
}