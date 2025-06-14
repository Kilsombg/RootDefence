#ifndef __Button__
#define __Button__

#include "SDLGameObject.h"

/**
* Base class for buttons.
* 
* override handleEvent() to handle button's event.
*/
class Button : public SDLGameObject
{
public:
	Button();
	Button(const Button* button);

	virtual void load(const std::shared_ptr<LoaderParams> pParams) override;
	virtual void handleEvent();

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
