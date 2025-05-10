#ifndef __TowerUpgradedButton__
#define __TowerUpgradedButton__

#include "Button.h"
#include "Tower.h"

#include "../UtilsHeaders/BaseCreator.h"

#include<functional>
#include<memory>

class TowerUpgradedButton : public Button
{
public:
	TowerUpgradedButton();

	void handleEvent() override;
	void update() override;
	void load(const std::shared_ptr<LoaderParams> pParams) override;

	typedef std::function<void(std::shared_ptr<Tower>, int)> TowerUpgradedCallback;

	void setCallback(TowerUpgradedCallback callback);
	void setSelectedTower(std::shared_ptr<Tower> selectedTower);

private:
	void handleOutsideCLick();
	void handleClickOnButton();

	void resetParams();

	bool m_selected;
	bool m_pressed;

	int m_upgradeID; // 0 - first, 1 - second

	TowerUpgradedCallback m_callback;

	std::shared_ptr<Tower> m_selectedTower;
};


class TowerUpgradedButtonCreator : public BaseCreator
{
	std::unique_ptr<GameObject> create() const override;
};

#endif // !__TowerUpgradedButton__
