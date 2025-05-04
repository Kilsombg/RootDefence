#ifndef __TowerButton__
#define __TowerButton__

#include "Button.h"
#include "../UtilsHeaders/BaseCreator.h"

#include "../MapHeaders/Level.h"

#include<string>
#include<memory>
#include<functional>

class TowerButton : public Button
{
public:
	typedef std::function<void(Button*)> TowerButtonCallback;

	TowerButton();

	virtual void load(const std::shared_ptr<LoaderParams> pParams) override;
	void handleEvent() override;

	virtual void update() override;

	void setCallback(TowerButtonCallback callback);
	std::string getTowerName();

	void setLevel(std::shared_ptr<Level> level);

private:
	void resetParams();
	void handleInterruptEvent();
	void handleOutsideCLick();
	void handleClickOnButton();

	std::string m_towerName;
	bool m_selected;
	bool m_pressed;
	bool m_isMouseOnFreeTowerTile;
	TowerButtonCallback m_callback;
	std::shared_ptr<Level> pLevel;
};

class TowerButtonCreator : public BaseCreator
{
public:
	std::unique_ptr<GameObject> createGameObject() const;
};

#endif // !__TowerButton__
