#include "../../../include/UIHeaders/CommonHeaders/InteractivePanel.h"

#include "../../../include/EntitiesHeaders/MenuButton.h"

#pragma region InteractivePanel function definition
InteractivePanel::InteractivePanel()
{
}

void InteractivePanel::draw()
{
	// draw buttons
	for (std::vector<std::shared_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		m_buttonObjects[i]->draw();
	}
}

void InteractivePanel::update()
{
	// update buttons
	for (std::vector<std::shared_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		m_buttonObjects[i]->update();
	}
}

void InteractivePanel::clean()
{
	// clean background texture
	m_backgroundTexture->clean();

	// clean objects texture
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	// clean labels
	for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
	{
		it->second->clean();
	}
}

void InteractivePanel::handleEvents()
{
	// handle buttons
	for (std::vector<std::shared_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		m_buttonObjects[i]->handleEvent();
	}
}

void InteractivePanel::setButtonObjects(std::vector<std::shared_ptr<Button>> buttons)
{
	m_buttonObjects = std::move(buttons);
}

void InteractivePanel::loadCallbacks()
{
}

#pragma endregion


#pragma region MenuInteractivePanel function definition

void MenuInteractivePanel::setCallbacks()
{
	for (std::vector<std::shared_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		if (MenuButton* pButton = dynamic_cast<MenuButton*>(m_buttonObjects[i].get()))
		{
			pButton->setCallback(m_callbacks.at(pButton->getCallbackID()));
			pButton = nullptr;
		}
	}
}

#pragma endregion


#pragma region TowerInteractivePanel function definition

TowerInteractivePanel::TowerInteractivePanel() : InteractivePanel()
{
}

void TowerInteractivePanel::setPlayStateTowers(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> playStateTowers)
{
	m_playStateTowers = playStateTowers;
}

#pragma endregion