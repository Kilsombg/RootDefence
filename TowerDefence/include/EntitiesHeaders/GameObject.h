#ifndef __GameObject__
#define __GameObject__

#include "../UtilsHeaders/LoaderParams.h"

#include<memory>

class GameObject
{
public:
	virtual ~GameObject();

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

	virtual void load(const std::shared_ptr<LoaderParams> pParams) = 0;

protected:
	GameObject();
};

#endif // !__GameObject__

