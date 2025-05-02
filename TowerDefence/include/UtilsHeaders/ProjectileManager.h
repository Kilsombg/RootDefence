#ifndef __ProjectileManager__
#define __ProjectileManager__

#include "../EntitiesHeaders/Projectile.h"
#include "../EntitiesHeaders/Tower.h"

#include<vector>
#include<memory>

class ProjectileManager
{
public:
	static ProjectileManager* Instance();
	void update();
	void render();
	void clean();

	void createProjectile(Tower& tower);
	void addProjectile(std::unique_ptr<Projectile> projectileToAdd);

private:
	ProjectileManager();
	static ProjectileManager* s_pInstance;
	std::vector<std::unique_ptr<Projectile>> m_activeProjectiles;
};

typedef ProjectileManager TheProjectileManager;

#endif // !__ProjectileManager__
