#ifndef __MenuButton__
#define __MenuButton__

#include "../UtilsHeaders/BaseCreator.h"

#include "SDLGameObject.h"

class MenuButton : public SDLGameObject
{
public:

	MenuButton();

	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void load(const LoaderParams* pParams);

	void setCallback(void(*callback)());
	int getCallbackID();

private:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	bool m_bReleased;
	int m_callbackID;
	void (*m_callback)();
};

class MenuButtonCreator : public BaseCreator
{
public:
	GameObject* createGameObject() const;
};

#endif // !__MenuButton__
