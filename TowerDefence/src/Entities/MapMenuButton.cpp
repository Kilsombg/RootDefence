#include "../../include/EntitiesHeaders/MapMenuButton.h"

#include "../../include/Constants/LoaderParamsConsts.h"
#include "../../include/Constants/UIConsts.h"

#include "../../include/UtilsHeaders/InputHandler.h"
#include "../../include/UtilsHeaders/TextureManager.h"
#include "../../include/UtilsHeaders/LoaderParams.h"

#include "../../include/Game.h"

MapMenuButton::MapMenuButton() : MenuButton(), m_mouseOver(false)
{
}

MapMenuButton::MapMenuButton(const MapMenuButton* mapMenuButton) : MenuButton(mapMenuButton)
{
	m_mapLevelFileName = mapMenuButton->m_mapLevelFileName;
	m_mapName = mapMenuButton->m_mapName;
	m_mapNameText = mapMenuButton->m_mapNameText;
	m_maxWaveText = mapMenuButton->m_maxWaveText;
}

void MapMenuButton::update()
{
	// check if mouse is over button
	m_mouseOver = TheInputHandler::Instance()->isMouseOnObject(m_position, m_width, m_height);

	// update button
	MenuButton::update();

	// update maxWave message
	updateMaxWaveLabel();
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
	TheTextureManager::Instance()->drawFilledRectangle(m_position.getX() - offset / 2,
		m_position.getY() - offset / 2, m_width + offset, m_height + offset,
		{ 0x2B, 0x1A, 0x17, 255 },
		TheGame::Instance()->getRenderer());

	// draw button
	MenuButton::draw();

	// draw max wave label
	m_maxWaveText->draw();

	// draw map name label
	m_mapNameText->draw();
}

void MapMenuButton::load(const std::shared_ptr<LoaderParams> pParams)
{
	MenuButton::load(pParams);

	m_mapLevelFileName = pParams->getAttribute<std::string>(LoaderParamsConsts::mapLevelFileName);

	int id = getID();
	m_mapName = id != -1 ? (*TheGame::Instance()->getProgressManager()->getMaps())[id - 1].name : "not found";
	loadMapLabel(m_mapName);

	loadMaxWaveLabel();
}

void MapMenuButton::clean()
{
	// clean map name text texture
	m_mapNameText->clean();

	// clean max wave text texture
	m_maxWaveText->clean();

	// clean button
	MenuButton::clean();
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

			m_callback(m_mapLevelFileName, getID());

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

void MapMenuButton::updateMaxWaveLabel()
{
	std::string message = "best wave: " + std::to_string((*TheGame::Instance()->getProgressManager()->getMapsProgress())[getID() - 1].maxWave);
	m_maxWaveText->setMessage(message);
	m_maxWaveText->update();
}

void MapMenuButton::loadMapLabel(std::string name)
{
	m_mapNameText = std::make_shared<Text>();
	std::shared_ptr<LoaderParams> pParams = std::make_shared<LoaderParams>();

	int textHeight = 14;
	int characterWidth = 7;
	int textWidth = characterWidth * name.length();

	pParams->setAttribute(LoaderParamsConsts::x, m_position.getX() + m_width / 2 - textWidth / 2);
	pParams->setAttribute(LoaderParamsConsts::y, m_position.getY() + m_height - textHeight);
	pParams->setAttribute(LoaderParamsConsts::characterWidth, characterWidth);
	pParams->setAttribute(LoaderParamsConsts::height, textHeight);
	std::string mapNameID = generateMapTextIDWithSuffix(UIConsts::mapNameLabelSuffix);
	pParams->setAttribute(LoaderParamsConsts::textureID, mapNameID);
	pParams->setAttribute(LoaderParamsConsts::labelId, mapNameID);
	pParams->setAttribute(LoaderParamsConsts::message, name);

	m_mapNameText->load(pParams);
}

void MapMenuButton::loadMaxWaveLabel()
{
	m_maxWaveText = std::make_shared<Text>();
	std::shared_ptr<LoaderParams> pParams = std::make_shared<LoaderParams>();

	// set message
	std::string message = "best wave: " + std::to_string((*TheGame::Instance()->getProgressManager()->getMapsProgress())[getID() - 1].maxWave);

	int textHeight = 12;
	int characterWidth = 6;

	// set attributes
	pParams->setAttribute(LoaderParamsConsts::x, m_position.getX() + 3);
	pParams->setAttribute(LoaderParamsConsts::y, m_position.getY() + 3);
	pParams->setAttribute(LoaderParamsConsts::characterWidth, characterWidth);
	pParams->setAttribute(LoaderParamsConsts::height, textHeight);
	std::string labelID = generateMapTextIDWithSuffix(UIConsts::maxWaveLabelSuffix);
	pParams->setAttribute(LoaderParamsConsts::textureID, labelID);
	pParams->setAttribute(LoaderParamsConsts::labelId, labelID);
	pParams->setAttribute(LoaderParamsConsts::message, message);

	m_maxWaveText->load(pParams);
}

int MapMenuButton::getID()
{
	// textureID must have 'l' before id number from mapLevel and ends with "ID" suffix.
	int idNumberIndex = m_textureID.rfind('l') + 1;
	int IDIndex = m_textureID.find("ID");
	std::string idStr = m_textureID.substr(idNumberIndex, IDIndex - idNumberIndex);
	if (std::isdigit(idStr[0]))
	{
		return std::stoi(idStr);
	}
	return -1;
}

std::string MapMenuButton::generateMapTextIDWithSuffix(std::string suffix)
{
	int idIndex = m_textureID.find("ID");
	std::string labelID = m_textureID.substr(0, idIndex) + suffix;
	return labelID;
}

std::unique_ptr<GameObject> MapMenuButtonCreator::create() const
{
	return std::make_unique<MapMenuButton>();
}
