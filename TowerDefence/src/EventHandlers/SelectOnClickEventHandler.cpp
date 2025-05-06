#include "../../include/EventHandlersHeaders/SelectOnClickEventHandler.h"

#include "../../include/UtilsHeaders/InputHandler.h"

SelectOnClickEventHandler::SelectOnClickEventHandler(Vector2D pos, int width, int height, CloseArea closeArea, bool keyInterruptible) : 
	m_objPos(pos), m_objWidth(width), m_objHeight(height), m_closeArea(closeArea), m_keyInterruptible(keyInterruptible), m_selected(true), m_pressed(false), m_pressedOutside(false), m_isMouseOnObject(false) {}

SelectOnClickEventHandler::SelectOnClickEventHandler()
{
}

void SelectOnClickEventHandler::update()
{
	m_isMouseOnObject = TheInputHandler::Instance()->isMouseOnObject(m_objPos, m_objWidth, m_objHeight);
}

void SelectOnClickEventHandler::handleEvent()
{
	handleInterruptEvent();

	handleOutsideCLick();

	handleClickOnButton();
}

bool SelectOnClickEventHandler::isSelected()
{
	return m_selected;
}

void SelectOnClickEventHandler::resetParams()
{
	m_selected = false;
	m_pressed = false;
	m_pressedOutside = false;
}

void SelectOnClickEventHandler::handleInterruptEvent()
{
	// if key interuptible not enabled then return
	if (!m_keyInterruptible) return;

	if (m_selected)
	{
		if (InputHandler::Instance()->isKeyPressed(SDL_SCANCODE_ESCAPE))
		{
			resetParams();
		}
	}
}

void SelectOnClickEventHandler::handleOutsideCLick()
{
	if (!m_isMouseOnObject)
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

void SelectOnClickEventHandler::handleClickOnButton()
{
	if (m_isMouseOnObject && !m_pressedOutside && !m_selected)
	{
		if (!TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_pressed)
		{
			//m_currentFrame = CLICKED;

			m_pressed = false;

			m_selected = true;
		}
		else if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_pressed = true;

			//m_currentFrame = MOUSE_OVER;
		}
	}
	else if (m_selected && isMouseInsideArea())
	{
		// handle second click
		if (!TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_pressed)
		{
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

bool SelectOnClickEventHandler::isMouseInsideArea()
{
	// not given area
	if (m_closeArea.m_areaWidth == 0) return true;

	Vector2D areaV = Vector2D(m_closeArea.m_areaX, m_closeArea.m_areaY);
	return TheInputHandler::Instance()->isMouseOnObject(areaV, m_closeArea.m_areaWidth, m_closeArea.m_areaHeight);
}
