#include "../../include/UtilsHeaders/TextFormatter.h"

std::shared_ptr<TextFormatter> TextFormatter::s_pInstance = nullptr;

std::shared_ptr<TextFormatter> TextFormatter::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = std::shared_ptr<TextFormatter>(new TextFormatter);
		return s_pInstance;
	}
	return s_pInstance;
}

std::string TextFormatter::trimFractionalPart(std::string floatStr, int numberAfterDot)
{
	int dotIndex = floatStr.find('.');
	return floatStr.substr(0, dotIndex + numberAfterDot + 1);
}

std::string TextFormatter::extractPercentage(std::string floatStr)
{
	int dotIndex = floatStr.find('.');
	return floatStr.substr(dotIndex + 1, 2);
}

std::vector<std::string> TextFormatter::splitCamelCase(const std::string& str)
{
    std::vector<std::string> words;
    std::string current;

    for (char ch : str) {
        if (isupper(ch)) {
            if (!current.empty()) {
                words.push_back(current);
                current.clear();
            }
            current += ch;
        }
        else {
            current += ch;
        }
    }
    if (!current.empty()) {
        words.push_back(current);
    }
    return words;
}

TextFormatter::TextFormatter()
{
}
