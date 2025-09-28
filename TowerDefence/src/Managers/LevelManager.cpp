#include "../../include/ManagersHeaders/LevelManager.h"

#include "../../include/Game.h"

#include "../../include/GameStateHeaders/LevelUpState.h"

#include "../../include/ManagersHeaders/DifficultyManager.h"

#include "../../include/UtilsHeaders/GameStateMachine.h"
#include "../../include/UtilsHeaders/TextureManager.h"

#include<ostream>

std::shared_ptr<LevelManager> LevelManager::s_pInstance = nullptr;

void LevelManager::clean()
{
	m_gameProgress = nullptr;
	s_pInstance = nullptr;

	if (m_maxLvlLabel)
	{
		delete m_maxLvlLabel;
		m_maxLvlLabel = nullptr;
	}
}

void LevelManager::reset()
{
	m_nextLevelXP = getLevelMaxExp();

	if (m_maxLvlLabel)
	{
		delete m_maxLvlLabel;
		m_maxLvlLabel = nullptr;
	}
}

LevelManager::LevelManager()
{
	m_gameProgress = TheGame::Instance()->getProgressManager()->getGameProgress();

	m_nextLevelXP = getLevelMaxExp();
	m_lvlProgressRect = SDL_Rect{ 60, 23, 77, 17 };
	if (m_gameProgress->level >= maxLvl) setMaxLevelLabel();
}

std::shared_ptr<LevelManager> LevelManager::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = std::shared_ptr<LevelManager>(new LevelManager);
		return s_pInstance;
	}
	return s_pInstance;
}

void LevelManager::addEnemyExperience(int exp)
{
	float diffMulti = TheDifficultyManager::Instance()->getGameExperienceMultiplayer();
	int actualXP = std::floor(exp * diffMulti);
	addExperience(actualXP);
}

void LevelManager::addExperience(int exp)
{
	if (m_gameProgress->level >= maxLvl) return;

	long currentXP = m_gameProgress->level_xp + exp;

	// if m_nextLevelXP is -1, then something worng with gameProgress or hitted max level
	if (currentXP >= m_nextLevelXP && m_nextLevelXP != -1)
	{
		levelUp(currentXP);
	}
	else
	{
		TheGame::Instance()->getProgressManager()->updateLoadedLevel(1, currentXP, m_gameProgress->level);
	}
}

void LevelManager::drawLevelProgressBar()
{
	float progress = m_nextLevelXP == -1 ? 1 : (float)m_gameProgress->level_xp / m_nextLevelXP;

	// draw level progress bar
	TheTextureManager::Instance()->drawProgressBar(
		m_lvlProgressRect.x, m_lvlProgressRect.y, m_lvlProgressRect.w, m_lvlProgressRect.h,
		{ ColorsConsts::levelBG.r, ColorsConsts::levelBG.g, ColorsConsts::levelBG.b, ColorsConsts::levelBG.a },
		{ ColorsConsts::green.r, ColorsConsts::green.g, ColorsConsts::green.b, ColorsConsts::green.a },
		progress,
		TheGame::Instance()->getRenderer()
	);

	// draw max level label
	if (m_maxLvlLabel) m_maxLvlLabel->draw();
}

long LevelManager::getNextLevelXP()
{
	return m_nextLevelXP;
}

long LevelManager::getLevelMaxExp()
{
	if (!m_gameProgress.use_count()) return -1;

	int lvl = m_gameProgress->level;
	if (lvl >= maxLvl) return -1;

	if (lvl <= 2) return lvl * 300;

	// arithm. progression
	int a1 = 50, d = 1;

	if (lvl <= 10) d = 100;
	else if (10 <= lvl <= 20) d = 150;

	return 10 * (a1 + (lvl - 1) * d);
}

void LevelManager::levelUp(int currentXP)
{
	// update XP
	TheGame::Instance()->getProgressManager()->updateLoadedLevel(1, currentXP - m_nextLevelXP, m_gameProgress->level + 1);
	m_nextLevelXP = getLevelMaxExp();
	if (m_gameProgress->level >= maxLvl) setMaxLevelLabel();

	// get reward
	std::string towerUnlockedID = TheGame::Instance()->getTowerUnlockManager()->unlockTowerByLevelUp();

	// change state
	auto pState = std::make_shared<LevelUpState>();
	pState->setTowerUnlockedID(towerUnlockedID);
	TheGameStateMachine::Instance()->pushState(pState);
}

void LevelManager::setMaxLevelLabel()
{
	if (!m_maxLvlLabel)
	{
		std::string textureID = "maxLvlLabelID";
		std::string message = "max  level";
		m_maxLvlLabel = new Text(m_lvlProgressRect.x + 7, m_lvlProgressRect.y + 5, 6, 10, textureID, textureID, message);
	}
}
