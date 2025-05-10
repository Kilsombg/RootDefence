#include "../../include/EntitiesHeaders/Text.h"

#include "../../include/Game.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/UtilsHeaders/TrueTypeManager.h"

Text::Text() : GameObject()
{
}

Text::Text(float x, float y, int width, int height, std::string id, std::string message)
{
	m_position = Vector2D(x, y);
	m_width = width;
	m_height = height;
	m_textureID = id;
	m_message = message;
	m_prevMessage = message;

	loadTexture();
}

void Text::draw()
{
	TheTrueTypeManager::Instance()->drawText(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, TheGame::Instance()->getRenderer());
}

void Text::update()
{
	// there is some change
	if (m_message != m_prevMessage)
	{
		loadTexture();
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
	m_width = pParams->getAttribute<int>(LoaderParamsConsts::width);
	m_height = pParams->getAttribute<int>(LoaderParamsConsts::height);
	m_textureID = pParams->getAttribute<std::string>(LoaderParamsConsts::textureID);
	m_message = pParams->getAttribute<std::string>(LoaderParamsConsts::message);
	m_prevMessage = m_message;

	loadTexture();
}

void Text::setMessage(std::string message)
{
	m_message = message;
}

void Text::loadTexture()
{
	TheTrueTypeManager::Instance()->load(m_textureID, m_message, TheGame::Instance()->getFont(), { 0,0,0 }, TheGame::Instance()->getRenderer());
}

std::unique_ptr<GameObject> TextCreator::create() const
{
	return std::make_unique<Text>();
}
