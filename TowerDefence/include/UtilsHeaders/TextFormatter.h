#ifndef __TextFormatter__
#define __TextFormatter__

#include<memory>
#include<vector>
#include<string>

/**
* Helper class for formatting string.
*/
class TextFormatter
{
public:
	static std::shared_ptr<TextFormatter> Instance();

	/**
	* Trim exceeded numbers from float number string after floating point.
	* 
	* @param floatStr - float value in string
	* @param numberAdterDot - count of numbers after floating point to keep.
	*/
	std::string trimFractionalPart(std::string floatStr, int numberAfterDot);

	/**
	* get's percentage from a string with float value.
	* 
	* @return two digits after floating point.
	*/
	std::string extractPercentage(std::string floatStr);
	/**
	* Split a  string into vector of words written in camelCase.
	*/
	static std::vector<std::string> splitCamelCase(const std::string& str);

private:
	TextFormatter();
	static std::shared_ptr<TextFormatter> s_pInstance;
};

typedef TextFormatter TheTextFormatter;

#endif // !__TextFormatter__
