#include "../../include/EntitiesHeaders/Tower.h"

#include "../../include/Game.h"

#include "../../include/Constants/LoaderParamsConsts.h"
#include "../../include/Constants/SettingsConsts.h"
#include "../../include/Constants/ColorsConsts.h"


#include "../../include/UtilsHeaders/Vector2D.h"
#include "../../include/UtilsHeaders/GameObjectFactory.h"
#include "../../include/UtilsHeaders/ProjectileManager.h"
#include "../../include/UtilsHeaders/TextureManager.h"


#include<iostream>

Tower::Tower() : SDLGameObject(), m_projectileID(""), m_attackSpeed(0), m_damage(0), m_radius(0), m_baseCost(0), m_selected(false), m_attackTimer(0)
{
}

float Tower::getRadius() const
{
	return m_radius;
}

Tower::TowerType Tower::getTowerType()
{
	return m_towerType;
}

float Tower::getDamage() const
{
	return m_damage;
}

std::string Tower::getProjectileID()
{
	return m_projectileID;
}

std::weak_ptr<Enemy> Tower::getTargetEnemy() const
{
	return m_targetEnemy;
}

void Tower::update()
{
	SDLGameObject::update();

	aimEnemy();
}

void Tower::draw()
{
	TheTextureManager::Instance()->drawFilledCircle(
		m_position.getX(), m_position.getY(), static_cast<int>(m_radius),
		{ ColorsConsts::gray.r, ColorsConsts::gray.g, ColorsConsts::gray.b, ColorsConsts::gray.a },
		TheGame::Instance()->getRenderer());

	SDLGameObject::draw();
}

void Tower::load(const std::shared_ptr<LoaderParams> pParams)
{
	SDLGameObject::load(pParams);

	m_projectileID = pParams->getAttribute<std::string>(LoaderParamsConsts::projectileID);
	m_damage = pParams->getAttribute<float>(LoaderParamsConsts::damage);
	m_radius = pParams->getAttribute<float>(LoaderParamsConsts::radius);
	m_attackSpeed = pParams->getAttribute<float>(LoaderParamsConsts::attackSpeed);
	float attackInterval = 1 / m_attackSpeed;
	m_attackTimer = Timer(attackInterval, attackInterval);
}

void Tower::targetEnemy(std::vector<std::shared_ptr<Enemy>> enemies)
{
	if (enemies.empty()) return;

	// if tower has target in range then skip searching a target, otherwise clear it
	if (inRadius(m_targetEnemy.lock())) { return; }
	else { m_targetEnemy.reset(); }

	std::shared_ptr<Enemy> tempEnemy;
	int index = 0;

	// get first enemy in radius if any
	while (tempEnemy.get() == nullptr && index < enemies.size())
	{
		if (inRadius(enemies[index]))
		{
			tempEnemy = enemies[index];
		}
		index++;
	}

	// get farthest enemy on the map in tower radius
	for (std::vector<std::shared_ptr<Enemy>>::size_type i = index; i < enemies.size(); i++)
	{
		if (tempEnemy->getDistance() < enemies[i]->getDistance() && inRadius(enemies[i]))
		{
			tempEnemy = enemies[i];
		}
	}

	// if there is none enemies in radius then return
	if (tempEnemy.get() == nullptr) return;

	// put target enemy to the tower
	if (m_targetEnemy.lock() != tempEnemy)
	{
		m_targetEnemy = tempEnemy;
	}
}

bool Tower::inRadius(std::shared_ptr<Enemy> enemy)
{
	if (enemy.get() == nullptr) return false;

	Vector2D topLeft = Vector2D(enemy->getPosition());
	Vector2D topRight = Vector2D(enemy->getPosition().getX() + enemy->getWidth(), enemy->getPosition().getY());
	Vector2D bottomLeft = Vector2D(enemy->getPosition().getX(), enemy->getPosition().getY() + enemy->getHeight());
	Vector2D bottomRight = Vector2D(enemy->getPosition().getX() + enemy->getWidth(), enemy->getPosition().getY() + enemy->getHeight());

	return Vector2D::distance(getPosition(), topLeft) <= getRadius() ||
		Vector2D::distance(getPosition(), topRight) <= getRadius() ||
		Vector2D::distance(getPosition(), bottomLeft) <= getRadius() ||
		Vector2D::distance(getPosition(), bottomRight) <= getRadius();
}

bool Tower::isSelected()
{
	return m_selected;
}

void Tower::aimEnemy()
{
	if (!m_targetEnemy.expired())
	{
		m_attackTimer.countDown(DELAY_TIME / 1000.);

		if (m_attackTimer.timeSIsZero())
		{
			TheProjectileManager::Instance()->createProjectile(*this);
			m_attackTimer.resetToMax();
			std::cout << "tower projectile created\n";
		}
	}
	else
	{
		m_attackTimer.resetToMax();
	}
}

std::unique_ptr<GameObject> TowerCreator::createGameObject() const
{
	return std::make_unique<Tower>();
}