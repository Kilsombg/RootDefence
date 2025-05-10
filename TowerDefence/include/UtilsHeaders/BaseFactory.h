#ifndef __BaseFactory__
#define __BaseFactory__

#include<map>
#include<memory>
#include<string>
#include<iostream>

template <typename TObject ,typename TCreator>
class BaseFactory
{
public:
	bool registerType(std::string typeID, std::shared_ptr<TCreator> pCreator);
	std::unique_ptr<TObject> create(std::string typeID);

private:
	std::map<std::string, std::shared_ptr<TCreator>> m_creators;
};


template <typename TObject, typename TCreator>
inline bool BaseFactory<TObject, TCreator>::registerType(std::string typeID, std::shared_ptr<TCreator> pCreator)
{
	//std::map<std::string, std::shared_ptr<TCeator>>::iterator it = m_creators.find(typeID);
	auto it = m_creators.find(typeID);

	// if the type is already registered, do nothing
	if (it != m_creators.end())
	{
		return false;
	}

	m_creators[typeID] = pCreator;
	return true;
}

template <typename TObject, typename TCreator>
inline std::unique_ptr<TObject> BaseFactory<TObject, TCreator>::create(std::string typeID)
{
	//std::map<std::string, std::shared_ptr<TCreator>>::iterator it = m_creators.find(typeID);
	auto it = m_creators.find(typeID);

	//If the type is not already registered
	if (it == m_creators.end())
	{
		std::cout << "could not find type: " << typeID << "\n";
		return NULL;
	}

	std::shared_ptr<TCreator> pCreator = it->second;
	return pCreator->create();
}


#endif // !__BaseFactory__