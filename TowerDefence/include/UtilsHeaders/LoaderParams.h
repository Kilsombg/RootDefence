#ifndef __LoaderParams__
#define __LoaderParams__

#include<string>
#include<boost/variant.hpp>
#include<unordered_map>
#include<iostream>

class LoaderParams
{
public:
	template <typename T>
	void setAttribute(const std::string& key, T value) {
		m_attributes[key] = static_cast<T>(value);
	}

	template <>
	void setAttribute(const std::string& key, std::string value) {
		m_attributes[key] = std::string(value);
	}

	template <typename T>
	T getAttribute(const std::string& key) const {
		try
		{
			T value = boost::get<T>(m_attributes.at(key));
			return value;
		}
		catch (const boost::bad_get& e) {
			std::cerr << "Error: " << e.what() << '\n';
			return NULL;
		}
	}


private:
	using AttributeVariant = boost::variant<int, float, std::string>;
	std::unordered_map<std::string, AttributeVariant> m_attributes;
};

#endif // !__LoaderParams__