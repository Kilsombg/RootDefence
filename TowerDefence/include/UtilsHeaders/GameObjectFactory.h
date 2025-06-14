#ifndef __GameObjectFactory__
#define __GameObjectFactory__

#include "BaseCreator.h"
#include "BaseFactory.h"

#include "../EntitiesHeaders/GameObject.h"

#include<memory>

/**
* Factory class for creating gameObjects.
*/
class GameObjectFactory : public BaseFactory<GameObject, BaseCreator>
{
public:
	static std::shared_ptr<GameObjectFactory> Instance();

private:
	GameObjectFactory();
	static std::shared_ptr<GameObjectFactory> s_pInstance;
};

typedef GameObjectFactory TheGameObjectFactory;

#endif // !__GameObjectFactory__
