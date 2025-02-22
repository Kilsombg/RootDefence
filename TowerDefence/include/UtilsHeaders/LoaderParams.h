#ifndef __LoaderParams__
#define __LoaderParams__

#include<string>
#include<boost/variant.hpp>
#include<unordered_map>
#include<iostream>

#include<nlohmann\json.hpp>
using json = nlohmann::json;

class LoaderParams
{
public:
	using AttributeVariant = boost::variant<int, float, std::string>;

	template <typename T>
	void setAttribute(const std::string& key, T value) {
		m_attributes[key] = value;
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

	const std::unordered_map<std::string, AttributeVariant>& getAttributes() const {
		return m_attributes;
	}

private:
	std::unordered_map<std::string, AttributeVariant> m_attributes;
};

void to_json(json& j, const LoaderParams& params);
void from_json(const json& j, LoaderParams& params);

void to_json(json& j, const std::map<std::string, std::shared_ptr<LoaderParams>>& data);
void from_json(const json & j, std::map<std::string, std::shared_ptr<LoaderParams>>&data);

#endif // !__LoaderParams__"