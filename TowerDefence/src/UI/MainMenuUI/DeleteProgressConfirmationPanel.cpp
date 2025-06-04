#include "../../../include/UIHeaders/MainMenuUIHeaders/DeleteProgressConfirmationPanel.h"

#include "../../../include/Constants/LoaderParamsConsts.h"

#include "../../../include/EntitiesHeaders/MenuButton.h"

#include "../../../include/UtilsHeaders/InputHandler.h"

#include "../../../include/Game.h"

bool DeleteProgressConfirmationPanel::s_active = false;

DeleteProgressConfirmationPanel::DeleteProgressConfirmationPanel() : MenuInteractivePanel()
{
}

void DeleteProgressConfirmationPanel::draw()
{
	if (s_active)
	{
		// draw textures
		for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
		{
			m_gameObjects[i]->draw();
		}

		// draw background
		//m_backgroundTexture->draw();

		// draw buttons
		MenuInteractivePanel::draw();

		// draw labels
		for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
		{
			it->second->draw();
		}
	}
}

void DeleteProgressConfirmationPanel::update()
{
	if (s_active)
	{
		// update buttons
		MenuInteractivePanel::update();
	}
}

void DeleteProgressConfirmationPanel::clean()
{
	// return static variables to default values
	s_active = false;

	// clean panel
	MenuInteractivePanel::clean();
}

void DeleteProgressConfirmationPanel::handleEvents()
{
	if (s_active)
	{
		// handle buttons
		MenuInteractivePanel::handleEvents();

		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) &&
			!TheInputHandler::Instance()->isMouseOnObject(m_backgroundTexture->getPosition(), m_backgroundTexture->getWidth(), m_backgroundTexture->getHeight()))
		{
			s_active = false;
		}
	}
}

void DeleteProgressConfirmationPanel::load(std::vector<std::unique_ptr<GameObject>> gameObjects)
{
	// load relevant objects
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < gameObjects.size(); i++)
	{
		// load buttons
		if (std::unique_ptr<MenuButton> pButton = std::unique_ptr<MenuButton>(dynamic_cast<MenuButton*>(gameObjects[i].get())))
		{
			m_buttonObjects.push_back(std::make_shared<MenuButton>(std::move(pButton.get())));
			gameObjects[i].release();
		}
		// load labels
		else if (std::unique_ptr<Text> pText = std::unique_ptr<Text>(dynamic_cast<Text*>(gameObjects[i].get())))
		{
			m_labelsMap[pText->getLabelID()] = std::move(pText);
			gameObjects[i].release();
		}
		else
		{
			// load textures
			m_gameObjects.push_back(std::move(gameObjects[i]));
		}
	}

	// load callbacks
	loadCallbacks();
}

void DeleteProgressConfirmationPanel::loadCallbacks()
{
	// load callbacks
	m_callbacks[LoaderParamsConsts::deleteProgressCallbackID] = s_deleteProgress;

	// set callbacks to buttons
	setCallbacks();
}

void DeleteProgressConfirmationPanel::s_setActivePanel(bool activeFlag)
{
	s_active = activeFlag;
}

void DeleteProgressConfirmationPanel::s_activatePanel()
{
	s_active = true;
}

void DeleteProgressConfirmationPanel::s_deleteProgress()
{
	TheGame::Instance()->getProgressManager()->deleteProgress();

	s_active = false;
}


std::unique_ptr<Panel> DeleteProgressConfirmationPanelCreator::create() const
{
	return std::make_unique<DeleteProgressConfirmationPanel>();
}
