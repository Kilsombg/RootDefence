#include "../../include/EntitiesHeaders/Texture.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/UtilsHeaders/TextureManager.h"

Texture::Texture() : SDLGameObject(), m_hidden(false)
{
}

Texture::Texture(const Texture& texture) : m_hidden(texture.m_hidden), SDLGameObject(texture)
{
}

void Texture::clean()
{
	TheTextureManager::Instance()->clearFromTextureMap(m_textureID);
}

void Texture::draw()
{
	if (!m_hidden)
	{
		SDLGameObject::draw();
	}
}

void Texture::load(const std::shared_ptr<LoaderParams> pParams)
{
	SDLGameObject::load(pParams);

	m_hidden = pParams->getAttribute<bool>(LoaderParamsConsts::hidden);
}

void Texture::loadAttributes(std::string textureID, float x, float y, int width, int height)
{
	std::shared_ptr<LoaderParams> pParams = std::make_shared<LoaderParams>();
	pParams->setAttribute(LoaderParamsConsts::textureID, textureID);
	pParams->setAttribute(LoaderParamsConsts::x, x);
	pParams->setAttribute(LoaderParamsConsts::y, y);
	pParams->setAttribute(LoaderParamsConsts::width, width);
	pParams->setAttribute(LoaderParamsConsts::height, height);
	
	load(pParams);
}

void Texture::centerTexture()
{
	m_position.setX(m_position.getX() - m_width / 2);
	m_position.setY(m_position.getY() - m_height / 2);
}

void Texture::setHidden(bool hidden)
{
	m_hidden = hidden;
}

std::string Texture::getTextureID()
{
	return m_textureID;
}

std::unique_ptr<GameObject> TextureCreator::create() const
{
	return std::make_unique<Texture>();
}
