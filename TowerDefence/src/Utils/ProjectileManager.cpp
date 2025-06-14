#include "../../include//UtilsHeaders/ProjectileManager.h"

#include "../../include/Constants/GameObjectConsts.h"
#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/UtilsHeaders/GameObjectFactory.h"
#include "../../include/UtilsHeaders/LoaderParams.h"

#include<iostream>

std::shared_ptr<ProjectileManager> ProjectileManager::s_pInstance = nullptr;

std::shared_ptr<ProjectileManager> ProjectileManager::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = std::shared_ptr<ProjectileManager>(new ProjectileManager);
		return s_pInstance;
	}
	return s_pInstance;
}

ProjectileManager::ProjectileManager()
{
}

float ProjectileManager::damageToEnemy(Projectile* projectile)
{
	// if enemy type is the same as tower's than it hits at 100%, otherwise reduce to 50% damage
	float damageMultiplier = projectile->getTargetEnemy().lock()->getDrop().type == projectile->getTowersType() ? 1. : 0.5;

	return damageMultiplier * projectile->getDamage();
}

void ProjectileManager::update()
{
	for (std::vector<std::unique_ptr<Projectile>>::size_type i = 0; i < m_activeProjectiles.size(); i++)
	{
		m_activeProjectiles[i]->update();

		if (m_activeProjectiles[i]->hitEnemy())
		{
			// if enemy is still alive then deal damage
			if (m_activeProjectiles[i]->getTargetEnemy().use_count()) 
			{
				float damageDealt = m_activeProjectiles[i]->getTargetEnemy().lock()->dealDamage(damageToEnemy(m_activeProjectiles[i].get()));
				m_activeProjectiles[i]->getTowerOrigin()->incrementDealtDamage(damageDealt);
				//std::cout << "target enemy health: " << m_activeProjectiles[i]->getTargetEnemy().lock()->getHealth() << '\n';
			}

			// remove projectile from the game
			m_activeProjectiles[i]->clean();
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
	m_activeProjectiles.clear();
	m_projectilesData = nullptr;

}

void ProjectileManager::createProjectile(Tower& tower)
{
	if (std::unique_ptr<GameObject> projectileObject = TheGameObjectFactory::Instance()->create(GameObjectConsts::projectile))
	{
		if (std::unique_ptr<Projectile> projectile = std::unique_ptr<Projectile>(dynamic_cast<Projectile*>(projectileObject.release())))
		{
			std::shared_ptr<LoaderParams> params = m_projectilesData->getData(tower.getProjectileID());
			params->setAttribute(LoaderParamsConsts::damage, tower.getDamage());
			params->setAttribute(LoaderParamsConsts::towerColor, tower.getColor());
			params->setAttribute(LoaderParamsConsts::x, tower.getPosition().getX() + tower.getWidth() / 2);
			params->setAttribute(LoaderParamsConsts::y, tower.getPosition().getY());
			
			projectile->load(params);
			projectile->setTargetEnemy(tower.getTargetEnemy());
			projectile->setTowerOrigin(&tower);
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

void ProjectileManager::setGameObjectData(GameObjectData<LoaderParams>& gameObjectdata)
{
	m_projectilesData = std::make_unique<GameObjectData<LoaderParams>>(gameObjectdata);
}
