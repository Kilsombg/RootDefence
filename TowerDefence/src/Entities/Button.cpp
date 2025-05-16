#include "../../include/EntitiesHeaders/Button.h"

#include "../../include/Constants/LoaderParamsConsts.h"

Button::Button() : SDLGameObject(), m_bReleased(false), m_pressedOutside(false), m_isMouseOnButton(false)
{
}

Button::Button(const Button* button) : SDLGameObject(*button)
{
	m_bReleased = button->m_bReleased;
	m_isMouseOnButton = button->m_isMouseOnButton;
	m_pressedOutside - button->m_pressedOutside;
	m_callbackID = button->m_callbackID;
}

void Button::load(const std::shared_ptr<LoaderParams> pParams)
{
	SDLGameObject::load(pParams);

	m_callbackID = pParams->getAttribute<std::string>(LoaderParamsConsts::callbackID);
	m_currentFrame = MOUSE_OUT;
	m_bReleased = false;
}

void Button::handleEvent()
{
}

std::string Button::getCallbackID()
{
	return m_callbackID;
}

