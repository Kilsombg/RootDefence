#include "../../include/EventHandlersHeaders/ClickToPlaceTowerHandler.h"

#include "../../include/UtilsHeaders/TowerFactory.h"
#include "../../include/UtilsHeaders/Vector2D.h"
#include "../../include/UtilsHeaders/InputHandler.h"
#include "../../include/UtilsHeaders/TextureManager.h"

#include "../../include/Game.h"

#include<memory>
#include<iostream>

ClickToPlaceTowerHandler::ClickToPlaceTowerHandler() : m_state(IDLE), m_activeButton(nullptr), m_canPlace(true)
{
}

void ClickToPlaceTowerHandler::handleEvent(Button* sourceButton)
{
	// if we send nullptr we stop the event
	if (sourceButton == nullptr)
	{
		interrupt();
		return;
	}
	std::cout << "ClickToPlaceHandler handleEvent() called.\n";
	switch (m_state) {
	case IDLE:
		handleIdleState(sourceButton);
		break;
	case MOVING:
		handleMovingState(sourceButton);
		break;
	case PLACING:
		// do nothing
		break;
	case INTERRUPTED:
		// do nothing
		break;
	}
}

void ClickToPlaceTowerHandler::update(std::vector<std::unique_ptr<GameObject>>& gameObjects)
{
	if (m_state == IDLE) return; 



	if (m_activeButton != nullptr)
	{
		if (m_state == MOVING)
		{
			setShadowObjectPosition();
		}
		else if (m_state == PLACING)
		{
			if (addObject(gameObjects))
			{
				m_state = IDLE;
			}
		}
	}
	else if (m_state == INTERRUPTED)
	{
		m_state = IDLE;
	}
}

void ClickToPlaceTowerHandler::render()
{
	m_shadowObjectRadiusColor = ColorsConsts::red;
	TheTextureManager::Instance()->drawFilledCircle(
		m_shadowObject->getPosition().getX(), m_shadowObject->getPosition().getY(), static_cast<int>(m_shadowObject->getRadius()),
		{m_shadowObjectRadiusColor.r, m_shadowObjectRadiusColor.g, m_shadowObjectRadiusColor.b, m_shadowObjectRadiusColor.a},
		TheGame::Instance()->getRenderer());
	m_shadowObject->draw();
}

void ClickToPlaceTowerHandler::clear()
{
}

std::unique_ptr<Tower>& ClickToPlaceTowerHandler::getShadowObject()
{
	return m_shadowObject;
}

void ClickToPlaceTowerHandler::handleIdleState(Button* sourceButton)
{
	if (m_activeButton = dynamic_cast<TowerButton*>(sourceButton))
	{
		createShadowObject();
		m_state = MOVING;
	}
	else {
		interrupt();
	};
}

void ClickToPlaceTowerHandler::handleMovingState(Button* sourceButton)
{
	if (m_activeButton != sourceButton) {
		interrupt();
	}
	else {
		m_state = PLACING;
	}
}

void ClickToPlaceTowerHandler::createShadowObject()
{
	m_shadowObject = TheTowerFactory::Instance()->createShadowTower(m_activeButton->getTowerName());	
}

void ClickToPlaceTowerHandler::setShadowObjectPosition()
{
	std::shared_ptr<Vector2D> mousePos = InputHandler::Instance()->getMousePosition();
	m_shadowObject->setPosition(*(mousePos.get()));
}

void ClickToPlaceTowerHandler::interrupt()
{
	m_state = INTERRUPTED;
	m_activeButton = nullptr;
	m_shadowObject = nullptr;
}
	
bool ClickToPlaceTowerHandler::addObject(std::vector<std::unique_ptr<GameObject>>& gameObjects)
{
	if (m_shadowObject == nullptr)
	{
		return false;
	}

	gameObjects.push_back(std::move(m_shadowObject));
	return true;
}