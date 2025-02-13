#ifndef __Enemy__
#define __Enemy__

#include "SDLGameObject.h"

#include "../UtilsHeaders/BaseCreator.h"

#include<vector>
#include<memory>

class Enemy : public SDLGameObject
{
public:
	Enemy();

	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void load(const std::shared_ptr<LoaderParams> pParams);

	void setPath(std::shared_ptr<std::vector<std::shared_ptr<Vector2D>>> pathPoints);

	bool isAlive();

private:
	void move();

	std::shared_ptr<std::vector<std::shared_ptr<Vector2D>>> m_path;
	bool m_isAlive;
};


class EnemyCreator : public BaseCreator
{
public:
	std::unique_ptr<GameObject> createGameObject() const;
};

#endif // !__Enemy__
