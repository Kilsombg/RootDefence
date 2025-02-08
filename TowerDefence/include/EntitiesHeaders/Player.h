#ifndef __Player__
#define __Player__

#include "SDLGameObject.h"

#include "../UtilsHeaders/BaseCreator.h"

#include<memory>

class Player : public SDLGameObject
{
public:
	Player();
	void handleInput();

	virtual void draw();
	virtual void update();
	virtual void clean();

	void load(const std::shared_ptr<LoaderParams> pParams);
};

class PlayerCreator : public BaseCreator
{
	std::unique_ptr<GameObject> createGameObject() const;
};

#endif // !__Player__