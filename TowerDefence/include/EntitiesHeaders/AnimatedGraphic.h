#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__

#include "SDLGameObject.h"

#include "../UtilsHeaders/BaseCreator.h"

#include<memory>

/**
* Class for animaiton graphics. It is running with m_animSpeed frames per second.
*/
class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic();

	void update() override;
	void draw() override;
	void clean() override;
	void load(const std::shared_ptr<LoaderParams> pParams) override;

private:
	int m_animSpeed;
};

class AnimatedGraphicCreator : public BaseCreator
{
public:
	std::unique_ptr<GameObject> create() const override;
};


#endif // !__AnimatedGraphic__
