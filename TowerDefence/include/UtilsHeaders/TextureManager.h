#ifndef __TextureManager__
#define __TextureManager__

#include<SDL.h>
#include<string>
#include<map>

class TextureManager
{
public:
	static TextureManager* Instance();

	static void clean();
	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void clearFromTextureMap(std::string id);
	void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer);

	void drawFilledCircle(int centerX, int centerY, int radius, SDL_Color color, SDL_Renderer* renderer, SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND);

	void drawProgressBar(int x, int y, int width, int height, SDL_Color bgColor, SDL_Color fillColor, float progress, SDL_Renderer* renderer);

private:
	TextureManager();
	static TextureManager* s_pInstance;

	void drawCircle(int centerX, int centerY, int radius, SDL_Renderer* renderer);
	void drawHorizontalLine(int x1, int x2, int y, SDL_Renderer* renderer);
	void drawRectangle(int x, int y, int width, int height, SDL_Renderer* renderer);

	std::map<std::string, SDL_Texture*> m_textureMap;
};

typedef TextureManager TheTextureManager;

#endif // !__TextureManager__
