#ifndef __BaseCreator__
#define __BaseCreator__

#include "../EntitiesHeaders/GameObject.h"

#include<memory>

class BaseCreator
{
public:
	virtual std::unique_ptr<GameObject> createGameObject() const = 0;
	virtual ~BaseCreator() {}
};

#endif // !__BaseCreator__
