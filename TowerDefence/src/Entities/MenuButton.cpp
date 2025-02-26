#include "../../include/EntitiesHeaders/MenuButton.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/UtilsHeaders/InputHandler.h"

MenuButton::MenuButton() : Button()
{
}

void MenuButton::load(const std::shared_ptr<LoaderParams> pParams)
{
	Button::load(pParams);
}

void MenuButton::setCallback(void(*callback)())
{
	m_callback = callback;
}
void MenuButton::update()
{
	std::shared_ptr<Vector2D> pMousePos = TheInputHandler::Instance()->getMousePosition();

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

std::unique_ptr<GameObject> MenuButtonCreator::createGameObject() const
{
	return std::make_unique<MenuButton>();
}
