#ifndef __WaveParser__
#define __WaveParser__

#include "WaveManager.h"

#include<memory>
#include<vector>

#include<nlohmann\json.hpp>
using json = nlohmann::json;

class WaveParser
{
public:
	bool parseWaves(const char* filePath, std::shared_ptr<WaveManager>& waveManager);
};

#endif // !__WaveParser__
