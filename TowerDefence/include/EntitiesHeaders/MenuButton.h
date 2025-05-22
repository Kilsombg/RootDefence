#ifndef __MenuButton__
#define __MenuButton__

#include "../UtilsHeaders/BaseCreator.h"

#include "Button.h"

#include<string>
#include<memory>

class MenuButton : public Button
{
public:

	MenuButton();
	MenuButton(const MenuButton* menuButton);

	virtual void update();

	virtual void load(const std::shared_ptr<LoaderParams> pParams) override;
	virtual void handleEvent() override;

	void setCallback(void(*callback)());

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
