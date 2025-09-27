#ifndef __MapsPanel__
#define __MapsPanel__

#include "../CommonHeaders/InteractivePanel.h"
#include "../CommonHeaders/PanelCreator.h"

#include "../../../include/EntitiesHeaders/MapMenuButton.h"

#include<string>
#include<map>

/**
* Main menu panel that shows all maps.
* 
* In that panel you can select map to play or get back to main menu screen.
*/
class MapsPanel : public MenuInteractivePanel
{
public:
	MapsPanel();

	void draw() override;
	void update() override;
	void clean() override;
	void handleEvents() override;

	void load(std::vector<std::unique_ptr<GameObject>> gameObjects) override;
	void loadCallbacks() override;

	/**
	* callback function for mainMenuPanel.
	*/
	static void s_activatePanel();
	/**
	* set active flag for MapsPanel.
	* 
	* Use this method from other panels to activate or deactivate MapsPanel.
	*/
	static void s_setActivePanel(bool activeFlag);

private:
	/**
	* callback function for closing panel.
	*/
	static void s_closePanel();

	void setCallbacks() override;
	/**
	* change state to playState with selected map.
	*/
	void mainMenuToPlay(std::string mapFileName, int mapID);

	std::map<std::string, MapMenuButtonCallback> m_mapMenuButtonCallbacs;

	static bool s_active;
};


class MapsPanelCreator : public PanelCreator
{
	virtual std::unique_ptr<Panel> create() const override;
};

#endif // !__MapsPanel__
