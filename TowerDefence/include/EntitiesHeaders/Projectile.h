#ifndef __Projectile__
#define __Projectile__

#include "SDLGameObject.h"

#include "Enemy.h"

#include "../UtilsHeaders/BaseCreator.h"

#include<memory>

class Projectile : public SDLGameObject
{
public:
	Projectile();
	Projectile(const Projectile& proj);

	void update() override;
	void draw() override;

	void setDamage(float damage);
	float getDamage();
	void setSpeed(float speed);
	void setTargetEnemy(std::weak_ptr<Enemy> targetEnemy);
	std::weak_ptr<Enemy> getTargetEnemy();
	bool hitEnemy();

private:
	void move();

	float m_damage;
	float m_speed;
	std::weak_ptr<Enemy> m_targetEnemy;
	float m_targetCenterX, m_targetCenterY;
	bool m_hitEnemy;
};


class ProjectileCreator : public BaseCreator
{
public:
	virtual std::unique_ptr<GameObject> createGameObject() const;
};

#endif // !__Projectile__
