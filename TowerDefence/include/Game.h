#ifndef __Game__
#define __Game__

#include "EntitiesHeaders/GameObject.h"
#include "EntitiesHeaders/Player.h"
#include "EntitiesHeaders/Enemy.h"

#include "UtilsHeaders/GameStateMachine.h"
#include "UtilsHeaders/TextureManager.h"

#include<SDL.h>
#include<vector>
#include<memory>

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

	std::shared_ptr<GameStateMachine> m_pGameStateMachine;
};


typedef Game TheGame;
#endif // !__Game__