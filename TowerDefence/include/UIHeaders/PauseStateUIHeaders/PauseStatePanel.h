#ifndef __PauseStatePanel__
#define __PauseStatePanel__

#include "../CommonHeaders/InteractivePanel.h"
#include "../CommonHeaders/PanelCreator.h"

/**
* Panel for PauseStateUI.
* 
* Here you can switch to MainMenu or Play states.
*/
class PauseStatePanel : public MenuInteractivePanel
{
public:
	PauseStatePanel();

	void draw() override;
	void update() override;
	void clean() override;
	void handleEvents() override;

	void load(std::vector<std::unique_ptr<GameObject>> gameObjects) override;
	void loadCallbacks() override;

private:
	static void s_pauseToMain();
	static void s_restartPlay();
	static void s_resumePlay();
};


class PauseStatePanelCreator : public PanelCreator
{
	std::unique_ptr<Panel> create() const override;
};

#endif // !__PauseStatePanel__
