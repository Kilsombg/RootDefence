#include "../../include/EntitiesHeaders/Enemy.h"

#include "../../include/Constants/ColorsConsts.h"
#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/Game.h"
#include "../../include/UtilsHeaders/TextureManager.h"

#include<SDL.h>

#include<iostream>

Enemy::Enemy() : SDLGameObject()
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
	m_distFromWaypoint = 0;
	m_distanceToWaypoint = 0;
	m_distance = 0;

	SDLGameObject::load(pParams);

	m_healthBarWidth = m_width / 2;
	m_healthBarHeight = 5;
}

float Enemy::getHealth()
{
	return m_health;
}

void Enemy::setPath(const std::vector<std::shared_ptr<Vector2D>>& pathPoints)
{
	m_path = pathPoints;
}

float Enemy::getDistance()
{
	return m_distance;
}

void Enemy::dealDamage(float damage)
{
	m_health -= damage;
}

bool Enemy::isAlive()
{
	return m_health > 0;
}

void Enemy::draw()
{
	SDLGameObject::draw();

	if (m_health < m_maxHealth)
	{
		TheTextureManager::Instance()->drawProgressBar(
			m_position.getX() + m_width / 4, m_position.getY(), m_healthBarWidth, m_healthBarHeight,
			{ ColorsConsts::black.r, ColorsConsts::black.g, ColorsConsts::black.b, ColorsConsts::black.a },
			{ ColorsConsts::green.r, ColorsConsts::green.g, ColorsConsts::green.b, ColorsConsts::green.a },
			m_health / m_maxHealth,
			TheGame::Instance()->getRenderer());
	}
}

void Enemy::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

	move();
	m_distance = m_distanceToWaypoint + m_distFromWaypoint;

	SDLGameObject::update();
}

void Enemy::move()
{
	if (m_path.size() >= 0 && m_movePathTileID < m_path.size())
	{
		std::shared_ptr<Vector2D> pathPoint = m_path[m_movePathTileID];
		m_velocity = *(pathPoint)-m_position;

		if (m_velocity.length() < m_moveSpeed)
		{
			m_movePathTileID++;
			Vector2D distV = m_movePathTileID < m_path.size() ? *(m_path[m_movePathTileID]) - *(pathPoint) : 0;
			m_distanceToWaypoint += distV.length();
			m_distFromWaypoint = 0;
			return;
		}

		m_velocity.normalize();
		m_velocity *= m_moveSpeed;
		m_distFromWaypoint += m_moveSpeed;
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