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

private:
	/**
	* move enemy position from its position to the points of m_paath.
	*/
	void move();

	std::vector<std::shared_ptr<Vector2D>> m_path;
	float m_moveSpeed;
	int m_movePathTileID;
	bool m_isAlive;
};

#endif // !__Enemy__
