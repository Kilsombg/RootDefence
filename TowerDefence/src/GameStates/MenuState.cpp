#include "../../include/GameStateHeaders/MenuState.h"

#include "../../include/EntitiesHeaders/MenuButton.h"

void MenuState::setCallbacks(const std::map<std::string, Callback>& callbacks)
{
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		if (dynamic_cast<MenuButton*>(m_gameObjects[i].get()))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i].get());
			pButton->setCallback(callbacks.at(pButton->getCallbackID()));
			pButton = nullptr;
		}
	}
}

void MenuState::handleEvents()
{
	// handle buttons event
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		if (Button* towerButton = dynamic_cast<Button*>(m_gameObjects[i].get()))
		{
			towerButton->handleEvent();
			towerButton = nullptr;
		}
	}
}

bool MenuState::drawUnderneath()
{
	return false;
}
