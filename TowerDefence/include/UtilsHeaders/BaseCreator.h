#ifndef __BaseCreator__
#define __BaseCreator__

#include "../EntitiesHeaders/GameObject.h"

class BaseCreator
{
public:
	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator() {}
};

#endif // !__BaseCreator__
