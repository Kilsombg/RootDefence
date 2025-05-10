// This project uses SDL2_ttf
// https://github.com/libsdl-org/SDL_ttf
// Licensed under the Zlib License (see below)

/*
Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef __TrueTypeManager__
#define __TrueTypeManager__

#include<SDL.h>
#include<SDL_ttf.h>
#include<string>
#include<map>

/**
* Manage text drawing on screen using SDL2_ttf library.
* 
* First you need to load the message with load() method, then call drawText() method to display the text.
* When you finish using a message, call clearFromTextureMap() to free the texture from the map.
* When you finish working with the manager, call clean() to free the memory.
*/
class TrueTypeManager
{
public:
	static TrueTypeManager* Instance();
	/**
	* clean manager's memomry usage.
	*/
	void clean();

	/**
	* Load text message as a texture to draw on screen.
	* 
	* @param id, textMessage - are respectively id and message of the text you want to display on sreen
	* @param font, color - are respectively font and color of the text to be displayed.
	* @param pRenderer - SDL renderer
	*/
	bool load(std::string id, std::string textMessage,TTF_Font* font, SDL_Color color, SDL_Renderer* pRenderer);
	/**
	* Deletes a texture from the map.
	* 
	* @param id - texture's id to be deleted.
	*/
	void clearFromTextureMap(std::string id);
	/**
	* Display a text on screen.
	* 
	* @param id of the text.
	* @param x, y - coordinates to be displayed.
	* @param width, height of the text message.
	* @param pRenderer - SDL renderer
	*/
	void drawText(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer);

private:
	TrueTypeManager();
	static TrueTypeManager* s_pInstance;

	// map of text texture ready to be displayed on screen.
	std::map<std::string, SDL_Texture*> m_textTextureMap;
};

typedef TrueTypeManager TheTrueTypeManager;

#endif // !__TrueTypeManager__
