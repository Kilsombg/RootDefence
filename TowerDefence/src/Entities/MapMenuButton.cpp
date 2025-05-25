#include "../../include/EntitiesHeaders/MapMenuButton.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/UtilsHeaders/InputHandler.h"
#include "../../include/UtilsHeaders/TextureManager.h"

#include "../../include/Game.h"

MapMenuButton::MapMenuButton() : MenuButton(), m_mouseOver(false)
{
}

MapMenuButton::MapMenuButton(const MapMenuButton* mapMenuButton) : MenuButton(mapMenuButton)
{
	m_mapLevelFileName = mapMenuButton->m_mapLevelFileName;
}

void MapMenuButton::update()
{
	// check if mouse is over button
	m_mouseOver = TheInputHandler::Instance()->isMouseOnObject(m_position, m_width, m_height);

	// update button
	MenuButton::update();
}

void MapMenuButton::draw()
{
	int offset = 4;
	if (m_mouseOver)
	{
		// draw outline
		TheTextureManager::Instance()->drawFilledRectangle(m_position.getX() - offset,
			m_position.getY() - offset, m_width + 2 * offset, m_height + 2 * offset,
			{ 255, 255, 255, 255 },
			TheGame::Instance()->getRenderer());
	}

	// draw frame
	TheTextureManager::Instance()->drawFilledRectangle(m_position.getX() - offset/2,
		m_position.getY() - offset/2, m_width + offset, m_height + offset,
		{ 0x2B, 0x1A, 0x17, 255 },
		TheGame::Instance()->getRenderer());

	// draw button
	MenuButton::draw();
}

void MapMenuButton::load(const std::shared_ptr<LoaderParams> pParams)
{
	MenuButton::load(pParams);

	m_mapLevelFileName = pParams->getAttribute<std::string>(LoaderParamsConsts::mapLevelFileName);
}

void MapMenuButton::setCallback(MapMenuButtonCallback callback)
{
	m_callback = callback;
}

void MapMenuButton::handleClickOnButton()
{
	if (m_isMouseOnButton && !m_pressedOutside)
	{
		// m_currentFrame = MOUSE_OVER;

		if (!TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			// m_currentFrame = CLICKED;

			m_callback(m_mapLevelFileName);

			m_bReleased = false;
		}
		else if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_bReleased = true;
		}
	}
	else
	{
		m_bReleased = false;

		// m_currentFrame = MOUSE_OUT;
	}
}

std::unique_ptr<GameObject> MapMenuButtonCreator::create() const
{
	return std::make_unique<MapMenuButton>();
}
