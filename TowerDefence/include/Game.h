#ifndef __Game__
#define __Game__

#include "DataHeaders/ProgressManager.h"

#include "EntitiesHeaders/GameObject.h"

#include "UtilsHeaders/GameStateMachine.h"

#include<SDL.h>
#include<SDL_ttf.h>
#include<vector>
#include<memory>

#define OUTLINE_SIZE 2

class Game
{
public:
	static Game* Instance();
	~Game();
	
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void render();
	void update();
	void handleEvents();
	void clean();
	void quit();
	
	SDL_Renderer* getRenderer() const;
	SDL_Window* getWindow() const;
	TTF_Font* getFont() const;
	TTF_Font* getFontOutline() const;
	std::shared_ptr<GameStateMachine> getStateMachine();
	std::shared_ptr<ProgressManager> getProgressManager();
	int getGameWidth() const;
	int getGameHeight() const;

	bool running();

private:
	/**
	* register game objects.
	*/
	void registerGameObjects();
	/**
	* register panels.
	*/
	void registerPanels();
	/**
	* configure progress manager.
	*/
	void configureProgressManager();

	bool m_bRunning;
	int m_gameWidth;
	int m_gameHeight;

	Game();
	static Game* s_pInstance;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;

	TTF_Font* m_pFont;
	TTF_Font* m_pFontOutline;

	std::shared_ptr<GameStateMachine> m_pGameStateMachine;

	std::shared_ptr<ProgressManager> m_progressManager;
};


typedef Game TheGame;
#endif // !__Game__