#ifndef __SellTowerButton__
#define __SellTowerButton__

#include "SelectedTowerButton.h"

#include "../UtilsHeaders/BaseCreator.h"

#include<functional>

/**
* Button for selling selected tower.
*/
class SellTowerButton : public SelectedTowerButton
{
public:
	SellTowerButton();

	void handleEvent() override;
	void update() override;
	void load(const std::shared_ptr<LoaderParams> pParams) override;

	typedef std::function<void(std::shared_ptr<Tower>)> SellTowerCallback;
	void setCallback(SellTowerCallback callback);

private:
	void handleOutsideCLick();
	void handleClickOnButton();

	bool m_selected;
	bool m_pressed;

	SellTowerCallback m_callback;
};


class SellTowerButtonCreator : public BaseCreator
{
	std::unique_ptr<GameObject> create() const override;
};

#endif // !__SellTowerButton__
