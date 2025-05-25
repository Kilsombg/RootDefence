#include "../../../include/UIHeaders/MainMenuUIHeaders/MapsPanel.h"

#include "../../../include/Constants/LoaderParamsConsts.h"

#include "../../../include/EntitiesHeaders/MenuButton.h"
#include "../../../include/EntitiesHeaders/MapMenuButton.h"

#include "../../../include/GameStateHeaders/PlayState.h"

#include "../../../include/UIHeaders/MainMenuUIHeaders/MainMenuPanel.h"

#include "../../../include/UtilsHeaders/GameStateMachine.h"
#include "../../../include/UtilsHeaders/InputHandler.h"

#include<functional>

bool MapsPanel::s_active = false;

MapsPanel::MapsPanel()
{
}

void MapsPanel::draw()
{
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
}

void MapsPanel::update()
{
	if (s_active)
	{
		// update buttons
		MenuInteractivePanel::update();
	}
}

void MapsPanel::clean()
{
	// clean panel
	MenuInteractivePanel::clean();
}

void MapsPanel::handleEvents()
{
	if (s_active)
	{
		// handle buttons
		MenuInteractivePanel::handleEvents();

		// handle click outside of panel
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && 
			!TheInputHandler::Instance()->isMouseOnObject(m_backgroundTexture->getPosition(),
				m_backgroundTexture->getWidth(), m_backgroundTexture->getHeight()))
		{
			s_closePanel();
		}
	}
}

void MapsPanel::load(std::vector<std::unique_ptr<GameObject>> gameObjects)
{
	// load relevant objects
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < gameObjects.size(); i++)
	{
		// load map menu buttons
		if (std::unique_ptr<MapMenuButton> pButton = std::unique_ptr<MapMenuButton>(dynamic_cast<MapMenuButton*>(gameObjects[i].get())))
		{
			m_buttonObjects.push_back(std::make_shared<MapMenuButton>(std::move(pButton.get())));
			gameObjects[i].release();
		}
		// load menu buttons
		else if (std::unique_ptr<MenuButton> pButton = std::unique_ptr<MenuButton>(dynamic_cast<MenuButton*>(gameObjects[i].get())))
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
	}

	// load callbacks
	loadCallbacks();
}

void MapsPanel::loadCallbacks()
{
	// load map menu buttons' callbacks
	m_mapMenuButtonCallbacs[LoaderParamsConsts::mapMenuButtonCallbackID] = std::bind(&MapsPanel::mainMenuToPlay, this, std::placeholders::_1);

	// load menu buttons' callbacks
	m_callbacks[LoaderParamsConsts::closeMapsPanelCallbackID] = s_closePanel;

	setCallbacks();
}

void MapsPanel::s_activatePanel()
{
	s_active = true;
	MainMenuPanel::s_setActivePanel(false);
}

void MapsPanel::s_closePanel()
{
	s_active = false;
	MainMenuPanel::s_setActivePanel(true);
}

void MapsPanel::setCallbacks()
{
	for (std::vector<std::shared_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		// set map buttons
		if (MapMenuButton* pButton = dynamic_cast<MapMenuButton*>(m_buttonObjects[i].get()))
		{
			pButton->setCallback(m_mapMenuButtonCallbacs.at(pButton->getCallbackID()));
			pButton = nullptr;
		}
		// set menu buttons
		else if (MenuButton* pButton = dynamic_cast<MenuButton*>(m_buttonObjects[i].get()))
		{
			pButton->setCallback(m_callbacks.at(pButton->getCallbackID()));
			pButton = nullptr;
		}
	}
}

void MapsPanel::mainMenuToPlay(std::string mapFileName)
{
	// close panel
	s_active = false;

	// set map to playstate
	std::string pathToFile = "./src/assets/Map/" + mapFileName;
	PlayState::setMapLevelPath(pathToFile);

	TheGameStateMachine::Instance()->changeState(std::make_shared<PlayState>());
}

std::unique_ptr<Panel> MapsPanelCreator::create() const
{
	return std::make_unique<MapsPanel>();
}
