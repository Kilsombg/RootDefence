#ifndef __LevelUpPanel__
#define __LevelUpPanel__

#include "../CommonHeaders/InteractivePanel.h"
#include "../CommonHeaders/PanelCreator.h"

#include "../../EntitiesHeaders/Texture.h"

#include "../../UtilsHeaders/Vector2D.h"

#include<memory>

/**
* Panel showing level up reward.
*/
class LevelUpPanel : public MenuInteractivePanel
{
public:
	LevelUpPanel();

	void draw() override;
	void update() override;
	void clean() override;
	void handleEvents() override;

	void load(std::vector<std::unique_ptr<GameObject>> gameObjects) override;
	void loadCallbacks() override;

	// getters and setters

	/**
	* set tower unlocked.
	* If there is no tower unlocked at this level doesn't do anything.
	*/
	void setTowerUnlockID(std::string name);

private:
	// callback functions for menu items
	
	static void s_returnToPlay();
	/**
	* When player clicks outside of panel then it closes panel.
	*/
	void handleClickOutside();
	/**
	* Load static labels.
	*/
	void loadStaticLabels();
	/**
	* Update panel move state.
	*/
	void updateMoveState();
	/**
	* Update Panel when state is set to exit.
	*/
	void updateExitMoveState();
	/**
	* Move panel to point.
	*/
	void movePanel(Vector2D targetPoint, int speed);
	/**
	* Calculates velocity for object moving in Panel.
	*/
	Vector2D calculateVelocity(Vector2D targetPoint, int speed);
	/**
	* Create tower unlock texture from textureID.
	*/
	void createTowerUnlockedTexture(std::string textureID, int width, int height);
	void createTowerUnklockLabel(std::string message);

	/**
	* represents the way it is moving.
	* If EXIT then it is preparing for clearing.
	*/
	enum moveState
	{
		IDLE = 1,
		DOWN = 2,
		UP = 3,
		EXIT = 4
	};

	static moveState s_moveState;
	std::unique_ptr<Texture> m_towerUnlockedTexture; // texture of tower unlocked. It could be nullptr.
	bool m_clickedInside;
};


class LevelUpPanelCreator : public PanelCreator
{
	virtual std::unique_ptr<Panel> create() const;
};

#endif // !__LevelUpPanel__
