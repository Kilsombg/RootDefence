#include "../../include/ManagersHeaders/DifficultyManager.h"


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


std::shared_ptr<DifficultyManager> DifficultyManager::s_pInstance = nullptr;

std::shared_ptr<DifficultyManager> DifficultyManager::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = std::shared_ptr<DifficultyManager>(new DifficultyManager);
		return s_pInstance;
	}
	return s_pInstance;
}

void DifficultyManager::clean()
{
	s_pInstance = nullptr;
}

void DifficultyManager::setDifficulty(Difficulty difficulty)
{
	m_currentDifficulty = difficulty;
}

float DifficultyManager::getTowerPriceMultiplayer()
{
	return m_towerPriceMultiplayers[m_currentDifficulty];
}

float DifficultyManager::getGameExperienceMultiplayer()
{
	return m_gameExperienceMultiplayers[m_currentDifficulty];
}

int DifficultyManager::getGameHealthPoints()
{
	return m_gameHealthPoints[m_currentDifficulty];
}

DifficultyManager::DifficultyManager() : m_currentDifficulty(EASY)
{
	loadData();
}

void DifficultyManager::loadData()
{
	// tower cost and upgrades multiplayer
	m_towerPriceMultiplayers = {0.75f, 1.0f, 1.25f};

	// XP multiplayer
	m_gameExperienceMultiplayers = {1.0f, 1.10f, 1.20f};

	// game health points
	m_gameHealthPoints = {10, 5, 1};
}
