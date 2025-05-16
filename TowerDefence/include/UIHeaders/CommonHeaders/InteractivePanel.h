#ifndef __InteractivePanel__
#define __InteractivePanel__

#include "Panel.h"

#include "../../EntitiesHeaders/Button.h"
#include "../../EntitiesHeaders/Tower.h"


#include<vector>
#include<memory>

/**
* base class for panels including buttons
*/
class InteractivePanel : public Panel
{
public:
	InteractivePanel();
	virtual void draw() override;
	virtual void update() override;
	virtual void handleEvents();

	void setButtonObjects(std::vector<std::shared_ptr<Button>> buttons);

	virtual void loadCallbacks();

protected:
	std::vector<std::shared_ptr<Button>> m_buttonObjects;
};



/**
* base class for panels including towers functionality
*/
class TowerInteractivePanel : public InteractivePanel
{
public:
	TowerInteractivePanel();
	virtual void setPlayStateTowers(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> playStateTowers);
		
protected:
	std::shared_ptr<std::vector<std::shared_ptr<Tower>>> m_playStateTowers;
};

#endif // !__InteractivePanel__
