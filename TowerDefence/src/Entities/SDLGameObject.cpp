#include "../../include/EntitiesHeaders/SDLGameObject.h"

#include "../../include/Game.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/UtilsHeaders/TextureManager.h"

SDLGameObject::SDLGameObject() : GameObject()
{
}

SDLGameObject::SDLGameObject(const SDLGameObject& gameObject)
{
	m_position = gameObject.m_position;
	m_velocity = gameObject.m_velocity;
	m_acceleration = gameObject.m_acceleration;
	m_width = gameObject.m_width;
	m_height = gameObject.m_height;
	m_currentRow = gameObject.m_currentRow;
	m_currentFrame = gameObject.m_currentFrame;
	m_numFrames = gameObject.m_numFrames;
	m_textureID = gameObject.m_textureID;
}

void SDLGameObject::load(const std::shared_ptr<LoaderParams> pParams)
{
	m_position = Vector2D(pParams->getAttribute<float>(LoaderParamsConsts::x), pParams->getAttribute<float>(LoaderParamsConsts::y));
	m_velocity = Vector2D(0, 0);
	m_acceleration = Vector2D(0, 0);

	m_width = pParams->getAttribute<int>(LoaderParamsConsts::width);
	m_height = pParams->getAttribute<int>(LoaderParamsConsts::height);
	m_textureID = pParams->getAttribute<std::string>(LoaderParamsConsts::textureID);

	m_currentRow = 1;
	m_currentFrame = 1;

	m_numFrames = pParams->getAttribute<int>(LoaderParamsConsts::numFrames);
}

void SDLGameObject::draw()
{
	if (m_velocity.getX() > 0)
	{
		TextureManager::Instance()->drawFrame(m_textureID,
			(Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame,
			TheGame::Instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
	}
	else
	{
		TextureManager::Instance()->drawFrame(m_textureID,
			(Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame,
			TheGame::Instance()->getRenderer());
	}
}

void SDLGameObject::update()
{
	m_velocity += m_acceleration;
	m_position += m_velocity;
}

void SDLGameObject::clean()
{
}

Vector2D& SDLGameObject::getPosition()
{
	return m_position;
}

int SDLGameObject::getWidth()
{
	return m_width;
}

int SDLGameObject::getHeight()
{
	return m_height;
}