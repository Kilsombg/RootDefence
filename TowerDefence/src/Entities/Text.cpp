#include "../../include/EntitiesHeaders/Text.h"

#include "../../include/Game.h"

#include "../../include/Constants/ColorsConsts.h"
#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/UtilsHeaders/TrueTypeManager.h"

Text::Text() : GameObject()
{
}

Text::Text(float x, float y,int characterWidth, int width, int height, std::string textureID, std::string labelID , std::string message, bool dynamic)
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

	loadTexture();
}

void Text::draw()
{
	TheTrueTypeManager::Instance()->drawText(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, TheGame::Instance()->getRenderer());
}

void Text::update()
{
	// if there is some change update texture
	if (m_message != m_prevMessage)
	{
		loadTexture();
		m_width = m_message.length() * m_characterWidth;
		m_prevMessage = m_message;
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

void Text::loadTexture()
{
	ColorsConsts::Color black = ColorsConsts::black;
	ColorsConsts::Color white = ColorsConsts::white;

	TheTrueTypeManager::Instance()->load(m_textureID, m_message, 
		TheGame::Instance()->getFont(), TheGame::Instance()->getFontOutline(), 
		{white.r, white.b, white.g},
		{black.r, black.b, black.g},
		TheGame::Instance()->getRenderer());
}

std::unique_ptr<GameObject> TextCreator::create() const
{
	return std::make_unique<Text>();
}
