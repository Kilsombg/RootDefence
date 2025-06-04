#ifndef __DeleteProgressConfirmationPanel__
#define __DeleteProgressConfirmationPanel__

#include "../CommonHeaders/InteractivePanel.h"
#include "../CommonHeaders/PanelCreator.h"

class DeleteProgressConfirmationPanel : public MenuInteractivePanel
{
public:
	DeleteProgressConfirmationPanel();
	
	void draw() override;
	void update() override;
	void clean() override;
	void handleEvents() override;

	void load(std::vector<std::unique_ptr<GameObject>> gameObjects) override;
	void loadCallbacks() override;

	// getters and setters

	static void s_setActivePanel(bool activeFlag);

	/**
	* callback function for mainMenuPanel.
	*/
	static void s_activatePanel();

private:
	// callback function
	static void s_deleteProgress();

	static bool s_active;
};

class DeleteProgressConfirmationPanelCreator : public PanelCreator
{
	virtual std::unique_ptr<Panel> create() const;
};

#endif // !__DeleteProgressConfirmationPanel__
