#ifndef __TowerButton__
#define __TowerButton__

#include "Button.h"
#include "Text.h"
#include "Texture.h"

#include "../UtilsHeaders/BaseCreator.h"

#include "../MapHeaders/Level.h"

#include<string>
#include<memory>
#include<functional>

/**
* Button for buying towers.
*/
class TowerButton : public Button
{
public:
	typedef std::function<void(Button*)> TowerButtonCallback;

	TowerButton();
	TowerButton(const TowerButton* towerButton);

	virtual void load(const std::shared_ptr<LoaderParams> pParams) override;
	void handleEvent() override;

	virtual void update() override;
	virtual void draw() override;
	virtual void clean() override;

	/**
	* set mouse position to dummy object
	*/
	void setDummyObjectPosition();


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

	/**
	* Create cost resource texture in load().
	*/
	void loadCostResourceTexture();
	/**
	* Create lock texture in load().
	*/
	void loadLockTexture();
	/**
	* Create cost value label in load().
	*/
	void loadCostValueLabel(std::string value);

	// name of the tower that the button will create.
	std::string m_towerName;
	// color of the tower
	std::string m_towerColor;
	// gets needed tower's position and widht, height.
	std::shared_ptr<LoaderParams> m_towerParams;
	// dummy object representing position of the tower
	std::shared_ptr<SDLGameObject> m_dummyObject;
	// selected flag used for dragging shadow object.
	bool m_selected;
	// flag for pressing button.
	bool m_pressed;
	// flag for mouse on free TowerTile. If true you can build tower on click.
	bool m_isMouseOnFreeTowerTile;
	// flag for checking if outside map to interrupt the button if clicked while selected.
	bool m_isMouseOutsideMap;
	// flag for texture.
	bool m_disabled;
	// flag for unlocked tower.
	bool m_unlocked;
	// base textureID of button without modification (disabled).
	std::string m_baseTextureID;
	// tower name with color type included.
	std::string m_towerNameID;
	// tower button cost label.
	std::unique_ptr<Text> m_costLabel;
	// tower button cost texture.
	std::unique_ptr<Texture> m_costResourceTexture;
	// tower lock texture.
	std::unique_ptr<Texture> m_lockTexture;
	// button callback.
	TowerButtonCallback m_callback;
	// pointer to level.
	std::shared_ptr<Level> pLevel;
};

class TowerButtonCreator : public BaseCreator
{
public:
	std::unique_ptr<GameObject> create() const override;
};

#endif // !__TowerButton__
