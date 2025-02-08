#include "../../include/EntitiesHeaders/MenuButton.h"

#include "../../include/UtilsHeaders/InputHandler.h"

MenuButton::MenuButton() : SDLGameObject()
{
}

void MenuButton::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);

	m_callbackID = pParams->getCallbackID();
	m_currentFrame = MOUSE_OUT;
	m_bReleased = false;
}

void MenuButton::setCallback(void(*callback)())
{
	m_callback = callback;
}

int MenuButton::getCallbackID()
{
	return m_callbackID;
}

void MenuButton::draw()
{
	SDLGameObject::draw();
}

void MenuButton::update()
{
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();

	if (pMousePos->getX() < (m_position.getX() + m_width)
		&& pMousePos->getX() > m_position.getX()
		&& pMousePos->getY() < (m_position.getY() + m_height)
		&& pMousePos->getY() > m_position.getY())
	{
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			m_currentFrame = CLICKED;

			m_callback();

			m_bReleased = false;
		}
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_bReleased = true;

			m_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}

std::unique_ptr<GameObject> MenuButtonCreator::createGameObject() const
{
	return std::make_unique<MenuButton>();
}
