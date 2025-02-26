#ifndef __BaseButtonListener__
#define __BaseButtonListener__

#include "../../include/EntitiesHeaders/Button.h"

class BaseButtonHandler
{
public:
	virtual void handleEvent(Button* sourceButton) = 0;
};

#endif // !__BaseButtonListener__
