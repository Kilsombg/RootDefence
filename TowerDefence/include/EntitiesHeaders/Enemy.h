#ifndef __Enemy__
#define __Enemy__

#include "SDLGameObject.h"

#include "../UtilsHeaders/BaseCreator.h"

#include "../DataHeaders/GameSessionData.h"

#include<vector>
#include<memory>
#include<string>

/**
* Base class for enemies.
*/
class Enemy : public SDLGameObject
{
public:
	Enemy();
	Enemy(const Enemy& e);
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	virtual void load(const std::shared_ptr<LoaderParams> pParams) override;

	// setters and getters

	float getHealth();

	Resource getDrop();

	int getExp();

	/**
	* set points for the path that enemies follow
	*/
	void setPath(const std::vector<std::shared_ptr<Vector2D>>& pathPoints);

	/**
	* @return total distance moved
	*/
	float getDistance();

	/**
	* slow enemy with additive percentage
	*/
	void slow(float slowPercentage);

	/**
	* return true if enemy is crossed to the end of path
	*/
	bool isCrossEndOfPath();

	/** reduce health by damage
	*/
	float dealDamage(float damage);

	bool isAlive();

protected:
	float m_moveSpeed;
	float m_maxHealth;
	float m_health; // current health points
	float m_defence; // percent reduction.
	Resource m_drop;

private:
	/**
	* move enemy position from its position to the points of m_paath.
	*/
	void move();
	/**
	* get enemy's movement speed with multipliers applied.
	*/
	float getActualMovementSpeed();

	std::vector < std::shared_ptr<Vector2D>> m_path;
	int m_exp; // experience value that drops upon death
	int m_movePathTileID; // represent which point from the path the Enemy is heading
	float m_distFromWaypoint; // current distance from passed path tile to enemy
	float m_distanceToWaypoint; // distance from the start to currently passed path tile
	float m_distance; // total distance moved
	float m_speedMultiplier; // multiply directly to moveSpeed
	float m_slowAdditive; // additive percentage of slowness
	float m_maxSlowPercentage; // maximum percentage the enemy can be slowed
	bool m_crossEndOfPath; // flag if enemy is passed the finish line
	int m_healthBarWidth;
	int m_healthBarHeight;
};



class EnemyCreator : public BaseCreator
{
	std::unique_ptr<GameObject> create() const override;
};

#endif // !__Enemy__
