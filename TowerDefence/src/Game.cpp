#include "../include/Game.h"

#include "../include/GameStateHeaders/MenuState.h"
#include "../include/GameStateHeaders/PlayState.h"

#include "../include/UtilsHeaders/InputHandler.h"

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

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		m_pWindow = SDL_CreateWindow(title, xpos, ypos,
			width, height, flags);
		if (m_pWindow != 0)
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0)
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

				TheTextureManager::Instance()->load("./src/assets/animate.png", "animate", m_pRenderer);

				m_pGameStateMachine = new GameStateMachine();
				m_pGameStateMachine->changeState(new MenuState());
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
	std::cout << "init success\n";
	m_bRunning = true;
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
	SDL_Quit();
}

SDL_Renderer* Game::getRenderer() const
{
	return m_pRenderer;
}

GameStateMachine* Game::getStateMachine()
{
	return m_pGameStateMachine;
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
		m_pGameStateMachine->changeState(new PlayState());
	}
}