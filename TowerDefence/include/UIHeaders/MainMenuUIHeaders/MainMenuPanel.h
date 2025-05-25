#ifndef __MainMenuPanel__
#define __MainMenuPanel__

#include "../CommonHeaders/InteractivePanel.h"
#include "../CommonHeaders/PanelCreator.h"

class MainMenuPanel : public MenuInteractivePanel
{
public:
	MainMenuPanel();

	void draw() override;
	void update() override;
	void clean() override;
	void handleEvents() override;

	void load(std::vector<std::unique_ptr<GameObject>> gameObjects) override;
	void loadCallbacks() override;

	// getters and setters

	static void s_setActivePanel(bool activeFlag);

private:
	// callback functions for menu items
	static void s_exitFromMenu();

	static bool s_active;
};


class MainMenuPanelCreator : public PanelCreator
{
	virtual std::unique_ptr<Panel> create() const;
};

#endif // !__MainMenuPanel__