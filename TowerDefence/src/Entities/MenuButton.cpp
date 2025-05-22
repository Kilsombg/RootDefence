#include "../../include/EntitiesHeaders/MenuButton.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/UtilsHeaders/InputHandler.h"

MenuButton::MenuButton() : Button()
{
}

MenuButton::MenuButton(const MenuButton* menuButton) : Button(menuButton)
{
	m_callback = menuButton->m_callback;
}

void MenuButton::load(const std::shared_ptr<LoaderParams> pParams)
{
	Button::load(pParams);
}

void MenuButton::handleEvent()
{
	handleOutsideCLick();

	handleClickOnButton();
}

void MenuButton::setCallback(void(*callback)())
{
	m_callback = callback;
}

void MenuButton::setCurrentRow(int currentRow)
{
	m_currentRow = currentRow;
}

void MenuButton::update()
{
	m_isMouseOnButton = TheInputHandler::Instance()->isMouseOnObject(m_position, m_width, m_height);
}

void MenuButton::handleOutsideCLick()
{
	if (!m_isMouseOnButton)
	{
		m_pressedOutside = TheInputHandler::Instance()->getMouseButtonState(LEFT);
	}
	else
	{
		if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_pressedOutside = false;
		}
	}
}

void MenuButton::handleClickOnButton()
{
	if (m_isMouseOnButton && !m_pressedOutside)
	{
		m_currentFrame = MOUSE_OVER;

		if (!TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			m_currentFrame = CLICKED;

			m_callback();

			m_bReleased = false;
		}
		else if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_bReleased = true;
		}
	}
	else
	{
		m_bReleased = false;

		m_currentFrame = MOUSE_OUT;
	}
}


std::unique_ptr<GameObject> MenuButtonCreator::create() const
{
	return std::make_unique<MenuButton>();
}
