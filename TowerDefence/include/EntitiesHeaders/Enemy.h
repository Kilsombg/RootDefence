#ifndef __Enemy__
#define __Enemy__

#include "SDLGameObject.h"

#include "../GameStateHeaders/PlayState.h"

#include<vector>
#include<memory>

class Enemy : public SDLGameObject
{
public:
	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void load(const std::shared_ptr<LoaderParams> pParams);

	/**
	* set points for the path that enemies follow
	*/ 
	void setPath(std::vector<std::shared_ptr<Vector2D>> pathPoints);

	bool isAlive();

protected:
	Enemy();

	float m_moveSpeed;
	float m_maxHealth;
	float m_health; // current health points
	float m_defence;

private:
	/**
	* move enemy position from its position to the points of m_paath.
	*/
	void move();

	std::vector<std::shared_ptr<Vector2D>> m_path;
	int m_movePathTileID; // represent which point from the path the Enemy is heading
};

#endif // !__Enemy__
