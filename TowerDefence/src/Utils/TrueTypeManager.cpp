#include "../../include/UtilsHeaders/TrueTypeManager.h"

#include "../../include/Game.h"

TrueTypeManager* TrueTypeManager::s_pInstance = nullptr;

TrueTypeManager* TrueTypeManager::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = new TrueTypeManager();
		return s_pInstance;
	}
	return s_pInstance;
}

TrueTypeManager::TrueTypeManager()
{
}

void TrueTypeManager::clean()
{
	delete s_pInstance;
	s_pInstance = nullptr;
}

bool TrueTypeManager::load(std::string id, std::string textMessage, TTF_Font* font, TTF_Font* fontOutline, SDL_Color color, SDL_Color colorOutline, SDL_Renderer* pRenderer)
{
	// add character when empty to prevent TTF_RenderText_Blended returning NULL.
	if (textMessage.empty()) textMessage = " ";

	// create font and background surfaces
	SDL_Surface* fg_surface = TTF_RenderText_Blended(font, textMessage.c_str(), color);
	SDL_Surface* bg_surface = TTF_RenderText_Blended(fontOutline, textMessage.c_str(), colorOutline);
	SDL_Rect rect = { OUTLINE_SIZE, OUTLINE_SIZE, fg_surface->w, fg_surface->h };

	// blit text onto its outline 
	SDL_SetSurfaceBlendMode(fg_surface, SDL_BLENDMODE_BLEND);
	SDL_BlitSurface(fg_surface, NULL, bg_surface, &rect);
	SDL_FreeSurface(fg_surface);

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, bg_surface);
	SDL_FreeSurface(bg_surface);

	if (pTexture != 0)
	{
		m_textTextureMap[id] = pTexture;
		return true;
	}
	return false;
}

bool TrueTypeManager::loadNoOutline(std::string id, std::string textMessage, TTF_Font* font, SDL_Color color, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = TTF_RenderText_Solid(font, textMessage.c_str(), color);
	if (pTempSurface == 0)
	{
		return false;
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0)
	{
		m_textTextureMap[id] = pTexture;
		return true;
	}

	return false;
}


void TrueTypeManager::clearFromTextureMap(std::string id)
{
	m_textTextureMap.erase(id);
}

void TrueTypeManager::drawText(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer)
{
	SDL_Rect textRect;

	textRect.x = x;
	textRect.y = y;
	textRect.w = width;
	textRect.h = height;

	SDL_RenderCopy(pRenderer, m_textTextureMap[id], NULL, &textRect);
}

