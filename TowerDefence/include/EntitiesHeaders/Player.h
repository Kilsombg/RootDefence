#ifndef __Player__
#define __Player__

#include "SDLGameObject.h"

#include "../UtilsHeaders/BaseCreator.h"

class Player : public SDLGameObject
{
public:
	Player();
	void handleInput();

	virtual void draw();
	virtual void update();
	virtual void clean();

	void load(const LoaderParams* pParams);
};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const;
};

#endif // !__Player__