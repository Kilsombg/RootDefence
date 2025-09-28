#ifndef __DifficultyManager__
#define __DifficultyManager__

#include<string>	
#include<memory>
#include<array>

/**
* Represents game difficulty.
*/
enum Difficulty
{
	EASY = 0,
	NORMAL = 1,
	HARD = 2
};

#define DIFFICULTY_COUNT HARD+1

namespace DifficultyConsts
{
	constexpr char difficultyEasyStr[] = "EASY";
	constexpr char difficultyNormalStr[] = "NORMAL";
	constexpr char difficultyHardStr[] = "HARD";
}

Difficulty getDifficultyByString(std::string difficultryStr);


/**
* Manages game difficulties.
* 
* Needs to outlive PlayState.
*/
class DifficultyManager
{
public:
	static std::shared_ptr<DifficultyManager> Instance();

	void clean();

	void setDifficulty(Difficulty difficulty);

	// getters

	float getTowerPriceMultiplayer();
	float getGameExperienceMultiplayer();
	int getGameHealthPoints();

private:
	DifficultyManager();
	static std::shared_ptr<DifficultyManager> s_pInstance;

	void loadData();

	Difficulty m_currentDifficulty;

	std::array<float, DIFFICULTY_COUNT> m_towerPriceMultiplayers; // tower cost and upgrades multiplayer
	std::array<float, DIFFICULTY_COUNT> m_gameExperienceMultiplayers; // XP multiplayer
	std::array<int, DIFFICULTY_COUNT> m_gameHealthPoints; // game health points
};

typedef DifficultyManager TheDifficultyManager;

#endif // !__DifficultyManager__
