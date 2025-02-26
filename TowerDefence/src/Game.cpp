#include "../include/Game.h"

#include "../include/Constants/GameObjectConsts.h"

#include "../include/EntitiesHeaders/MenuButton.h"
#include "../include/EntitiesHeaders/TowerButton.h"
#include "../include/EntitiesHeaders/AnimatedGraphic.h"
#include "../include/EntitiesHeaders/Carrot.h"
#include "../include/EntitiesHeaders/Cabbage.h"

#include "../include/GameStateHeaders/MainMenuState.h"
#include "../include/GameStateHeaders/PlayState.h"

#include "../include/UtilsHeaders/InputHandler.h"
#include "../include/UtilsHeaders/GameObjectFactory.h"

#include<iostream>
#include<memory>

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

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{

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

	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::player, std::make_shared<PlayerCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::carrot, std::make_shared<CarrotCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::cabbage ,std::make_shared<CabbageCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::tower ,std::make_shared<PlayerCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::menuButton, std::make_shared<MenuButtonCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::towerButton, std::make_shared<TowerButtonCreator>());
	TheGameObjectFactory::Instance()->registerType(GameObjectConsts::animatedGraphic, std::make_shared<AnimatedGraphicCreator>());

	m_pGameStateMachine = TheGameStateMachine::Instance();
	m_pGameStateMachine->changeState(std::make_shared<MainMenuState>());


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

	TheInputHandler::Instance()->clean();

	SDL_Quit();
}

SDL_Renderer* Game::getRenderer() const
{
	return m_pRenderer;
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
	TheInputHandler::Instance()->update();

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		m_pGameStateMachine->changeState(std::make_shared<PlayState>());
	}
}