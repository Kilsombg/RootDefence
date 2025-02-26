#ifndef __Button__
#define __Button__

#include "SDLGameObject.h"

class Button : public SDLGameObject
{
public:
	Button();

	virtual void load(const std::shared_ptr<LoaderParams> pParams);

	std::string getCallbackID();

protected:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	bool m_bReleased;
	bool m_isMouseOnButton;
	bool m_pressedOutside;
	std::string m_callbackID;
};

#endif // !__Button__
