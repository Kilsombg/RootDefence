#include "../../../include/UIHeaders/MainMenuUIHeaders/MainMenuPanel.h"

#include "../../../include/Game.h"

#include "../../../include/Constants/LoaderParamsConsts.h"
#include "../../../include/Constants/UIConsts.h"

#include "../../../include/EntitiesHeaders/MenuButton.h"

#include "../../../include/UIHeaders/MainMenuUIHeaders/MapsPanel.h"
#include "../../../include/UIHeaders/MainMenuUIHeaders/DeleteProgressConfirmationPanel.h"

bool MainMenuPanel::s_active = true;

MainMenuPanel::MainMenuPanel() : MenuInteractivePanel()
{
}

void MainMenuPanel::draw()
{
	// draw textures - main background, game Title and coinsPanel
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}

	// draw level progress bar
	TheGame::Instance()->getLevelManager()->drawLevelProgressBar();

	if (s_active)
	{
		// draw background
		m_backgroundTexture->draw();


		// draw buttons
		MenuInteractivePanel::draw();

		// draw labels
		for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
		{
			it->second->draw();
		}
	}
	else
	{
		// draw labels even not active
		m_labelsMap[UIConsts::coinsLabelID]->draw();
		m_labelsMap[UIConsts::levelLabelID]->draw();
	}
}

void MainMenuPanel::update()
{
	if (s_active)
	{
		// update buttons
		MenuInteractivePanel::update();

		// update dynamic labels
		updateDynamicLabels();
	}
}

void MainMenuPanel::clean()
{
	// return static variables to default values
	s_active = true;

	// clean panel
	MenuInteractivePanel::clean();
}

void MainMenuPanel::handleEvents()
{
	if (s_active)
	{
		// handle buttons
		MenuInteractivePanel::handleEvents();
	}
}

void MainMenuPanel::load(std::vector<std::unique_ptr<GameObject>> gameObjects)
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
			m_gameObjects.push_back(std::move(gameObjects[i]));
		}
	}

	// load static labels
	//loadStaticLabels();

	// load callbacks
	loadCallbacks();
}

void MainMenuPanel::loadCallbacks()
{
	m_callbacks[LoaderParamsConsts::playbuttonCallbackID] = MapsPanel::s_activatePanel;
	m_callbacks[LoaderParamsConsts::exitbuttonCallbackID] = s_exitFromMenu;
	m_callbacks[LoaderParamsConsts::openDeleteConfPanelCallbackID] = DeleteProgressConfirmationPanel::s_activatePanel;

	setCallbacks();
}

void MainMenuPanel::s_setActivePanel(bool activeFlag)
{
	s_active = activeFlag;
}

void MainMenuPanel::s_exitFromMenu()
{
	TheGame::Instance()->quit();
}

void MainMenuPanel::loadStaticLabels()
{

	// update text on screen
	for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
	{
		if (!it->second->getDynamic())
		{
			it->second->update();
		}
	}
}

void MainMenuPanel::updateDynamicLabels()
{
	m_labelsMap[UIConsts::coinsLabelID]->setMessage(std::to_string(TheGame::Instance()->getProgressManager()->getGameProgress()->coins));

	// level label
	m_labelsMap[UIConsts::levelLabelID]->setMessage(std::to_string(TheGame::Instance()->getProgressManager()->getGameProgress()->level));
	m_labelsMap[UIConsts::levelLabelID]->centerText();

	// update text on screen
	for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
	{
		if (it->second->getDynamic())
		{
			it->second->update();
		}
	}
}

std::unique_ptr<Panel> MainMenuPanelCreator::create() const
{
	return std::make_unique<MainMenuPanel>();
}
