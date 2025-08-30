#ifndef __Game__
#define __Game__

#include "DataHeaders/ProgressManager.h"

#include "EntitiesHeaders/GameObject.h"

#include "ManagersHeaders/LevelManager.h"
#include "ManagersHeaders/TowerUnlockManager.h"

#include "UtilsHeaders/GameStateMachine.h"

#include<SDL.h>
#include<SDL_ttf.h>
#include<vector>
#include<memory>

#define OUTLINE_SIZE 2

/**
* Main class.
* 
* Game initiate SDL2 components and registers dynamic objects to be created on runtime.
*/
class Game
{
public:
	static Game* Instance();
	~Game();
	/**
	* Initiate SDL2 window and renderer.
	* 
	* Register gameObjects and Panels.
	*/
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	/**
	* Renders game.
	*/
	void render();
	/**
	* Update game.
	*/
	void update();
	/**
	* Handle game.
	*/
	void handleEvents();
	/**
	* Clean memory on exit.
	*/
	void clean();
	/**
	* Exit from the game.
	*/
	void quit();
	
	// getters and setters 

	SDL_Renderer* getRenderer() const;
	SDL_Window* getWindow() const;
	TTF_Font* getFont() const;
	TTF_Font* getFontOutline() const;
	std::shared_ptr<GameStateMachine> getStateMachine();
	std::shared_ptr<ProgressManager> getProgressManager();
	std::shared_ptr<LevelManager> getLevelManager();
	std::shared_ptr<TowerUnlockManager> getTowerUnlockManager();
	int getGameWidth() const;
	int getGameHeight() const;



	// @return true if still playing. When you quit game it returns false.
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

	bool m_bRunning; // flag for running main game loop.
	int m_gameWidth;
	int m_gameHeight;

	Game();
	static Game* s_pInstance;

	// SDL components

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;

	TTF_Font* m_pFont;
	TTF_Font* m_pFontOutline;

	// game components

	std::shared_ptr<GameStateMachine> m_pGameStateMachine;

	std::shared_ptr<ProgressManager> m_progressManager;

	std::shared_ptr<LevelManager> m_levelManager;

	std::shared_ptr<TowerUnlockManager> m_towerUnlockManager;
};


typedef Game TheGame;
#endif // !__Game__