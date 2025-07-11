#include "../../include/EntitiesHeaders/TowerUpgradedButton.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/ManagersHeaders/PurchaseManager.h"

#include "../../include/UtilsHeaders/InputHandler.h"

TowerUpgradedButton::TowerUpgradedButton() : SelectedTowerButton(), m_selected(false), m_pressed(false), m_upgradeID(-1)
{
}

void TowerUpgradedButton::handleEvent()
{
	handleOutsideCLick();

	handleClickOnButton();
}

void TowerUpgradedButton::update()
{
	m_isMouseOnButton = TheInputHandler::Instance()->isMouseOnObject(m_position, m_width, m_height);
}

void TowerUpgradedButton::load(const std::shared_ptr<LoaderParams> pParams)
{
	SelectedTowerButton::load(pParams);

	m_upgradeID = pParams->getAttribute<int>(LoaderParamsConsts::upgradeID);
}

void TowerUpgradedButton::setCallback(TowerUpgradedCallback callback)
{
	m_callback = callback;
}

bool TowerUpgradedButton::isMouseOnButton()
{
	return m_isMouseOnButton;
}

int TowerUpgradedButton::getUpgradeID()
{
	return m_upgradeID;
}

void TowerUpgradedButton::handleOutsideCLick()
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

void TowerUpgradedButton::handleClickOnButton()
{
	if (m_isMouseOnButton && !m_pressedOutside)
	{
		m_currentFrame = MOUSE_OVER;

		if (!TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_pressed)
		{
			m_currentFrame = CLICKED;

			// invoke callback only if there are enough resources to buy the upgrade.
			if (PurchaseManager::Instance()->canPurchaseUpgrade(m_selectedTower->getTowerUpgradesData()[m_upgradeID], m_selectedTower->getColor()))
			{
				m_callback(m_selectedTower, m_upgradeID);

				m_selected = true;
			}

			// change m_pressed to false here, so it calls canPurchaseUpgrade() only once when mouse is on button
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

void TowerUpgradedButton::resetParams()
{
	m_selected = false;
	m_pressed = false;
	m_pressedOutside = false;
}

std::unique_ptr<GameObject> TowerUpgradedButtonCreator::create() const
{
	return std::make_unique<TowerUpgradedButton>();
}
