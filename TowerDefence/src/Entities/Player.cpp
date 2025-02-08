#include "../../include/EntitiesHeaders/Player.h"

#include "../../include/UtilsHeaders/InputHandler.h"
#include<SDL.h>

Player::Player() : SDLGameObject()
{
}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

	handleInput();

	SDLGameObject::update();
}

void Player::clean()
{
	SDLGameObject::clean();
}

void Player::load(const std::shared_ptr<LoaderParams> pParams)
{
	SDLGameObject::load(pParams);
}

void Player::handleInput()
{
	if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
	{
		Vector2D* target = TheInputHandler::Instance()->getMousePosition();

		m_velocity = (*target - m_position) / 50;
	}
}

std::unique_ptr<GameObject> PlayerCreator::createGameObject() const
{
	return std::make_unique<Player>();
}
