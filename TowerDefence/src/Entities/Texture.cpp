#include "../../include/EntitiesHeaders/Texture.h"

#include "../../include/UtilsHeaders/TextureManager.h"

Texture::Texture() : SDLGameObject()
{
}

void Texture::clean()
{
	TheTextureManager::Instance()->clearFromTextureMap(m_textureID);
}

std::unique_ptr<GameObject> TextureCreator::create() const
{
	return std::make_unique<Texture>();
}
