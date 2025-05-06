#include "../../../include/UIHeaders/PlayStateUIHeaders/TowerUpgradePanel.h"

#include "../../../include/Constants/LoaderParamsConsts.h"

#include "../../../include/EntitiesHeaders/TowerUpgradedButton.h"

#include "../../../include/EventHandlersHeaders/TowerUpgradeHandlers.h"

#include<functional>

TowerUpgradePanel::TowerUpgradePanel() : TowerInteractivePanel()
{
}

void TowerUpgradePanel::draw()
{
	if (isSelected())
	{
		// draw buttons
		InteractivePanel::draw();
	}
}

void TowerUpgradePanel::update()
{
	// update buttons
	if (isSelected())
	{
		for (std::vector<std::unique_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
		{
			m_buttonObjects[i]->update();

			// set selected tower into upgrade buttons
			if (TowerUpgradedButton* towerUpgradedButton = dynamic_cast<TowerUpgradedButton*>(m_buttonObjects[i].get()))
			{
				towerUpgradedButton->setSelectedTower(m_selectedTower);
				towerUpgradedButton = nullptr;
			}
		}
	}

	// set selected tower to TowerUpgradePanel
	updateSelectedTower();
}

void TowerUpgradePanel::loadCallbacks()
{
	// load tower upgrade buttons callbacks
	TowerUpgradeHandlers towerUpgradeHandlers;
	m_towerUpgradedButtonCallbacks[LoaderParamsConsts::towerUpgradeOneCallbackID] = std::bind(&TowerUpgradeHandlers::handleUpgradeOneEvent, towerUpgradeHandlers, std::placeholders::_1);
	m_towerUpgradedButtonCallbacks[LoaderParamsConsts::towerUpgradeTwoCallbackID] = std::bind(&TowerUpgradeHandlers::handleUpgradeTwoEvent, towerUpgradeHandlers, std::placeholders::_1);
	m_towerUpgradedButtonCallbacks[LoaderParamsConsts::towerUpgradeThreeCallbackID] = std::bind(&TowerUpgradeHandlers::handleUpgradeThreeEvent, towerUpgradeHandlers, std::placeholders::_1);
	setTowerUpgradedButtonCallbacks();
}

void TowerUpgradePanel::setSelectedTower(std::shared_ptr<Tower> selectedTower)
{
	m_selectedTower = selectedTower;
}

bool TowerUpgradePanel::isSelected()
{
	if (m_selectedTower.get())
	{
		return m_selectedTower->isSelected();
	}
	return false;
}

void TowerUpgradePanel::updateSelectedTower()
{
	for (std::vector<std::shared_ptr<Tower>>::size_type i = 0; i < m_playStateTowers->size(); i++)
	{
		if ((*m_playStateTowers)[i]->isSelected())
		{
			m_selectedTower = (*m_playStateTowers)[i];
			return;
		}
	}
	m_selectedTower.reset();
}

void TowerUpgradePanel::setTowerUpgradedButtonCallbacks()
{
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		if (TowerUpgradedButton* pButton = dynamic_cast<TowerUpgradedButton*>(m_buttonObjects[i].get()))
		{
			pButton->setCallback(m_towerUpgradedButtonCallbacks.at(pButton->getCallbackID()));
			pButton = nullptr;
		}
	}
}
