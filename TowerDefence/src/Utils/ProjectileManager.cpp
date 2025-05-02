#include "../../include//UtilsHeaders/ProjectileManager.h"

#include "../../include/Constants/GameObjectConsts.h"

#include "../../include/UtilsHeaders/GameObjectFactory.h"
#include "../../include/UtilsHeaders/Vector2D.h"

#include<iostream>

ProjectileManager* ProjectileManager::s_pInstance = nullptr;

ProjectileManager* ProjectileManager::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = new ProjectileManager();
		return s_pInstance;
	}
	return s_pInstance;
}

ProjectileManager::ProjectileManager()
{
}

void ProjectileManager::update()
{
	for (std::vector<std::unique_ptr<Projectile>>::size_type i = 0; i < m_activeProjectiles.size(); i++)
	{
		m_activeProjectiles[i]->update();

		if (m_activeProjectiles[i]->hitEnemy() && m_activeProjectiles[i]->getTargetEnemy().use_count())
		{
			m_activeProjectiles[i]->getTargetEnemy().lock()->dealDamage(m_activeProjectiles[i]->getDamage());
			std::cout << "target enemy health: " << m_activeProjectiles[i]->getTargetEnemy().lock()->getHealth() << '\n';
			m_activeProjectiles.erase(m_activeProjectiles.begin() + i--);

		}
	}
}

void ProjectileManager::render()
{
	for (std::vector<std::unique_ptr<Projectile>>::size_type i = 0; i < m_activeProjectiles.size(); i++)
	{
		m_activeProjectiles[i]->draw();
	}
}

void ProjectileManager::clean()
{
	delete s_pInstance;
	s_pInstance = nullptr;
}

void ProjectileManager::createProjectile(Tower& tower)
{
	if (std::unique_ptr<GameObject> projectileObject = TheGameObjectFactory::Instance()->create(GameObjectConsts::projectile))
	{
		if (std::unique_ptr<Projectile> projectile = std::unique_ptr<Projectile>(dynamic_cast<Projectile*>(projectileObject.release())))
		{
			projectile->setDamage(tower.getDamage());
			projectile->setTargetEnemy(tower.getTargetEnemy());
			projectile->setSpeed(tower.getProjectileSpeed());
			Vector2D topCenterPos = Vector2D(tower.getPosition().getX() + tower.getWidth() / 2, tower.getPosition().getY());
			projectile->setPosition(topCenterPos);
			
			m_activeProjectiles.push_back(std::move(projectile));
		}
		else
		{
			projectileObject.reset(); // remove object to prevent memory leak
		};
	}
}

void ProjectileManager::addProjectile(std::unique_ptr<Projectile> projectileToAdd)
{
	m_activeProjectiles.push_back(std::move(projectileToAdd));
}
