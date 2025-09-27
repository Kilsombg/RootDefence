#include "../../../include/UIHeaders/MainMenuUIHeaders/MapDifficultyPanel.h"

#include "../../../include/UIHeaders/MainMenuUIHeaders/MapsPanel.h"

#include "../../../include/Constants/LoaderParamsConsts.h"

#include "../../../include/GameStateHeaders/PlayState.h"

#include "../../../include/EntitiesHeaders/MenuButton.h"

#include "../../../include/UtilsHeaders/InputHandler.h"
#include "../../../include/UtilsHeaders/GameStateMachine.h"

#include<functional>

bool MapDifficultyPanel::s_active = false;
MapDetail MapDifficultyPanel::s_mapDetail = MapDetail();

MapDifficultyPanel::MapDifficultyPanel()
{
}

void MapDifficultyPanel::draw()
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

void MapDifficultyPanel::update()
{
	if (s_active)
	{
		// update buttons
		MenuInteractivePanel::update();
	}
}

void MapDifficultyPanel::clean()
{
	s_active = false;
	s_mapDetail = MapDetail();

	// clean panel
	MenuInteractivePanel::clean();
}

void MapDifficultyPanel::handleEvents()
{
	if (s_active)
	{
		// handle buttons
		MenuInteractivePanel::handleEvents();
	}
}

void MapDifficultyPanel::load(std::vector<std::unique_ptr<GameObject>> gameObjects)
{
	// load relevant objects
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < gameObjects.size(); i++)
	{
		// load difficulty buttons
		if (std::unique_ptr<DifficultyButton> pButton = std::unique_ptr<DifficultyButton>(dynamic_cast<DifficultyButton*>(gameObjects[i].get())))
		{
			m_buttonObjects.push_back(std::make_shared<DifficultyButton>(std::move(pButton.get())));
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

void MapDifficultyPanel::loadCallbacks()
{
	m_callbacks[LoaderParamsConsts::backToMapsPanelCallbackID] = s_closePanel;

	m_mapMenuButtonCallbacs[LoaderParamsConsts::difficultyButtonCallbackID] = std::bind(&MapDifficultyPanel::mainMenuToPlay, this, std::placeholders::_1);

	setCallbacks();
}

void MapDifficultyPanel::s_activatePanel()
{
	s_active = true;
}

void MapDifficultyPanel::s_setMapDetail(MapDetail mapDetail)
{
	s_mapDetail = mapDetail;
}

void MapDifficultyPanel::s_closePanel()
{
	s_active = false;

	// open MapsPanel when closing.
	MapsPanel::s_setActivePanel(true);
}

void MapDifficultyPanel::mainMenuToPlay(Difficulty difficulty)
{
	//TO-DO
	// set map's difficulty

	// set map to playstate
	s_mapDetail.mapLevelPath = "./src/assets/Map/" + s_mapDetail.mapLevelPath;
	PlayState::s_setCurrentMap(s_mapDetail);

	TheGameStateMachine::Instance()->changeState(std::make_shared<PlayState>());
}

void MapDifficultyPanel::setCallbacks()
{
	for (std::vector<std::shared_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		// set difficulty buttons
		if (DifficultyButton* pButton = dynamic_cast<DifficultyButton*>(m_buttonObjects[i].get()))
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

std::unique_ptr<Panel> MapDifficultyPanelCreator::create() const
{
	return std::make_unique<MapDifficultyPanel>();
}
