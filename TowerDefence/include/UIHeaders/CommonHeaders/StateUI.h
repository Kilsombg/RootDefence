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
	virtual void update() = 0;
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

	/**
	* draw panels
	*/
	virtual void draw() override;
	/**
	* update panels.
	*/
	virtual void update() override;
	/**
	* load data from state xml file.
	*/
	virtual void load() override;
	/**
	* clean state UI.
	*/
	virtual void clean() override;
	/**
	* handle buttons from interactive panels.
	*/
	virtual void handleEvents() override;

	/*
	* get a specific panel type in state UI.
	*/
	template <typename T>
	T* getPanel()
	{
		for (std::vector<std::unique_ptr<Panel>>::size_type i = 0; i < m_panels.size();i++)
		{
			if (T* panel = dynamic_cast<T*>(m_panels[i].get()))
			{
				return panel;
			}
		}

		return nullptr;
	};

protected:
	std::vector<std::unique_ptr<Panel>> m_panels;
};

#endif // !__StateUI__
