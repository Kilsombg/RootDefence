#include "../../include/EntitiesHeaders/TowerButton.h"

#include "../../include/Game.h"

#include "../../include/Constants/UIConsts.h"
#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/ManagersHeaders/PurchaseManager.h"
#include "../../include/ManagersHeaders/CollisionManager.h"

#include "../../include/UtilsHeaders/InputHandler.h"
#include "../../include/UtilsHeaders/TowerFactory.h"

#include<regex>

TowerButton::TowerButton() : Button(), m_selected(false), m_pressed(false), m_isMouseOnFreeTowerTile(false), m_disabled(false)
{
}

TowerButton::TowerButton(const TowerButton* towerButton) : Button(towerButton)
{
	m_towerName = towerButton->m_towerName;
	m_towerColor = towerButton->m_towerColor;
	m_baseTextureID = towerButton->m_baseTextureID;
	m_towerNameID = towerButton->m_towerNameID;

	m_selected = towerButton->m_selected;
	m_pressed = towerButton->m_pressed;
	m_isMouseOnFreeTowerTile = towerButton->m_isMouseOnFreeTowerTile;
	m_isMouseOutsideMap = towerButton->m_isMouseOutsideMap;
	m_disabled = towerButton->m_disabled;
	
	m_callback = towerButton->m_callback;
	m_towerParams = towerButton->m_towerParams;
	m_dummyObject = towerButton->m_dummyObject;
}

void TowerButton::load(const std::shared_ptr<LoaderParams> pParams)
{
	m_towerName = pParams->getAttribute<std::string>(LoaderParamsConsts::towerName);
	m_towerColor = pParams->getAttribute<std::string>(LoaderParamsConsts::towerColor);
	m_baseTextureID = pParams->getAttribute<std::string>(LoaderParamsConsts::textureID);
	m_towerNameID = std::regex_replace(m_baseTextureID, std::regex(LoaderParamsConsts::towerButtonSuffix), LoaderParamsConsts::towerNameIDSuffix);

	m_towerParams = TheTowerFactory::Instance()->getTowerData(m_towerName);
	m_towerParams->setAttribute(LoaderParamsConsts::x, 0.0f);
	m_towerParams->setAttribute(LoaderParamsConsts::y, 0.0f);

	m_dummyObject = std::make_shared<SDLGameObject>();
	m_dummyObject->load(m_towerParams);

	Button::load(pParams);
}

void TowerButton::update()
{
	// check if mouse is on button
	m_isMouseOnButton = TheInputHandler::Instance()->isMouseOnObject(m_position, m_width, m_height);

	// update texture
	m_disabled = !ThePurchaseManager::Instance()->canPurchaseTower(m_towerName, m_towerColor) || 
		!TheGame::Instance()->getTowerUnlockManager()->isUnlocked(m_towerNameID);
	m_textureID = m_disabled ? m_baseTextureID + UIConsts::disabledSuffix : m_baseTextureID;

	if (m_selected)
	{
		// update dummy position
		setDummyObjectPosition();

		// check if there is free space to place tower
		m_isMouseOnFreeTowerTile = !TheCollisionManager::Instance()->collideTowerPlacement(m_dummyObject.get(), pLevel);

		// check if mouse is outside of map
		std::shared_ptr<Vector2D> mousePos = InputHandler::Instance()->getMousePosition();
		m_isMouseOutsideMap = (mousePos->getX() > pLevel->getWidth()) || (mousePos->getY() > pLevel->getHeight());
	}
}

void TowerButton::setDummyObjectPosition()
{
	Vector2D mousePos = *InputHandler::Instance()->getMousePosition().get();
	mousePos.setX(mousePos.getX() - m_dummyObject->getWidth() / 2);
	mousePos.setY(mousePos.getY() - m_dummyObject->getHeight() / 2);
	m_dummyObject->setPosition(mousePos);
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

bool TowerButton::isSelected()
{
	return m_selected;
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
		if (TheInputHandler::Instance()->isKeyPressed(SDL_SCANCODE_ESCAPE) || TheInputHandler::Instance()->getMouseButtonState(RIGHT))
		{
			m_callback(nullptr);
			resetParams();
		}
		// interrupt when button is selected and clicked outside map and button.
		if (!m_isMouseOnButton && m_isMouseOutsideMap && TheInputHandler::Instance()->getMouseButtonState(LEFT))
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
			if (!m_disabled)
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
