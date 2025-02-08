#ifndef __Enemy__
#define __Enemy__

#include "SDLGameObject.h"

#include "../UtilsHeaders/BaseCreator.h"

#include<memory>

class Enemy : public SDLGameObject
{
public:
	Enemy();
	
	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void load(const LoaderParams* pParams);
};


class EnemyCreator : public BaseCreator
{
public:
	std::unique_ptr<GameObject> createGameObject() const;
};

#endif // !__Enemy__
