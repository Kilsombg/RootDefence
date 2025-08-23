#include "../../include/EntitiesHeaders/Text.h"

#include "../../include/Game.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/UtilsHeaders/TrueTypeManager.h"

Text::Text() : GameObject()
{
}

Text::Text(float x, float y, int characterWidth, int width, int height, std::string textureID, std::string labelID, std::string message, bool dynamic)
{
	m_position = Vector2D(x, y);
	m_characterWidth = characterWidth;
	m_width = width;
	m_height = height;
	m_textureID = textureID;
	m_message = message;
	m_prevMessage = message;
	m_labelID = labelID;
	m_dynamic = dynamic;

	m_isCentered = false;

	loadTexture();
}

void Text::draw()
{
	if (!m_hidden)
	{
		TheTrueTypeManager::Instance()->drawText(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, TheGame::Instance()->getRenderer());
	}
}

void Text::update()
{
	// if there is some change update texture
	if (m_message != m_prevMessage || m_fontColor != m_prevFontColor)
	{
		loadTexture();
		updateWidth();
		m_prevMessage = m_message;
		m_prevFontColor = m_fontColor;
	}
}

void Text::clean()
{
	TrueTypeManager::Instance()->clearFromTextureMap(m_textureID);
}

void Text::load(const std::shared_ptr<LoaderParams> pParams)
{
	m_position = Vector2D(pParams->getAttribute<float>(LoaderParamsConsts::x), pParams->getAttribute<float>(LoaderParamsConsts::y));
	m_characterWidth = pParams->getAttribute<int>(LoaderParamsConsts::characterWidth);
	m_height = pParams->getAttribute<int>(LoaderParamsConsts::height);
	m_textureID = pParams->getAttribute<std::string>(LoaderParamsConsts::textureID);
	m_labelID = pParams->getAttribute<std::string>(LoaderParamsConsts::labelId);
	m_message = pParams->getAttribute<std::string>(LoaderParamsConsts::message);
	m_prevMessage = m_message;
	m_width = m_message.length() * m_characterWidth;
	m_dynamic = pParams->getAttribute<bool>(LoaderParamsConsts::dynamic);
	m_hidden = pParams->getAttribute<bool>(LoaderParamsConsts::hidden);
	m_fontColor = ColorsConsts::white;
	m_prevFontColor = m_fontColor;
	m_fontOutlineColor = ColorsConsts::black;

	m_isCentered = false;

	loadTexture();
}

void Text::setMessage(std::string message)
{
	m_message = message;
}

std::string Text::getLabelID()
{
	return m_labelID;
}

bool Text::getDynamic()
{
	return m_dynamic;
}

void Text::setHidden(bool hidden)
{
	m_hidden = hidden;
}

ColorsConsts::Color Text::getFontColor()
{
	return m_fontColor;
}

void Text::setFontColor(ColorsConsts::Color fontColor)
{
	m_fontColor = fontColor;
}

void Text::updateWidth()
{
	m_width = m_message.length() * m_characterWidth;
}

void Text::centerText()
{
	if (!m_isCentered)
	{
		updateWidth();
		m_position.setX(m_position.getX() - 0.5 * m_width);
		m_isCentered = true;
	}
}

void Text::loadTexture()
{
	TheTrueTypeManager::Instance()->load(m_textureID, m_message,
		TheGame::Instance()->getFont(), TheGame::Instance()->getFontOutline(),
		{ m_fontColor.r, m_fontColor.g, m_fontColor.b },
		{ m_fontOutlineColor.r, m_fontOutlineColor.g, m_fontOutlineColor.b },
		TheGame::Instance()->getRenderer());
}

std::unique_ptr<GameObject> TextCreator::create() const
{
	return std::make_unique<Text>();
}
