#include "../../include/EntitiesHeaders/SellTowerButton.h"

#include "../../include/UtilsHeaders/InputHandler.h"

SellTowerButton::SellTowerButton() : SelectedTowerButton(), m_selected(false), m_pressed(false)
{
}

void SellTowerButton::handleEvent()
{
	handleOutsideCLick();

	handleClickOnButton();
}

void SellTowerButton::update()
{
	m_isMouseOnButton = TheInputHandler::Instance()->isMouseOnObject(m_position, m_width, m_height);
}

void SellTowerButton::load(const std::shared_ptr<LoaderParams> pParams)
{
	SelectedTowerButton::load(pParams);
}

void SellTowerButton::setCallback(SellTowerCallback callback)
{
	m_callback = callback;
}

void SellTowerButton::handleOutsideCLick()
{
	if (!m_isMouseOnButton)
	{
		m_pressedOutside = TheInputHandler::Instance()->getMouseButtonState(LEFT);
	}
	else
	{
		// left mouseButton released inside towerButton
		if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_pressedOutside = false;
		}
	}
}

void SellTowerButton::handleClickOnButton()
{
	if (m_isMouseOnButton && !m_pressedOutside)
	{
		m_currentFrame = MOUSE_OVER;

		if (!TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_pressed)
		{
			m_currentFrame = CLICKED;

			m_callback(m_selectedTower);

			m_selected = true;

			m_pressed = false;
		}
		else if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_pressed = true;
		}
	}
	else
	{
		m_pressed = false;

		m_currentFrame = MOUSE_OUT;
	}
}

std::unique_ptr<GameObject> SellTowerButtonCreator::create() const
{
	return std::make_unique<SellTowerButton>();
}
