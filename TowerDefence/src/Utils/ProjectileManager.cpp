#include "../../include//UtilsHeaders/ProjectileManager.h"

#include "../../include/Constants/GameObjectConsts.h"
#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/UtilsHeaders/GameObjectFactory.h"
#include "../../include/UtilsHeaders/LoaderParams.h"
#include "../../include/UtilsHeaders/Vector2D.h"

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
			params->setAttribute(LoaderParamsConsts::x, tower.getPosition().getX() + tower.getWidth() / 2);
			params->setAttribute(LoaderParamsConsts::y, tower.getPosition().getY());
			
			projectile->load(params);
			projectile->setTargetEnemy(tower.getTargetEnemy());
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
