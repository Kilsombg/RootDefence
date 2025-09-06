#include "../../include/ManagersHeaders/LevelManager.h"

#include "../../include/Game.h"

#include "../../include/GameStateHeaders/LevelUpState.h"

#include "../../include/UtilsHeaders/GameStateMachine.h"

#include<ostream>

std::shared_ptr<LevelManager> LevelManager::s_pInstance = nullptr;

void LevelManager::clean()
{
	m_gameProgress = nullptr;
	s_pInstance = nullptr;
}

LevelManager::LevelManager()
{
	m_gameProgress = TheGame::Instance()->getProgressManager()->getGameProgress();

	m_nextLevelXP = getLevelMaxExp();
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

void LevelManager::addExperience(int exp)
{
	if (m_gameProgress->level > maxLvl) return;

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

long LevelManager::getNextLevelXP()
{
	return m_nextLevelXP;
}

long LevelManager::getLevelMaxExp()
{
	if (!m_gameProgress.use_count()) return -1;

	int lvl = m_gameProgress->level;
	if (lvl > maxLvl) return -1;

	if (lvl <= 2) return lvl * 300;

	// arithm. progression
	int a1 = 50, d=1;

	if (lvl <= 10) d = 100;
	else if (10 <= lvl <= 20) d = 150;

	return 10 * (a1 + (lvl - 1) * d);
}

void LevelManager::levelUp(int currentXP)
{
	// update XP
	TheGame::Instance()->getProgressManager()->updateLoadedLevel(1, currentXP - m_nextLevelXP, m_gameProgress->level + 1);
	m_nextLevelXP = getLevelMaxExp();

	// get reward
	std::string towerUnlockedID = TheGame::Instance()->getTowerUnlockManager()->unlockTowerByLevelUp();

	// change state
	auto pState = std::make_shared<LevelUpState>();
	pState->setTowerUnlockedID(towerUnlockedID);
	TheGameStateMachine::Instance()->pushState(pState);
}
