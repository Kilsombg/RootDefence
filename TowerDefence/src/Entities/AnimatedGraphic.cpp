#include "../../include/EntitiesHeaders/AnimatedGraphic.h"

#include "../../include/UtilsHeaders/TextureManager.h"

#include "../../include/Game.h"

#include<SDL.h>

AnimatedGraphic::AnimatedGraphic(const LoaderParams* pParams, int animSpeed) : SDLGameObject(pParams), m_animSpeed(animSpeed)
{
}

void AnimatedGraphic::draw()
{
    TheTextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
}

void AnimatedGraphic::update()
{
	m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % 6));
}


void AnimatedGraphic::clean()
{

}

void AnimatedGraphic::load(const LoaderParams* pParams)
{
    m_position = Vector2D(static_cast<double>(pParams->getX()), static_cast<double>(pParams->getY()));
    m_velocity = Vector2D(0.0, 0.0);
    m_acceleration = Vector2D(0.0, 0.0);
    
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_currentRow = 1;
    m_currentFrame = 1;
}