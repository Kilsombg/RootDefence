#ifndef __ObjectLayer__
#define __ObjectLayer__

#include "Layer.h"

#include "../EntitiesHeaders/GameObject.h"

#include<vector>
#include<memory>

/**
* Object layer of map.
* 
* It contains enemy's path and pathAreas.
*/
class ObjectLayer : public Layer
{
public:
	virtual void update();
	virtual void render();
	
	std::vector<std::shared_ptr<GameObject>>* getGameObjects();

private:
	std::vector<std::shared_ptr<GameObject>> m_gameObjects;
};


#endif // !__ObjectLayer__
