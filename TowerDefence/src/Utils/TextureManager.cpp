#include "../../include/UtilsHeaders/TextureManager.h"

#include<SDL_image.h>
#include<iostream>

TextureManager::TextureManager()
{
}

TextureManager* TextureManager::s_pInstance = nullptr;

TextureManager* TextureManager::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = new TextureManager();
		return s_pInstance;
	}
	return s_pInstance;
}

void TextureManager::clean()
{
	std::cout << "Release TextureManager Instance\n";
	delete s_pInstance;
	s_pInstance = nullptr;
}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (pTempSurface == 0)
	{
		return false;
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}

	return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}


void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::clearFromTextureMap(std::string id)
{
	m_textureMap.erase(id);
}

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = margin + (spacing + width) * currentFrame;
	srcRect.y = margin + (spacing + height) * currentRow;

	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::drawFilledCircle(int centerX, int centerY, int radius, SDL_Color color, SDL_Renderer* renderer, SDL_BlendMode blendMode)
{
	// get current color
	SDL_Color oldColor;
	SDL_GetRenderDrawColor(renderer, &oldColor.r, &oldColor.g, &oldColor.b, &oldColor.a);

	// set color and blendmode
	SDL_SetRenderDrawBlendMode(renderer, blendMode);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	drawCircle(centerX, centerY, radius, renderer);

	// return back old colors and blendMode
	SDL_SetRenderDrawColor(renderer, oldColor.r, oldColor.g, oldColor.b, oldColor.a);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}


void TextureManager::drawProgressBar(int x, int y, int width, int height, SDL_Color bgColor, SDL_Color fillColor, float progress, SDL_Renderer* renderer)
{
	// get current color
	SDL_Color oldColor;
	SDL_GetRenderDrawColor(renderer, &oldColor.r, &oldColor.g, &oldColor.b, &oldColor.a);

	// draw frame
	SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	drawRectangle(x, y, width, height, renderer);

	// draw progress inside
	SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
	drawRectangle(x, y, progress * width, height, renderer);

	// return old color
	SDL_SetRenderDrawColor(renderer, oldColor.r, oldColor.g, oldColor.b, oldColor.a);
}

void TextureManager::dimBackground(SDL_Window* pWindow, SDL_Renderer* pRenderer)
{
	// get old draw color
	SDL_Color oldColor;
	SDL_GetRenderDrawColor(pRenderer, &oldColor.r, &oldColor.g, &oldColor.b, &oldColor.a);

	// get window's width and height
	int windowWidth, windowHeight;
	SDL_GetWindowSize(pWindow, &windowWidth, &windowHeight);

	// dim background
	SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 128);
	SDL_Rect dimRect = { 0, 0, windowWidth, windowHeight };
	SDL_RenderFillRect(pRenderer, &dimRect);

	// set the old draw color
	SDL_SetRenderDrawColor(pRenderer, oldColor.r, oldColor.g, oldColor.b, oldColor.a);
	SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_NONE);
}

void TextureManager::drawFilledRectangle(int x, int y, int width, int height, SDL_Color fillColor, SDL_Renderer* renderer)
{
	// get old draw color
	SDL_Color oldColor;
	SDL_GetRenderDrawColor(renderer, &oldColor.r, &oldColor.g, &oldColor.b, &oldColor.a);

	// draw rectangle
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
	drawRectangle(x, y, width, height, renderer);

	// set the old draw color
	SDL_SetRenderDrawColor(renderer, oldColor.r, oldColor.g, oldColor.b, oldColor.a);
}


void TextureManager::drawRectangle(int x, int y, int width, int height, SDL_Renderer* renderer)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;

	SDL_RenderFillRect(renderer, &rect);
}

void TextureManager::drawCircle(int centerX, int centerY, int radius, SDL_Renderer* renderer)
{
	int x = radius;
	int y = 0;
	int decisionOver2 = 1 - x; // initial condition

	while (x >= y) {
		// draw horizontal line
		drawHorizontalLine(centerX - x, centerX + x, centerY + y, renderer);
		drawHorizontalLine(centerX - x, centerX + x, centerY - y, renderer);
		drawHorizontalLine(centerX - y, centerX + y, centerY + x, renderer);
		drawHorizontalLine(centerX - y, centerX + y, centerY - x, renderer);

		y++;

		if (decisionOver2 <= 0) {
			decisionOver2 += 2 * y + 1; // error correction
		}
		else {
			x--;
			decisionOver2 += 2 * (y - x) + 1;
		}
	}
}

void TextureManager::drawHorizontalLine(int x1, int x2, int y, SDL_Renderer* renderer)
{
	SDL_RenderDrawLine(renderer, x1, y, x2, y);
}

