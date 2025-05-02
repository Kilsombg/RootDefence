#ifndef __Enemy__
#define __Enemy__

#include "SDLGameObject.h"

#include<vector>
#include<memory>

class Enemy : public SDLGameObject
{
public:
	Enemy();
	Enemy(const Enemy& e);
	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void load(const std::shared_ptr<LoaderParams> pParams);

	float getHealth();

	/**
	* set points for the path that enemies follow
	*/
	void setPath(const std::vector<std::shared_ptr<Vector2D>>& pathPoints);

	/**
	* @return total distance moved
	*/
	float getDistance();

	/** reduce health by damage
	*/
	void dealDamage(float damage);

	bool isAlive();

protected:
	float m_moveSpeed;
	float m_maxHealth;
	float m_health; // current health points
	float m_defence;

private:
	/**
	* move enemy position from its position to the points of m_paath.
	*/
	void move();

	std::vector < std::shared_ptr<Vector2D>> m_path;
	int m_movePathTileID; // represent which point from the path the Enemy is heading
	float m_distFromWaypoint; // current distance from passed path tile to enemy
	float m_distanceToWaypoint; // distance from the start to currently passed path tile
	float m_distance; // total distance moved
};

#endif // !__Enemy__
