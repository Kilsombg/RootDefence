#ifndef __MapMenuButton__
#define __MapMenuButton__

#include "MenuButton.h"

#include "../UtilsHeaders/BaseCreator.h"

#include<string>
#include<functional>

typedef std::function<void(std::string)> MapMenuButtonCallback;

class MapMenuButton : public MenuButton
{
public:
	MapMenuButton();
	MapMenuButton(const MapMenuButton* mapMenuButton);

	void update() override;
	void draw() override;
	void load(const std::shared_ptr<LoaderParams> pParams) override;

	void setCallback(MapMenuButtonCallback callback);

private:
	void handleClickOnButton() override;

	MapMenuButtonCallback m_callback;

	std::string m_mapLevelFileName; // name of map file
	
	bool m_mouseOver;
};


class MapMenuButtonCreator : public BaseCreator
{
public:
	std::unique_ptr<GameObject> create() const override;
};

#endif // !__MapMenuButton__
