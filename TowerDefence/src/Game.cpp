#include "../include/Game.h"

#include "../include/Constants/GameObjectConsts.h"

#include "../include/DataHeaders/RepositoriesHeaders/GameProgressRepository.h"
#include "../include/DataHeaders/RepositoriesHeaders/MapsProgressRepository.h"
#include "../include/DataHeaders/RepositoriesHeaders/MapsRepository.h"

#include "../include/DataHeaders/UserProgressDBContext.h"

#include "../include/EntitiesHeaders/MenuButton.h"
#include "../include/EntitiesHeaders/MapMenuButton.h"
#include "../include/EntitiesHeaders/TowerButton.h"
#include "../include/EntitiesHeaders/TowerUpgradedButton.h"
#include "../include/EntitiesHeaders/SellTowerButton.h"
#include "../include/EntitiesHeaders/Enemy.h"
#include "../include/EntitiesHeaders/Tower.h"
#include "../include/EntitiesHeaders/FreezeTower.h"
#include "../include/EntitiesHeaders/Projectile.h"
#include "../include/EntitiesHeaders/AnimatedGraphic.h"
#include "../include/EntitiesHeaders/Text.h"
#include "../include/EntitiesHeaders/Texture.h"


#include "../include/GameStateHeaders/MainMenuState.h"
#include "../include/GameStateHeaders/PlayState.h"

#include "../include/UIHeaders/GameOverUIHeaders/GameOverStatePanel.h"

#include "../include/UIHeaders/VictoryStateUIHeaders/VictoryStatePanel.h"

#include "../include/UIHeaders/MainMenuUIHeaders/MainMenuPanel.h"
#include "../include/UIHeaders/MainMenuUIHeaders/MapsPanel.h"
#include "../include/UIHeaders/MainMenuUIHeaders/DeleteProgressConfirmationPanel.h"

#include "../include/UIHeaders/PauseStateUIHeaders/PauseStatePanel.h"

#include "../include/UIHeaders/PlayStateUIHeaders/TowersPanel.h"
#include "../include/UIHeaders/PlayStateUIHeaders/TowerUpgradePanel.h"
#include "../include/UIHeaders/PlayStateUIHeaders/TipsPanel.h"


#include "../include/UtilsHeaders/TrueTypeManager.h"
#include "../include/UtilsHeaders/InputHandler.h"
#include "../include/UtilsHeaders/GameObjectFactory.h"
#include "../include/UtilsHeaders/PanelFactory.h"
#include "../include/UtilsHeaders/TextureManager.h"

#include<iostream>

Game* Game::s_pInstance = nullptr;

Game::Game()
{
}

Game::~Game()
{
}

Game* Game::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = new Game();
		return s_pInstance;
	}
	return s_pInstance;
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
		//flags = SDL_WINDOW_RESIZABLE;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (m_pWindow != 0)
		{
			std::cout << "window creation success\n";

			// stretching window
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
			SDL_SetWindowMinimumSize(m_pWindow, width, height);

			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0)
			{
				std::cout << "renderer creation success\n";
				SDL_RenderSetLogicalSize(m_pRenderer, width, height);

				if (TTF_Init() == -1) {
					std::cout << "Could not initailize SDL2_ttf, error: " << TTF_GetError() << std::endl;
				}
				else {
					std::cout << "SDL2_ttf system ready to go!" << std::endl;
				}

				// Load font file and set the font size
				m_pFont = TTF_OpenFont("src/fonts/LuckiestGuy-Regular.ttf", 32);
				m_pFontOutline = TTF_OpenFont("src/fonts/LuckiestGuy-Regular.ttf", 32);
				TTF_SetFontOutline(m_pFontOutline, OUTLINE_SIZE);
				// Confirm that it was loaded
				if (m_pFont == nullptr) {
					std::cout << "Could not load font" << std::endl;
				}

				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

			}
			else
			{
				std::cout << "renderer init fail\n";
				return false;
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false;
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false;
	}

	m_bRunning = true;
	m_gameWidth = width;
	m_gameHeight = height;

	// register objects
	registerGameObjects();

	// register panels
	registerPanels();

	// create gameStateMachine
	m_pGameStateMachine = TheGameStateMachine::Instance();
	m_pGameStateMachine->changeState(std::make_shared<MainMenuState>());

	// configure progressManager
	configureProgressManager();
	m_progressManager->loadAll("src/database/gameProgress.sqlite");

	std::cout << "init success\n";
	return true;
}


void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	m_pGameStateMachine->render();

	SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
	m_pGameStateMachine->update();
}

void Game::clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);

	m_pGameStateMachine->clean();

	// save and close db connection
	m_progressManager->updateLevelToDB(1);
	m_progressManager->closeDB();

	TheTextureManager::Instance()->clean();

	TheTrueTypeManager::Instance()->clean();

	TTF_CloseFont(m_pFont);

	TheInputHandler::Instance()->clean();

	SDL_Quit();

	delete s_pInstance;
	s_pInstance = nullptr;
}

SDL_Renderer* Game::getRenderer() const
{
	return m_pRenderer;
}

SDL_Window* Game::getWindow() const
{
	return m_pWindow;
}

TTF_Font* Game::getFont() const
{
	return m_pFont;
}

TTF_Font* Game::getFontOutline() const
{
	return m_pFontOutline;
}

std::shared_ptr<GameStateMachine> Game::getStateMachine()
{
	return m_pGameStateMachine;
}

std::shared_ptr<ProgressManager> Game::getProgressManager()
{
	return m_progressManager;
}

int Game::getGameWidth() const
{
	return m_gameWidth;
}

int Game::getGameHeight() const
{
	return m_gameHeight;
}

bool Game::running()
{
	return m_bRunning;
}

void Game::registerGameObjects()
{
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::greenChoy, std::make_shared<EnemyCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::greenPlant, std::make_shared<EnemyCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::greenBroccoli, std::make_shared<EnemyCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::yellowOrange, std::make_shared<EnemyCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::yellowCarrot, std::make_shared<EnemyCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::yellowSquash, std::make_shared<EnemyCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::redRadish, std::make_shared<EnemyCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::redPepper, std::make_shared<EnemyCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::redTomato, std::make_shared<EnemyCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::blueBean, std::make_shared<EnemyCreator>());

	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::stump, std::make_shared<TowerCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::pine, std::make_shared<TowerCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::oak, std::make_shared<TowerCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::frozenBush, std::make_shared<FreezeTowerCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::projectile, std::make_shared<ProjectileCreator>());

	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::menuButton, std::make_shared<MenuButtonCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::mapMenuButton, std::make_shared<MapMenuButtonCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::towerButton, std::make_shared<TowerButtonCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::towerUpgradedButton, std::make_shared<TowerUpgradedButtonCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::sellTowerButton, std::make_shared<SellTowerButtonCreator>());

	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::animatedGraphic, std::make_shared<AnimatedGraphicCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::text, std::make_shared<TextCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::texture, std::make_shared<TextureCreator>());
}

void Game::registerPanels()
{
	ThePanelFactory::Instance()->registerType(PanelConsts::gameOverStatePanel, std::make_shared<GameOverStatePanelCreator>());

	ThePanelFactory::Instance()->registerType(PanelConsts::victoryStatePanel, std::make_shared<VictoryStatePanelCreator>());

	ThePanelFactory::Instance()->registerType(PanelConsts::mainMenuPanel, std::make_shared<MainMenuPanelCreator>());
	ThePanelFactory::Instance()->registerType(PanelConsts::mapsPanel, std::make_shared<MapsPanelCreator>());
	ThePanelFactory::Instance()->registerType(PanelConsts::deleteProgressConfirmationPanel, std::make_shared<DeleteProgressConfirmationPanelCreator>());

	ThePanelFactory::Instance()->registerType(PanelConsts::pauseStatePanel, std::make_shared<PauseStatePanelCreator>());

	ThePanelFactory::Instance()->registerType(PanelConsts::towersPanel, std::make_shared<TowersPanelCreator>());
	ThePanelFactory::Instance()->registerType(PanelConsts::towerUpgradePanel, std::make_shared<TowerUpgradePanelCreator>());
	ThePanelFactory::Instance()->registerType(PanelConsts::tipsPanel, std::make_shared<TipsPanelCreator>());
}

void Game::configureProgressManager()
{
	// create repositories
	std::shared_ptr<GameProgressRepository> gameRepo = std::make_shared<GameProgressRepository>();
	std::shared_ptr<MapsRepository> mapRepo = std::make_shared<MapsRepository>();
	std::shared_ptr<MapsProgressRepository> mapProgressRepo = std::make_shared<MapsProgressRepository>();

	// db context
	std::shared_ptr<UserProgressDBContext> dbContext = std::make_shared<UserProgressDBContext>();

	m_progressManager = std::make_shared<ProgressManager>(gameRepo, mapRepo, mapProgressRepo, dbContext);
}

void Game::quit()
{
	m_bRunning = false;
}

void Game::handleEvents()
{
	// handle input
	TheInputHandler::Instance()->update();

	// handle active state events
	m_pGameStateMachine->handleEvents();
}