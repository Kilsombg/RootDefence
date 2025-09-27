#include "../../include/EntitiesHeaders/DifficultyButton.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/UtilsHeaders/InputHandler.h"

DifficultyButton::DifficultyButton() : MenuButton()
{
}

DifficultyButton::DifficultyButton(const DifficultyButton* difficultyButton) : MenuButton(difficultyButton)
{
	m_difficulty = difficultyButton->m_difficulty;
	m_callback = difficultyButton->m_callback;
}

void DifficultyButton::update()
{
	MenuButton::update();
}

void DifficultyButton::draw()
{
	// draw button
	MenuButton::draw();
}

void DifficultyButton::load(const std::shared_ptr<LoaderParams> pParams)
{
	MenuButton::load(pParams);

	m_difficulty = getDifficultyByString(pParams->getAttribute<std::string>(LoaderParamsConsts::difficulty));
}

void DifficultyButton::clean()
{
	// clean button
	MenuButton::clean();
}

void DifficultyButton::setCallback(DifficultyButtonCallback callback)
{
	m_callback = callback;
}

void DifficultyButton::handleClickOnButton()
{
	if (m_isMouseOnButton && !m_pressedOutside)
	{
		m_currentFrame = MOUSE_OVER;

		if (!TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			m_currentFrame = CLICKED;

			m_callback(m_difficulty);

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

		m_currentFrame = MOUSE_OUT;
	}
}

std::unique_ptr<GameObject> DifficultyButtonCreator::create() const
{
	return std::make_unique<DifficultyButton>();
}

Difficulty getDifficultyByString(std::string difficultryStr)
{
	if (!difficultryStr.compare(DifficultyConsts::difficultyEasyStr))
		return EASY;

	if (!difficultryStr.compare(DifficultyConsts::difficultyNormalStr))
		return NORMAL;

	if (!difficultryStr.compare(DifficultyConsts::difficultyHardStr))
		return HARD;


	// erorr
	return Difficulty();
}
