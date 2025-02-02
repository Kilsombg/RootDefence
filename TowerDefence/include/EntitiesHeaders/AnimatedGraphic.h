#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__

#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic(const LoaderParams* pParams, int animSpeed);

	void update();
	void draw();
	void clean();
	void load(const LoaderParams* pParams);

private:
	int m_animSpeed;
};

#endif // !__AnimatedGraphic__
