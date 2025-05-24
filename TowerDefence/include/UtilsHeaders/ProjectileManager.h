#ifndef __ProjectileManager__
#define __ProjectileManager__

#include "GameObjectData.h"

#include "../EntitiesHeaders/Projectile.h"
#include "../EntitiesHeaders/Tower.h"

#include<vector>
#include<memory>

class ProjectileManager
{
public:
	static std::shared_ptr<ProjectileManager> Instance();
	void update();
	void render();
	void clean();

	void createProjectile(Tower& tower);
	void addProjectile(std::unique_ptr<Projectile> projectileToAdd);

	void setGameObjectData(GameObjectData<LoaderParams>& gameObjectdata);

private:
	ProjectileManager();
	/**
	* calculates damage dealt to enemy, corresponding to type.
	*/
	float damageToEnemy(Projectile* projectile);

	static std::shared_ptr<ProjectileManager> s_pInstance;
	std::vector<std::unique_ptr<Projectile>> m_activeProjectiles;
	std::unique_ptr<GameObjectData<LoaderParams>> m_projectilesData;
};

typedef ProjectileManager TheProjectileManager;

#endif // !__ProjectileManager__
