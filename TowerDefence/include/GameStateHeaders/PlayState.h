#ifndef __PlayState__
#define __PlayState__

#include "GameState.h"

#include "../EntitiesHeaders/GameObject.h"
#include "../EntitiesHeaders/SDLGameObject.h"

#include "../MapHeaders/Level.h"

#include<vector>
#include<memory>

class PlayState : public GameState
{
public:
	PlayState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const;


	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);


private:
	std::shared_ptr<Level> pLevel;

	void handleEvents();
};

#endif // !__PlayState__
