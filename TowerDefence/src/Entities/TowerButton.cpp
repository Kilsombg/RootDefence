#include "../../include/EntitiesHeaders/TowerButton.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/UtilsHeaders/InputHandler.h"


TowerButton::TowerButton() : Button(), m_selected(false), m_pressed(false)
{
}

void TowerButton::load(const std::shared_ptr<LoaderParams> pParams)
{
	m_towerName = pParams->getAttribute<std::string>(LoaderParamsConsts::towerName);
	Button::load(pParams);
}

void TowerButton::update()
{
	std::shared_ptr<Vector2D> pMousePos = TheInputHandler::Instance()->getMousePosition();
	m_isMouseOnButton = pMousePos->getX() < (m_position.getX() + m_width)
		&& pMousePos->getX() > m_position.getX()
		&& pMousePos->getY() < (m_position.getY() + m_height)
		&& pMousePos->getY() > m_position.getY();
}

void TowerButton::handleEvent()
{
	// TO-DO
	// - check if pos is in UI or on another object

	handleInterruptEvent();

	handleOutsideCLick();

	handleClickOnButton();
}

void TowerButton::setCallback(TowerButtonCallback callback)
{
	m_callback = callback;
}

std::string TowerButton::getTowerName()
{
	return m_towerName;
}

void TowerButton::resetParams()
{
	m_selected = false;
	m_pressed = false;
	m_pressedOutside = false;
}

void TowerButton::handleInterruptEvent()
{
	if (m_selected)
	{
		if (InputHandler::Instance()->isKeyPressed(SDL_SCANCODE_ESCAPE))
		{
			m_callback(nullptr);
			resetParams();
		}
	}
}

void TowerButton::handleOutsideCLick()
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

void TowerButton::handleClickOnButton()
{
	if (m_isMouseOnButton && !m_pressedOutside && !m_selected)
	{
		if (!TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_pressed)
		{
			//m_currentFrame = CLICKED;

			m_callback(this);

			m_pressed = false;

			m_selected = true;
		}
		else if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_pressed = true;

			//m_currentFrame = MOUSE_OVER;
		}
	}
	else if (m_selected)
	{
		// handle second click
		if (!TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_pressed)
		{
			m_callback(this);

			m_pressed = false;

			m_selected = false;
		}
		else if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_pressed = true;
		}
		//m_currentFrame = MOUSE_OUT;
	}
	else
	{
		m_pressed = false;
	}
}

std::unique_ptr<GameObject> TowerButtonCreator::createGameObject() const
{
	return std::make_unique<TowerButton>();
}
