// This project uses the JSON for Modern C++ library by Niels Lohmann
// https://github.com/nlohmann/json
// Licensed under the MIT License (see below)

/*Mit License
The class is licensed under the MIT License:

Copyright © 2013-2025 Niels Lohmann

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
IN THE SOFTWARE.
*/

#ifndef __NLJsonParser__
#define __NLJsonParser__

#include<iostream>
#include <fstream>
#include<nlohmann\json.hpp>

using json = nlohmann::json;

/*
* Generic json parser.
* Note: to_json() and from_json() MUST be in your type's namespace.
*/
template<typename T>
class NLJasonParser
{
public:
	template<typename T>
	static bool parseFromFile(const char* filePath, T& object, const std::string objectKey)
	{
		// open file
		std::ifstream ifs(filePath);

		if (!ifs.is_open()) {
			std::cerr << "Error: Could not open file!\n";
			return false;
		}

		json j;
		ifs >> j;

		ifs.close();

		// check if JSON is empty
		if (j.is_null() || j.empty()) {
			std::cerr << "Error: JSON file is empty or invalid!\n";
			return false;
		}

		try
		{
			if (j.contains(objectKey)) {
				//object = j.at(objectKey).get<T>();
				j.at(objectKey).get_to(object);
			}
			else
			{
				std::cerr << "JSON does not contain key: " << objectKey << std::endl;
			}
			return true;
		}
		catch (json::out_of_range& e)
		{
			std::cerr << e.what() << '\n';
		}
		return false;
	}

	template<typename T>
	static bool parseFromStream(std::ifstream& fileStream, T& object, const std::string objectKey)
	{
		// return the stream to the beginning of the file
		fileStream.clear();
		fileStream.seekg(0, std::ios::beg);

		json j;
		fileStream >> j;

		// check if JSON is empty
		if (j.is_null() || j.empty()) {
			std::cerr << "Error: JSON file is empty or invalid!\n";
			return false;
		}

		try
		{
			if (j.contains(objectKey)) {
				//object = j.at(objectKey).get<T>();
				j.at(objectKey).get_to(object);
			}
			else
			{
				std::cerr << "JSON does not contain key: " << objectKey << std::endl;
			}
			return true;
		}
		catch (json::out_of_range& e)
		{
			std::cerr << e.what() << '\n';
		}
		return false;
	}

	template<typename T>
	static bool parseFromJson(const json& j, T& object, const std::string objectKey)
	{
		// check if JSON is empty
		if (j.is_null() || j.empty()) {
			std::cerr << "Error: JSON file is empty or invalid!\n";
			return false;
		}

		try
		{
			if (j.contains(objectKey)) {
				//object = j.at(objectKey).get<T>();
				j.at(objectKey).get_to(object);
			}
			else
			{
				std::cerr << "JSON does not contain key: " << objectKey << std::endl;
			}
			return true;
		}
		catch (json::out_of_range& e)
		{
			std::cerr << e.what() << '\n';
		}
		return false;
	}
};

#endif // !__NLJsonParser__