#ifndef __TipsPanel__
#define __TipsPanel__

#include "../CommonHeaders/Panel.h"
#include "../CommonHeaders/PanelCreator.h"

#include "../../UtilsHeaders/Timer.h"

#include<vector>
#include<string>

class TipsPanel : public Panel
{
public:
	TipsPanel();

	void draw() override;
	void update() override;
	void clean() override;
	void load(std::vector<std::unique_ptr<GameObject>> gameObjects) override;

private:
	/**
	* update the tip that is showing on screen.
	*/
	void updateTipOnScreen();
	/**
	* update dynamic labels' value.
	*/
	void updateDynamicLabel();
	/**
	* load all tips.
	*/
	void loadTips();

	// id of current tip.
	int m_currentTipID;
	std::vector<std::string> m_tips;
	// timer for rotating tips.
	Timer m_tipsTimer;
};


class TipsPanelCreator : public PanelCreator
{
	std::unique_ptr<Panel> create() const override;
};

#endif // !__TipsPanel__
