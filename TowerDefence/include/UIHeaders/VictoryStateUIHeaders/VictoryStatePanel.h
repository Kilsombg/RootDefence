#ifndef __VictoryStatePanel__
#define __VictoryStatePanel__

#include "../CommonHeaders/InteractivePanel.h"
#include "../CommonHeaders/PanelCreator.h"

/**
* Panel for VictoryState UI.
* 
* In this panel are buttons for switching to other states.
*/
class VictoryStatePanel : public MenuInteractivePanel
{
public:
	VictoryStatePanel();

	void draw() override;
	void update() override;
	void clean() override;
	void handleEvents() override;

	void load(std::vector<std::unique_ptr<GameObject>> gameObjects) override;
	void loadCallbacks() override;

	// getters and setters

	void setRewardValue(int rewardValue);

private:
	static void s_victoryToMain();
	static void s_restartPlay();

	/**
	* update dynamic labels' value.
	*/
	void updateStaticLabel();

	int m_rewardValue;
};


class VictoryStatePanelCreator : public PanelCreator
{
	std::unique_ptr<Panel> create() const override;
};

#endif // !__VictoryStatePanel__
