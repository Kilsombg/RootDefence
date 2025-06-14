#ifndef __BaseCreator__
#define __BaseCreator__

#include "Creator.h"

#include "../EntitiesHeaders/GameObject.h"

/**
* Creator class for gameObjects.
*/
class BaseCreator : public Creator<GameObject>
{
public:
	virtual ~BaseCreator() {}
};

#endif // !__BaseCreator__
