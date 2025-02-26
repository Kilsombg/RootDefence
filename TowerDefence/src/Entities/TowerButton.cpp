#include "../../include/EntitiesHeaders/TowerButton.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/UtilsHeaders/InputHandler.h"


TowerButton::TowerButton() : Button(), m_selected(false)
{
}

void TowerButton::load(const std::shared_ptr<LoaderParams> pParams)
{
	m_towerName = pParams->getAttribute<std::string>(LoaderParamsConsts::towerName);
	Button::load(pParams);
}

void TowerButton::update()
{
	handleEvent();
}

void TowerButton::setCallback(std::function<void(Button*)> callback)
{
	m_callback = callback;
}

std::string TowerButton::getTowerName()
{
	return m_towerName;
}

void TowerButton::handleEvent()
{
	// TO-DO
	// - handle a way to stop the event
	// - check if pos is in UI or on another object
	std::shared_ptr<Vector2D> pMousePos = TheInputHandler::Instance()->getMousePosition();

	if (pMousePos->getX() < (m_position.getX() + m_width)
		&& pMousePos->getX() > m_position.getX()
		&& pMousePos->getY() < (m_position.getY() + m_height)
		&& pMousePos->getY() > m_position.getY())
	{
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			//m_currentFrame = CLICKED;

			m_callback(this);

			m_bReleased = false;

			m_selected = true;
		}
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_bReleased = true;

			//m_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		// handle second click
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_selected && m_bReleased)
		{
			m_callback(this);

			m_selected = false;
		} 
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_bReleased = true;
		}
		//m_currentFrame = MOUSE_OUT;
	}
}

std::unique_ptr<GameObject> TowerButtonCreator::createGameObject() const
{
	return std::make_unique<TowerButton>();
}
