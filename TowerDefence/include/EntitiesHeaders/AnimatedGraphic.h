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
	void load(const std::shared_ptr<LoaderParams> pParams);

private:
	int m_animSpeed;
};

class AnimatedGraphicCreator : public BaseCreator
{
public:
	std::unique_ptr<GameObject> create() const override;
};


#endif // !__AnimatedGraphic__
