#include "../../include/EntitiesHeaders/AnimatedGraphic.h"

#include "../../include/UtilsHeaders/TextureManager.h"

#include "../../include/Game.h"

#include<SDL.h>

AnimatedGraphic::AnimatedGraphic() : SDLGameObject()
{
}

void AnimatedGraphic::draw()
{
	TheTextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
}

void AnimatedGraphic::update()
{
	m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
}


void AnimatedGraphic::clean()
{
	SDLGameObject::clean();
}

void AnimatedGraphic::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);

	m_animSpeed = pParams->getAnimSpeed();
}

std::unique_ptr<GameObject> AnimatedGraphicCreator::createGameObject() const
{
	return std::make_unique<AnimatedGraphic>();
}
