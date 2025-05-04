#ifndef __TowerUpgradedButton__
#define __TowerUpgradedButton__

#include "Button.h"
#include "Tower.h"

#include<functional>

class TowerUpgradedButton : public Button
{
public:
	TowerUpgradedButton();

	typedef std::function<void(Tower&)> TowerUpgradedCallback;

	void setCallback(TowerUpgradedCallback callback);

private:
	TowerUpgradedCallback m_callback;
};

#endif // !__TowerUpgradedButton__
