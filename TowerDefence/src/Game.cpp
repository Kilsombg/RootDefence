#include "../include/Game.h"

#include "../include/Constants/GameObjectConsts.h"

#include "../include/EntitiesHeaders/MenuButton.h"
#include "../include/EntitiesHeaders/TowerButton.h"
#include "../include/EntitiesHeaders/TowerUpgradedButton.h"
#include "../include/EntitiesHeaders/SellTowerButton.h"
#include "../include/EntitiesHeaders/Tower.h"
#include "../include/EntitiesHeaders/FreezeTower.h"
#include "../include/EntitiesHeaders/Projectile.h"
#include "../include/EntitiesHeaders/AnimatedGraphic.h"
#include "../include/EntitiesHeaders/Text.h"
#include "../include/EntitiesHeaders/Texture.h"


#include "../include/GameStateHeaders/MainMenuState.h"
#include "../include/GameStateHeaders/PlayState.h"

#include "../include/UIHeaders/GameOverUIHeaders/GameOverStatePanel.h"

#include "../include/UIHeaders/PauseStateUIHeaders/PauseStatePanel.h"

#include "../include/UIHeaders/PlayStateUIHeaders/TowersPanel.h"
#include "../include/UIHeaders/PlayStateUIHeaders/TowerUpgradePanel.h"


#include "../include/UtilsHeaders/TrueTypeManager.h"
#include "../include/UtilsHeaders/InputHandler.h"
#include "../include/UtilsHeaders/GameObjectFactory.h"
#include "../include/UtilsHeaders/PanelFactory.h"

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
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0)
			{
				std::cout << "renderer creation success\n";

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

				// stretching window
				SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
				SDL_RenderSetLogicalSize(m_pRenderer, width, height);
				SDL_SetWindowMinimumSize(m_pWindow, width, height);
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

	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::player, std::make_shared<PlayerCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::greenChoy, std::make_shared<EnemyCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::greenPlant,std::make_shared<EnemyCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::greenBroccoli,std::make_shared<EnemyCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::yellowOrange, std::make_shared<EnemyCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::yellowCarrot,std::make_shared<EnemyCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::yellowSquash,std::make_shared<EnemyCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::redRadish, std::make_shared<EnemyCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::redPepper ,std::make_shared<EnemyCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::redTomato ,std::make_shared<EnemyCreator>());

	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::stump , std::make_shared<TowerCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::pine, std::make_shared<TowerCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::oak , std::make_shared<TowerCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::frozenBush , std::make_shared<FreezeTowerCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::projectile, std::make_shared<ProjectileCreator>());

	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::menuButton, std::make_shared<MenuButtonCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::towerButton, std::make_shared<TowerButtonCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::towerUpgradedButton, std::make_shared<TowerUpgradedButtonCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::sellTowerButton, std::make_shared<SellTowerButtonCreator>());

	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::animatedGraphic, std::make_shared<AnimatedGraphicCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::text, std::make_shared<TextCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::texture, std::make_shared<TextureCreator>());


	ThePanelFactory::Instance()->registerType(PanelConsts::gameOverStatePanel, std::make_shared<GameOverStatePanelCreator>());
	
	ThePanelFactory::Instance()->registerType(PanelConsts::pauseStatePanel, std::make_shared<PauseStatePanelCreator>());

	ThePanelFactory::Instance()->registerType(PanelConsts::towersPanel, std::make_shared<TowersPanelCreator>());
	ThePanelFactory::Instance()->registerType(PanelConsts::towerUpgradePanel, std::make_shared<TowerUpgradePanelCreator>());

	m_pGameStateMachine = TheGameStateMachine::Instance();
	//m_pGameStateMachine->changeState(std::make_shared<MainMenuState>());
	m_pGameStateMachine->changeState(std::make_shared<PlayState>());


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

	TheTextureManager::Instance()->clean();

	TheTrueTypeManager::Instance()->clean();

	TTF_CloseFont(m_pFont);

	TheInputHandler::Instance()->clean();

	SDL_Quit();
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

void Game::quit()
{
	m_bRunning = false;
}

void Game::handleEvents()
{
	// handle input
	TheInputHandler::Instance()->update();

	// handle keys input
	if (TheInputHandler::Instance()->isKeyPressed(SDL_SCANCODE_RETURN))
	{
		m_pGameStateMachine->changeState(std::make_shared<PlayState>());
	}

	// handle active state events
	m_pGameStateMachine->handleEvents();
}