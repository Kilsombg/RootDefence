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

	virtual void update();

	virtual void load(const std::shared_ptr<LoaderParams> pParams);

	void setCallback(void(*callback)());

private:
	void (*m_callback)();
};

class MenuButtonCreator : public BaseCreator
{
public:
	std::unique_ptr<GameObject> createGameObject() const;
};

#endif // !__MenuButton__
