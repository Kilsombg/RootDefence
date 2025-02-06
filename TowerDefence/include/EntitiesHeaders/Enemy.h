#ifndef __Enemy__
#define __Enemy__

#include "SDLGameObject.h"

#include "../UtilsHeaders/BaseCreator.h"

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
	GameObject* createGameObject() const;
};

#endif // !__Enemy__
