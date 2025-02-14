#ifndef __Carrot__
#define __Carrot__

#include "Enemy.h"

class Carrot : Enemy
{
public:
	Carrot();

	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void load(const std::shared_ptr<LoaderParams> pParams);
};

#endif // !__Carrot__
