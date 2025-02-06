#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__

#include "SDLGameObject.h"

#include "../UtilsHeaders/BaseCreator.h"

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
	GameObject* createGameObject() const;
};


#endif // !__AnimatedGraphic__
