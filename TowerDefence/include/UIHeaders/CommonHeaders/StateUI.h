#ifndef __StateUI__
#define __StateUI__

#include "../CommonHeaders/Panel.h"

#include<string>
#include<vector>
#include<memory>

class BaseStateUI 
{
public:
	virtual void draw() = 0;
	virtual void load() = 0;
	virtual void handleEvents() = 0;

	virtual void clean() = 0;

protected:
	std::string s_stateID;
	std::vector<std::string> m_textureIDList;
};
	

class StateUI : public BaseStateUI
{
public:
	StateUI(std::string stateID);

protected:
	std::vector<std::unique_ptr<Panel>> m_panels;
};

#endif // !__StateUI__
