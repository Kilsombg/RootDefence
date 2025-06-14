#ifndef __WaveParser__
#define __WaveParser__

#include "WaveManager.h"

#include<memory>

#include<nlohmann\json.hpp>
using json = nlohmann::json;

/**
* Parser for waves.
* 
* Call parseWaves with JSON file to get waves.
*/
class WaveParser
{
public:
	/**
	* Set waves to waveManager from JSON file.
	* 
	* @param filePaht - path to waves JSON file.
	* @param waveManager - game's waveManager.
	*/
	bool parseWaves(const char* filePath, std::shared_ptr<WaveManager>& waveManager);
};

#endif // !__WaveParser__
