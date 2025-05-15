#ifndef __Texture__
#define __Texture__

#include "SDLGameObject.h"

#include "../UtilsHeaders/BaseCreator.h"

#include <memory>


/**
* Class to represent a texture on screen.
* 
* Use this class, when you need to only show a texture on screen.
* examples:
* - background,
* - icons
*/
class Texture : public SDLGameObject
{
public:
	Texture();
	void clean() override;
};

class TextureCreator : public BaseCreator
{
	std::unique_ptr<GameObject> create() const override;
};

#endif // !__Texture__
