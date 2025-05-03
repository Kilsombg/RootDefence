#ifndef __Tower__
#define __Tower__

#include "SDLGameObject.h"
#include "Enemy.h"

#include "../UtilsHeaders/BaseCreator.h"
#include "../UtilsHeaders/Timer.h"

#include<string>
#include<memory>

class Tower : public SDLGameObject
{
public:
	enum TowerType { towerTypes };

	Tower();
	float getRadius() const;
	TowerType getTowerType();

	float getDamage() const;
	std::string getProjectileID();
	std::weak_ptr<Enemy> getTargetEnemy() const;

	virtual void update() override;
	virtual void draw() override;
	void load(const std::shared_ptr<LoaderParams> pParams);
	/**
	* look for enemy in radius to target
	* @param enemies is a vector of objects in current state
	*/
	void targetEnemy(std::vector<std::shared_ptr<Enemy>> enemies);
	/**
	* check wheather the enemy is in tower radius
	*/
	bool inRadius(std::shared_ptr<Enemy> enemy);
	/**
	* execute attack interval
	*/
	void aimEnemy();
	

private:

	enum priceType {};

	std::string m_projectileID;
	float m_attackSpeed;
	Timer m_attackTimer;
	float m_damage;
	float m_radius;
	int m_baseCost;
	priceType m_priceType;
	TowerType m_towerType;
	std::weak_ptr<Enemy> m_targetEnemy;
};

class TowerCreator : public BaseCreator
{
	std::unique_ptr<GameObject> createGameObject() const;
};

#endif // !__Tower__