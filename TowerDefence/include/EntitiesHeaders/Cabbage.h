#ifndef __Cabbage__
#define __Cabbage__

#include "Enemy.h"

#include "../UtilsHeaders/BaseCreator.h"

class Cabbage : public Enemy
{
public:
	Cabbage();

	void draw();
	void update();
	void clean();

	void load(const std::shared_ptr<LoaderParams> pParams);
};

class CabbageCreator : public BaseCreator
{
	std::unique_ptr<GameObject> createGameObject() const;
};

#endif // !__Cabbage__