#include "../../include/EntitiesHeaders/TowerUpgradedButton.h"

#include "../../include/UtilsHeaders/InputHandler.h"

TowerUpgradedButton::TowerUpgradedButton() : Button()
{
}

void TowerUpgradedButton::handleEvent()
{
	handleClickOnButton();
}

void TowerUpgradedButton::setCallback(TowerUpgradedCallback callback)
{
	m_callback = callback;
}

void TowerUpgradedButton::handleClickOnButton()
{
	if (m_isMouseOnButton && !m_pressedOutside)
	{
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			m_currentFrame = CLICKED;

			m_callback(*m_selectedTower);

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

std::unique_ptr<GameObject> TowerUpgradedButtonCreator::createGameObject() const
{
	return std::make_unique<TowerUpgradedButton>();
}
