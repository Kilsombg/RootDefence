#ifndef __MenuButton__
#define __MenuButton__

#include "../UtilsHeaders/BaseCreator.h"

#include "Button.h"

#include<memory>

/**
* State of the button.
*/
enum MenuMode
{
	ACTIVE = 1,
	DISABLED = 2
};

/**
* Button with static callback that has not have parameters.
*/
class MenuButton : public Button
{
public:
	MenuButton();
	MenuButton(const MenuButton* menuButton);

	virtual void update() override;

	virtual void load(const std::shared_ptr<LoaderParams> pParams) override;
	virtual void handleEvent() override;

	// getters and setters

	void setCallback(void(*callback)());
	
	/**
	* Change texture based on button's MenuMode.
	*/
	void setCurrentRow(int currentRow);


protected:
	virtual void handleClickOnButton();


private:
	void handleOutsideCLick();
	void (*m_callback)();
};

class MenuButtonCreator : public BaseCreator
{
public:
	std::unique_ptr<GameObject> create() const override;
};

#endif // !__MenuButton__
