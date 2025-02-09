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
	
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void update();
	void handleEvents();
	void clean();
	void quit();
	
	SDL_Renderer* getRenderer() const;
	std::shared_ptr<GameStateMachine> getStateMachine();
	
	bool running();

private:
	bool m_bRunning;

	Game();
	static Game* s_pInstance;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;

	std::shared_ptr<GameStateMachine> m_pGameStateMachine;
};


typedef Game TheGame;
#endif // !__Game__