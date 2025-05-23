#ifndef __GameOverStatePanel__
#define __GameOverStatePanel__

#include "../CommonHeaders/InteractivePanel.h"
#include "../CommonHeaders/PanelCreator.h"

#include "../../EntitiesHeaders/Text.h"


class GameOverStatePanel : public MenuInteractivePanel
{
public:
	GameOverStatePanel();

	void draw() override;
	void update() override;
	void clean() override;
	void handleEvents() override;

	void load(std::vector<std::unique_ptr<GameObject>> gameObjects) override;
	void loadCallbacks() override;

	void setCurrentWaveID(int currentWaveID);

private:
	static void s_gameOverToMain();
	static void s_restartPlay();

	/**
	* update dynamic labels' value.
	*/
	void updateDynamicLabel();

	int m_currentWaveID;
};


class GameOverStatePanelCreator : public PanelCreator
{
	std::unique_ptr<Panel> create() const override;
};

#endif // !__GameOverStatePanel__
