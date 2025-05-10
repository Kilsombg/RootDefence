#ifndef __Panel__
#define __Panel__

#include "../../EntitiesHeaders/GameObject.h"

#include<vector>
#include<memory>

/**
* base class for panels
*/
class Panel
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void load(std::vector<std::unique_ptr<GameObject>> gameObjects) = 0;
};

#endif // !__Panel__
