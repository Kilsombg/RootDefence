#include "../../include/EntitiesHeaders/Button.h"

#include "../../include/Constants/LoaderParamsConsts.h"

Button::Button() : SDLGameObject(), m_bReleased(false), m_pressedOutside(false)
{
}

void Button::load(const std::shared_ptr<LoaderParams> pParams)
{
	SDLGameObject::load(pParams);

	m_callbackID = pParams->getAttribute<std::string>(LoaderParamsConsts::callbackID);
	m_currentFrame = MOUSE_OUT;
	m_bReleased = false;
}

std::string Button::getCallbackID()
{
	return m_callbackID;
}

