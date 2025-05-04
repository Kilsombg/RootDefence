#ifndef __TowerUpgradedButton__
#define __TowerUpgradedButton__

#include "Button.h"
#include "Tower.h"

#include "../UtilsHeaders/BaseCreator.h"

#include<functional>

class TowerUpgradedButton : public Button
{
public:
	TowerUpgradedButton();

	void handleEvent() override;

	typedef std::function<void(Tower&)> TowerUpgradedCallback;

	void setCallback(TowerUpgradedCallback callback);

private:
	void handleClickOnButton();

	TowerUpgradedCallback m_callback;
	Tower* m_selectedTower;
};


class TowerUpgradedButtonCreator : public BaseCreator
{
	std::unique_ptr<GameObject> createGameObject() const;
};

#endif // !__TowerUpgradedButton__
