#include "../../../include/UIHeaders/CommonHeaders/InteractivePanel.h"

InteractivePanel::InteractivePanel()
{
}

void InteractivePanel::draw()
{
	// draw buttons
	for (std::vector<std::unique_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		m_buttonObjects[i]->draw();
	}
}

void InteractivePanel::update()
{
}

void InteractivePanel::handleEvents()
{
	for (std::vector<std::unique_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		m_buttonObjects[i]->handleEvent();
	}
}

void InteractivePanel::setButtonObjects(std::vector<std::unique_ptr<Button>> buttons)
{
	m_buttonObjects = std::move(buttons);
}

void InteractivePanel::loadCallbacks()
{
}




#pragma region TowerInteractivePanel function definition

TowerInteractivePanel::TowerInteractivePanel() : InteractivePanel()
{
}

void TowerInteractivePanel::setPlayStateTowers(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> playStateTowers)
{
	m_playStateTowers = playStateTowers;
}

#pragma endregion