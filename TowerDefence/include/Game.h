#ifndef __Game__
#define __Game__

#include "EntitiesHeaders/GameObject.h"
#include "EntitiesHeaders/Player.h"
#include "EntitiesHeaders/Enemy.h"

#include "UtilsHeaders/TextureManager.h"

#include<SDL.h>
#include<vector>

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
	SDL_Renderer* getRenderer() const;
	
	bool running() { return m_bRunning; }

private:
	bool m_bRunning;
	int m_currentFrame;

	Game();
	static Game* s_pInstance;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;
	GameObject* m_go;
	GameObject* m_player;
	GameObject* m_enemy;
	std::vector<GameObject*> m_gameObjects;
};


typedef Game TheGame;
#endif // !__Game__