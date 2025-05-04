#include "../../include/EntitiesHeaders/TowerUpgradedButton.h"

TowerUpgradedButton::TowerUpgradedButton() : Button()
{
}

void TowerUpgradedButton::setCallback(TowerUpgradedCallback callback)
{
	m_callback = callback;
}
