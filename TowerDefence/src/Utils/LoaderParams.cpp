#include "../../include/UtilsHeaders/LoaderParams.h"

void to_json(json& j, const LoaderParams& params) {
	for (const auto& it : params.getAttributes()) {
		const std::string& key = it.first;
		const LoaderParams::AttributeVariant& value = it.second;

		if (const int* intVal = boost::get<int>(&value)) {
			j[key] = *intVal;
		}
		else if (const float* floatVal = boost::get<float>(&value)) {
			j[key] = *floatVal;
		}
		else if (const bool* boolVal = boost::get<bool>(&value)) {
			j[key] = *boolVal;
		}
		else if (const std::string* strVal = boost::get<std::string>(&value)) {
			j[key] = *strVal;
		}
	}
}

void from_json(const json& j, LoaderParams& params) {
	for (auto it = j.begin(); it != j.end(); ++it) {
		if (it->is_number_integer()) {
			params.setAttribute(it.key(), it->get<int>());
		}
		else if (it->is_number_float()) {
			params.setAttribute(it.key(), it->get<float>());
		}
		else if (it->is_boolean()) {
			params.setAttribute(it.key(), it->get<bool>());
		}
		else if (it->is_string()) {
			params.setAttribute(it.key(), it->get<std::string>());
		}
	}
}

void to_json(json& j, const std::map<std::string, std::shared_ptr<LoaderParams>>& data) {
	for (const auto& it : data) {
		if (it.second) {
			j[it.first] = *(it.second);
		}
	}
}

void from_json(const json& j, std::map<std::string, std::shared_ptr<LoaderParams>>& data) {
	for (auto it = j.begin(); it != j.end(); ++it) {
		auto params = std::make_shared<LoaderParams>();
		from_json(it.value(), *params);
		data[it.key()] = params;
	}
}