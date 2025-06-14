#ifndef __TextureManager__
#define __TextureManager__

#include<SDL.h>
#include<string>
#include<map>

/**
* Manages textures.
* 
* Load textures inside Manager, when finished with them calls clearFromTextureMap() to clear them.
* 
* Call draw() or drawFrame() to draw textures.
* drawTile() is map's tiles drawing.
* 
* Beside textures it can draw progressBar, circles and filledRectangles.
*/
class TextureManager
{
public:
	static TextureManager* Instance();
	/**
	* Clears TextureManager instance.
	*/
	static void clean();
	/**
	* Load a texture in manager with id.
	* 
	* @param fileName - path to the texture file.
	* @param id - identifier for accessing from textureMap.
	* @param pRenderer - game Renderer.
	*/
	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	/**
	* Draw full texture.
	* If object has animation call drawFrame() instead.
	* 
	* @param id - texture id.
	* @param x,y - destination coordinates to be drawn.
	* @param width, height of the texture.
	* @param pRenderer - game Renderer.
	* @param flip - flip constant. Default value SDL_FLIP_NONE.
	*/
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	/**
	* Draw a frame of image.
	* If image has no animation call draw() or set currentRow and currentFrame to 0 and 1.
	* 
	* @param id - texture id.
	* @param x,y - destination coordinates to be drawn.
	* @param width, height of the texture.
	* @param currentRow, currentFrame - row and frame of the animation.
	* @param pRenderer - game Renderer.
	* @param flip - flip constant. Default value SDL_FLIP_NONE.
	*/
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	/**
	*Clear texture from textureMap when not needed anymore.
	* 
	* @param id - texture id.
	*/
	void clearFromTextureMap(std::string id);
	/**
	* Draw tile from tileSet.
	* 
	* @param id - tileset texture id.
	* @param margin, spacing of tileset.
	* @param x,y - destination coordinates to be drawn.
	* @param width, height of the tile.
	* @param currentRow, currentFrame - row and frame of the tile in tileset.
	* @param pRenderer - game Renderer.
	*/
	void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer);
	/**
	* Draw filled circle with color.
	* 
	* @param centerX, centerY - coordinates of circle's center.
	* @param radius of circle.
	* @param color of the circle to be drawn.
	* @param pRenderer - game Renderer.
	* @param blendMode. Default value SDL_BLENDMODE_BLEND.
	*/
	void drawFilledCircle(int centerX, int centerY, int radius, SDL_Color color, SDL_Renderer* renderer, SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND);
	/**
	* Draw progress bar with progress.
	* 
	* @param x, y- destinaiton coordinates.
	* @param width, height of the progressBar.
	* @param bgColor - frame color.
	* @param fillColor - progress color.
	* @param progress - value of the progerss in range [0,1].
	* @param pRenderer - game Renderer.
	*/
	void drawProgressBar(int x, int y, int width, int height, SDL_Color bgColor, SDL_Color fillColor, float progress, SDL_Renderer* renderer);
	/**
	* Dim full screen.
	* Call this method when drawing state underneath another state.
	* Methods needs to be invoked between the two states draw() methods.
	* 
	* @param game window and renderer.
	*/
	void dimBackground(SDL_Window* pWindow , SDL_Renderer* pRenderer);
	/**
	* Draw filled rectangle on screen.
	* 
	* @param x,y - destination coordinates.
	* @param width, height of the rectangle.
	* @param fillColor - color of rectangle.
	* @param pRenderer - game Renderer.
	*/
	void drawFilledRectangle(int x, int y, int width, int height, SDL_Color fillColor, SDL_Renderer* renderer);

private:
	TextureManager();
	static TextureManager* s_pInstance;

	/**
	* Draw circle on screen.
	* 
	* @param centerX, centerY - coordinates of circle's center.
	* @param radius of circle.
	* @param pRenderer - game Renderer.
	*/
	void drawCircle(int centerX, int centerY, int radius, SDL_Renderer* renderer);
	/**
	* Draw horizontal line.
	* 
	* param (x1,y) starting point. (x2,y) end point.
	* @param pRenderer - game Renderer.
	*/
	void drawHorizontalLine(int x1, int x2, int y, SDL_Renderer* renderer);
	/**
	* Draw rectangle on screen.
	* 
	* @param x,y - destination coordinates.
	* @param width, height of the rectangle.
	* @param pRenderer - game Renderer.
	*/
	void drawRectangle(int x, int y, int width, int height, SDL_Renderer* renderer);

	std::map<std::string, SDL_Texture*> m_textureMap; // texture map,containing current textures ready to be drawn.
};

typedef TextureManager TheTextureManager;

#endif // !__TextureManager__
