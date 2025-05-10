#include "../../include/EntitiesHeaders/TowerButton.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/ManagersHeaders/PurchaseManager.h"

#include "../../include/MapHeaders/TileType.h"

#include "../../include/UtilsHeaders/InputHandler.h"


TowerButton::TowerButton() : Button(), m_selected(false), m_pressed(false), m_isMouseOnFreeTowerTile(false)
{
}

void TowerButton::load(const std::shared_ptr<LoaderParams> pParams)
{
	m_towerName = pParams->getAttribute<std::string>(LoaderParamsConsts::towerName);
	m_towerColor = pParams->getAttribute<std::string>(LoaderParamsConsts::towerColor);
	Button::load(pParams);
}

void TowerButton::update()
{
	m_isMouseOnButton = TheInputHandler::Instance()->isMouseOnObject(m_position, m_width, m_height);

	std::shared_ptr<Vector2D> pMousePos = TheInputHandler::Instance()->getMousePosition();
	if (pLevel != nullptr && m_selected)
	{
		m_isMouseOnFreeTowerTile = TileType::TOWER == pLevel->getTileTypeByPosition(pMousePos->getX(), pMousePos->getY());
	}
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

std::string TowerButton::getTowerColor()
{
	return m_towerColor;
}

void TowerButton::setLevel(std::shared_ptr<Level> level)
{
	pLevel = level;
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

			// invoke callback only if there are enough resources to buy the tower.
			if (ThePurchaseManager::Instance()->canPurchaseTower(m_towerName, m_towerColor))
			{
				m_callback(this);

				m_selected = true;
			}
			// change m_pressed to false here, so it calls canPurchaseTower() only once when mouse is on button
			m_pressed = false;
		}
		else if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_pressed = true;

			//m_currentFrame = MOUSE_OVER;
		}
	}
	else if (m_selected && m_isMouseOnFreeTowerTile)
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

std::unique_ptr<GameObject> TowerButtonCreator::create() const
{
	return std::make_unique<TowerButton>();
}
