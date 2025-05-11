#include "../../include/EntitiesHeaders/SelectedTowerButton.h"

SelectedTowerButton::SelectedTowerButton() : Button()
{
}

void SelectedTowerButton::load(const std::shared_ptr<LoaderParams> pParams)
{
	Button::load(pParams);
}

void SelectedTowerButton::setSelectedTower(std::shared_ptr<Tower> selectedTower)
{
	m_selectedTower = selectedTower;
}
