#ifndef __Game__
#define __Game__

#include "EntitiesHeaders/GameObject.h"
#include "EntitiesHeaders/Player.h"
#include "EntitiesHeaders/Enemy.h"

#include "UtilsHeaders/GameStateMachine.h"
#include "UtilsHeaders/TextureManager.h"

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
	int getGameWidth() const;
	int getGameHeight() const;
	
	bool running();

private:
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
};


typedef Game TheGame;
#endif // !__Game__