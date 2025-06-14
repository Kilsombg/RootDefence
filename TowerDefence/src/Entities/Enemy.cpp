#include "../../include/EntitiesHeaders/Enemy.h"

#include "../../include/Constants/ColorsConsts.h"
#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/Game.h"
#include "../../include/UtilsHeaders/TextureManager.h"

#include<SDL.h>

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
	m_speedMultiplier = e.m_speedMultiplier;
	m_slowAdditive = e.m_slowAdditive;
	m_maxSlowPercentage = e.m_maxSlowPercentage;
}

void Enemy::load(const std::shared_ptr<LoaderParams> pParams)
{
	m_moveSpeed = pParams->getAttribute<float>(LoaderParamsConsts::moveSpeed) ? pParams->getAttribute<float>(LoaderParamsConsts::moveSpeed) : 0;
	m_maxHealth = pParams->getAttribute<float>(LoaderParamsConsts::maxHealth) ? pParams->getAttribute<float>(LoaderParamsConsts::maxHealth) : 0;
	m_health = m_maxHealth;
	m_defence = pParams->getAttribute<float>(LoaderParamsConsts::defence) ? pParams->getAttribute<float>(LoaderParamsConsts::defence) : 0;
	m_drop.type = getResourceTypeByString(pParams->getAttribute<std::string>(LoaderParamsConsts::dropType));
	m_drop.value = pParams->getAttribute<int>(LoaderParamsConsts::dropValue) ? pParams->getAttribute<int>(LoaderParamsConsts::dropValue) : 0;
	m_movePathTileID = 0;
	m_distFromWaypoint = 0;
	m_distanceToWaypoint = 0;
	m_distance = 0;
	m_speedMultiplier = 1;
	m_slowAdditive = 0;
	m_maxSlowPercentage = 0.8;
	m_crossEndOfPath = false;

	SDLGameObject::load(pParams);

	m_healthBarWidth = m_width / 2;
	m_healthBarHeight = 5;
}

float Enemy::getHealth()
{
	return m_health;
}

Resource Enemy::getDrop()
{
	return m_drop;
}

void Enemy::setPath(const std::vector<std::shared_ptr<Vector2D>>& pathPoints)
{
	m_path = pathPoints;
}

float Enemy::getDistance()
{
	return m_distance;
}

void Enemy::slow(float slowPercentage)
{
	m_slowAdditive += slowPercentage;
	if (m_slowAdditive > m_maxSlowPercentage) m_slowAdditive = m_maxSlowPercentage;
}

bool Enemy::isCrossEndOfPath()
{
	return m_crossEndOfPath;
}

float Enemy::dealDamage(float damage)
{
	float actualDamageTaken = damage * (1 - m_defence);
	m_health -= actualDamageTaken;
	if (m_health < 0) m_health = 0;

	return actualDamageTaken;
}

bool Enemy::isAlive()
{
	return m_health > 0;
}

void Enemy::draw()
{
	// draw enemy object
	SDLGameObject::draw();

	// draw progress bar
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
	// update animation
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

	// move
	move();
	m_distance = m_distanceToWaypoint + m_distFromWaypoint;

	// reset slow percentage
	if(m_slowAdditive != 0) m_slowAdditive = 0;

	SDLGameObject::update();
}

void Enemy::move()
{
	float actualSpeed = getActualMovementSpeed();

	// if enemy has path and not in last point
	if (m_path.size() >= 0 && m_movePathTileID < m_path.size())
	{
		// point enemy to the pathPoint
		std::shared_ptr<Vector2D> pathPoint = m_path[m_movePathTileID];
		m_velocity = *(pathPoint)-m_position;

		// change pathPoint when enemy is close to current
		if (m_velocity.length() < actualSpeed)
		{
			m_movePathTileID++;

			// increase the distance moved from start to current waypoint
			Vector2D distV = m_movePathTileID < m_path.size() ? *(m_path[m_movePathTileID]) - *(pathPoint) : 0;
			m_distanceToWaypoint += distV.length();
			m_distFromWaypoint = 0;
			return;
		}

		// if target is far away get the direction to target and change the magnitude to enemy speed
		m_velocity.normalize();
		m_velocity *= actualSpeed;
		// increase the distance from pathPoint to enemy
		m_distFromWaypoint += actualSpeed;
	}
	else
	{
		// went to END of the path
		m_crossEndOfPath = true;
	}
}

float Enemy::getActualMovementSpeed()
{
	return (m_speedMultiplier - m_slowAdditive) * m_moveSpeed;
}


void Enemy::clean()
{
	m_path.clear();
	SDLGameObject::clean();
}

std::unique_ptr<GameObject> EnemyCreator::create() const
{
	return std::make_unique<Enemy>();
}
