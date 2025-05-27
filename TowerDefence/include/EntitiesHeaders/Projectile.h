#ifndef __Projectile__
#define __Projectile__

#include "SDLGameObject.h"
#include "Enemy.h"
#include "Tower.h"

#include "../DataHeaders/GameSessionData.h"


#include "../UtilsHeaders/BaseCreator.h"
#include "../UtilsHeaders/LoaderParams.h"

#include<memory>

class Projectile : public SDLGameObject
{
public:
	Projectile();
	Projectile(const Projectile& proj);

	void update() override;
	void draw() override;
	void load(const std::shared_ptr<LoaderParams> pParams) override;
	void clean() override;

	// getters and setters

	float getDamage();

	void setTargetEnemy(std::weak_ptr<Enemy> targetEnemy);
	std::weak_ptr<Enemy> getTargetEnemy();
	
	void setTowerOrigin(Tower* towerOrigin);
	Tower* getTowerOrigin();

	ResourceType getTowersType();
	
	bool hitEnemy();

private:
	void move();

	float m_damage;
	ResourceType m_towerType;
	float m_speed;
	std::weak_ptr<Enemy> m_targetEnemy;
	Tower* m_towerOrigin; // pointer to the tower, that created the projectile
	float m_targetCenterX, m_targetCenterY;
	bool m_hitEnemy; // flag for hit enemy, used in projectile manager
};


class ProjectileCreator : public BaseCreator
{
public:
	virtual std::unique_ptr<GameObject> create() const override;
};

#endif // !__Projectile__
