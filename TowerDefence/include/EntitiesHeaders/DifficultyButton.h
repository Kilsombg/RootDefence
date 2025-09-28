#ifndef __DifficultyButton__
#define __DifficultyButton__

#include "MenuButton.h"

#include "../ManagersHeaders/DifficultyManager.h"

#include "../UtilsHeaders/BaseCreator.h"

#include<functional>

typedef std::function<void(Difficulty)> DifficultyButtonCallback;

/**
* DifficultyButton defines on which difficulty the user will play.
* 
* When declaring a button in external file, define its difficulty attribute there.
*/
class DifficultyButton : public MenuButton
{
public:
	DifficultyButton();
	DifficultyButton(const DifficultyButton* difficultyButton);

	void update() override;
	void draw() override;
	void load(const std::shared_ptr<LoaderParams> pParams) override;
	void clean() override;

	void setCallback(DifficultyButtonCallback callback);

private:
	void handleClickOnButton() override;

	Difficulty m_difficulty; // difficulty of the map
	DifficultyButtonCallback m_callback;
};

class DifficultyButtonCreator : public BaseCreator
{
public:
	std::unique_ptr<GameObject> create() const override;
};

#endif // !__DifficultyButton__
