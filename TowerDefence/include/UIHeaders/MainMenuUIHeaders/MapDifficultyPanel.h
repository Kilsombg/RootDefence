#ifndef __MapDifficultyPanel__
#define __MapDifficultyPanel__

#include "../CommonHeaders/InteractivePanel.h"
#include "../CommonHeaders/PanelCreator.h"

#include "../../EntitiesHeaders/DifficultyButton.h"

struct MapDetail;

/**
* Panel for choosing game difficulty.
* 
* When closing this Panel, MapsPanel opens.
*/
class MapDifficultyPanel : public MenuInteractivePanel
{
public:
	MapDifficultyPanel();

	void draw() override;
	void update() override;
	void clean() override;
	void handleEvents() override;

	void load(std::vector<std::unique_ptr<GameObject>> gameObjects) override;
	void loadCallbacks() override;

	/**
	* callback function for mapsPanel.
	*/

	static void s_activatePanel();

	static void s_setMapDetail(MapDetail mapDetail);

private:
	// Callbacks functions

	/**
	* callback function for closing panel.
	*
	* When closing MapDifficultyPanel, MapsPanel opens.
	*/
	static void s_closePanel();
	/**
	* Callback method for changing to PlayState with chosen difficulty.
	*/
	void mainMenuToPlay(Difficulty difficulty);

	virtual void setCallbacks() override;

	static bool s_active;

	static MapDetail s_mapDetail;

	std::map<std::string, DifficultyButtonCallback> m_mapMenuButtonCallbacs; // callback map for difficulty buttons
};

class MapDifficultyPanelCreator : public PanelCreator
{
	virtual std::unique_ptr<Panel> create() const override;
};

#endif // !__MapDifficultyPanel__
