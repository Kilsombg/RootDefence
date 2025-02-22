#include "../../include/WaveHeaders/WaveParser.h"
#include "../../include/WaveHeaders/Wave.h"

#include "../../include/Constants/WaveConstans.h"

#include "../../include/UtilsHeaders/NLJsonParser.h"

#include<fstream>
#include<iostream>
#include<vector>

bool WaveParser::parseWaves(const char* filePath, std::shared_ptr<WaveManager>& waveManager)
{
	if (!waveManager) {
		std::cerr << "Error: waveManager is not initialized.\n";
		return false;
	}

	if (!NLJasonParser<std::vector<Wave>>::parseFromFile(filePath, waveManager->getWaves(), WaveConstans::waves))
	{
		std::cerr << "Couldn't parse waves object.\n";
		return false;
	}

	waveManager->load();
	return true;
}