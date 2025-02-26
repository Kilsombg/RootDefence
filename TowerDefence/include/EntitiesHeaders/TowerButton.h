#ifndef __TowerButton__
#define __TowerButton__

#include "Button.h"
#include "../UtilsHeaders/BaseCreator.h"

#include<string>
#include<memory>
#include<functional>

class TowerButton : public Button
{
public:
	typedef std::function<void(Button*)> TowerButtonCallback;

	TowerButton();

	virtual void load(const std::shared_ptr<LoaderParams> pParams);

	virtual void update();

	void setCallback(TowerButtonCallback callback);
	std::string getTowerName();

private:
	void handleEvent();

	std::string m_towerName;
	bool m_selected;
	TowerButtonCallback m_callback;
};

class TowerButtonCreator : public BaseCreator
{
public:
	std::unique_ptr<GameObject> createGameObject() const;
};

#endif // !__TowerButton__
