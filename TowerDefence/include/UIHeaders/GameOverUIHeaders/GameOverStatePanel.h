#ifndef __GameOverStatePanel__
#define __GameOverStatePanel__

#include "../CommonHeaders/InteractivePanel.h"
#include "../CommonHeaders/PanelCreator.h"

/**
* Panel that is shown when gameOverState occurs.
* 
* It has logic for switching to others states and representing the panel on screen.
*/
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

	// getters and setters

	void setCurrentWaveID(int currentWaveID);

private:
	// static callbacks

	/**
	* Change state from gameOver to MainMenu.
	*/
	static void s_gameOverToMain();
	/**
	* Changes to new PlayState.
	*/
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
