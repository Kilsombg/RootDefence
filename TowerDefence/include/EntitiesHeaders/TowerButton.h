#ifndef __TowerButton__
#define __TowerButton__

#include "Button.h"
#include "../UtilsHeaders/BaseCreator.h"

#include "../MapHeaders/Level.h"
#include "../MapHeaders/TileType.h"

#include<string>
#include<memory>
#include<functional>

class TowerButton : public Button
{
public:
	typedef std::function<void(Button*)> TowerButtonCallback;

	TowerButton();
	TowerButton(const TowerButton* towerButton);

	virtual void load(const std::shared_ptr<LoaderParams> pParams) override;
	void handleEvent() override;

	virtual void update() override;


	// setters and getters

	void setCallback(TowerButtonCallback callback);
	std::string getTowerName();
	std::string getTowerColor();
	bool isSelected();

	void setLevel(std::shared_ptr<Level> level);

private:
	void resetParams();
	void handleInterruptEvent();
	void handleOutsideCLick();
	void handleClickOnButton();

	// name of the tower that the button will create.
	std::string m_towerName;
	// color of the tower
	std::string m_towerColor;
	// selected flag used for dragging shadow object.
	bool m_selected;
	// flag for pressing button.
	bool m_pressed;
	// flag for mouse on free TowerTile. If true you can build tower on click.
	bool m_isMouseOnFreeTowerTile;
	// which type of tile the mouse is over
	TileType m_mouseOnTileType;
	// button callback.
	TowerButtonCallback m_callback;
	// pointer to level to setup m_isMouseOnFreeTowerTile flag.
	std::shared_ptr<Level> pLevel;
};

class TowerButtonCreator : public BaseCreator
{
public:
	std::unique_ptr<GameObject> create() const override;
};

#endif // !__TowerButton__
