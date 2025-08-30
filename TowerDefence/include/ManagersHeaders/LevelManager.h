#ifndef __LevelManager__
#define __LevelManager__

#include "../DataHeaders/DTOsHeaders/GameProgressDTO.h"
#include<memory>

/**
* Manage levels. 
* 
* Use LevelManager to update user level and experience.
*/
class LevelManager
{
public:
	static std::shared_ptr<LevelManager> Instance();

	/**
	* add enemy experience.
	*/
	void addExperience(int exp);

	// getters and setters

	long getNextLevelXP();

	/**
	* clean after using it.
	*/
	void clean();

private:
	static std::shared_ptr<LevelManager> s_pInstance;
	LevelManager();

	/**
	* Get experience needed to level up.
	* 
	* If returns -1, then there is something wrong with gameProgress or hitted max level
	*/
	long getLevelMaxExp();
	/**
	* Calls this when player level up.
	*/
	void levelUp(int currentXP);
	/**
	* xp needed to level up;
	*/
	long m_nextLevelXP;

	std::shared_ptr<GameProgressDTO> m_gameProgress;
	int maxLvl = 20;
};

typedef LevelManager TheLevelManager;

#endif // !__LevelManager__
