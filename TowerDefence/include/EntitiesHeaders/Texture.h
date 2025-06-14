#ifndef __Texture__
#define __Texture__

#include "SDLGameObject.h"

#include "../UtilsHeaders/BaseCreator.h"

#include <memory>
#include<string>

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
	void draw() override;

	void load(const std::shared_ptr<LoaderParams> pParams) override;

	void loadAttributes(std::string textureID, float x, float y, int width, int height);

	/**
	* Center texture based on position i.e. make position coordinates texture's center.
	* 
	* Call this method only once.
	*/
	void centerTexture();

	// getters and setters

	void setHidden(bool hidden);

	std::string getTextureID();

private:
	bool m_hidden;
};

class TextureCreator : public BaseCreator
{
	std::unique_ptr<GameObject> create() const override;
};

#endif // !__Texture__
