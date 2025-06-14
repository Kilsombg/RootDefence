#ifndef __MapMenuButton__
#define __MapMenuButton__

#include "MenuButton.h"
#include "Text.h"

#include "../UtilsHeaders/BaseCreator.h"

#include<string>
#include<functional>

typedef std::function<void(std::string, int)> MapMenuButtonCallback;

/**
* Class for choosing a map in mapMenuPanel.
*/
class MapMenuButton : public MenuButton
{
public:
	MapMenuButton();
	MapMenuButton(const MapMenuButton* mapMenuButton);

	void update() override;
	void draw() override;
	void load(const std::shared_ptr<LoaderParams> pParams) override;
	void clean() override;

	void setCallback(MapMenuButtonCallback callback);

private:
	void handleClickOnButton() override;
	/**
	* Update best wave achieved label on button.
	*/
	void updateMaxWaveLabel();
	/**
	* Load a text label for map name.
	*/
	void loadMapLabel(std::string name);
	/**
	* Load a text label for max wave.
	*/
	void loadMaxWaveLabel();
	/**
	* gets id of map.
	* 
	* @return id from states xml decremented.
	*/
	int getID();
	/**
	* helper method for creating mapName's text id
	*/
	std::string generateMapTextIDWithSuffix(std::string suffix);

	MapMenuButtonCallback m_callback;

	std::string m_mapLevelFileName; // name of map file
	std::string m_mapName; // name of map
	std::shared_ptr<Text> m_mapNameText; // label for map's name
	std::shared_ptr<Text> m_maxWaveText; // label for map's max wave

	bool m_mouseOver;
};


class MapMenuButtonCreator : public BaseCreator
{
public:
	std::unique_ptr<GameObject> create() const override;
};

#endif // !__MapMenuButton__
