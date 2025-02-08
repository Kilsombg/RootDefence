#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__

#include "SDLGameObject.h"

#include "../UtilsHeaders/BaseCreator.h"

#include<memory>

class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic();

	void update();
	void draw();
	void clean();
	void load(const LoaderParams* pParams);

private:
	int m_animSpeed;
};

class AnimatedGraphicCreator : public BaseCreator
{
public:
	std::unique_ptr<GameObject> createGameObject() const;
};


#endif // !__AnimatedGraphic__
