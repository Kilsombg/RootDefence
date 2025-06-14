#ifndef __ProjectileManager__
#define __ProjectileManager__

#include "GameObjectData.h"

#include "../EntitiesHeaders/Projectile.h"
#include "../EntitiesHeaders/Tower.h"

#include<vector>
#include<memory>

/**
* Manages projectiles.
* 
* Update each projectile on screen and manage deletion after hit.
* 
* Calls clean() when finished with ProjectileManager.
*/
class ProjectileManager
{
public:
	static std::shared_ptr<ProjectileManager> Instance();
	/**
	* Update projectiles and cleans on hitEnemy.
	*/
	void update();
	/**
	* Render all active projectiles on screen.
	*/
	void render();
	/**
	* Cleans projectiles and projectile data.
	*/
	void clean();
	/**
	* Create projectile based on tower.
	*/
	void createProjectile(Tower& tower);
	/**
	* Add projectile to active vector.
	*/
	void addProjectile(std::unique_ptr<Projectile> projectileToAdd);
	/**
	* Set projecitle data, used for creation projectiles.
	*/
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
