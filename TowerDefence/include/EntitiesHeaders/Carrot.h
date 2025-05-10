#ifndef __Carrot__
#define __Carrot__

#include "Enemy.h"

#include "../UtilsHeaders/BaseCreator.h"

class Carrot : public Enemy
{
public:
	Carrot();

	void draw();
	void update();
	void clean();

	void load(const std::shared_ptr<LoaderParams> pParams);
};

class CarrotCreator : public BaseCreator
{
	std::unique_ptr<GameObject> create() const override;
};

#endif // !__Carrot__
