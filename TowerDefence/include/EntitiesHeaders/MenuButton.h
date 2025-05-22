#ifndef __MenuButton__
#define __MenuButton__

#include "../UtilsHeaders/BaseCreator.h"

#include "Button.h"

#include<string>
#include<memory>

enum MenuMode
{
	ACTIVE = 1,
	DISABLED = 2
};

class MenuButton : public Button
{
public:
	MenuButton();
	MenuButton(const MenuButton* menuButton);

	virtual void update();

	virtual void load(const std::shared_ptr<LoaderParams> pParams) override;
	virtual void handleEvent() override;

	// getters and setters

	void setCallback(void(*callback)());

	void setCurrentRow(int currentRow);

private:
	void handleOutsideCLick();
	void handleClickOnButton();
	void (*m_callback)();
};

class MenuButtonCreator : public BaseCreator
{
public:
	std::unique_ptr<GameObject> create() const override;
};

#endif // !__MenuButton__
