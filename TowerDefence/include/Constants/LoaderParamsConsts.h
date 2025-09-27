#pragma once

namespace LoaderParamsConsts {
#pragma region general load params
	constexpr char x[] = "x";
	constexpr char y[] = "y";
	constexpr char textureID[] = "textureID";
	constexpr char numFrames[] = "numFrames";
	constexpr char width[] = "width";
	constexpr char height[] = "height";
#pragma endregion

#pragma region tilemap params specific
#pragma endregion

#pragma region xml states params specific
	constexpr char callbackID[] = "callbackID";
	
	// main menu callbacks
	constexpr char playbuttonCallbackID[] = "playbuttonCallbackID";
	constexpr char exitbuttonCallbackID[] = "exitbuttonCallbackID";
	constexpr char openDeleteConfPanelCallbackID[] = "openDeleteConfPanelCallbackID";
	constexpr char deleteProgressCallbackID[] = "deleteProgressCallbackID";
	constexpr char mapMenuButtonCallbackID[] = "mapMenuButtonCallbackID";
	constexpr char closeMapsPanelCallbackID[] = "closeMapsPanelCallbackID";
	constexpr char backToMapsPanelCallbackID[] = "backToMapsPanelCallbackID";
	constexpr char difficultyButtonCallbackID[] = "difficultyButtonCallbackID";

	// maps menu callbacks
	constexpr char mainMenuButtonCallbackID[] = "mainMenuButtonCallbackID";
	
	// pause callbacks
	constexpr char restartButtonCallbackID[] = "restartButtonCallbackID";
	constexpr char resumeButtonCallbackID[] = "resumeButtonCallbackID";
	
	// play callbacks
	constexpr char createTowerCallbackID[] = "createTowerCallbackID";
	constexpr char startWaveCallbackID[] = "startWaveCallbackID";
	constexpr char pauseStateCallbackID[] = "pauseStateCallbackID";

	constexpr char towerUpgradeCallbackID[] = "towerUpgradeCallbackID";
	constexpr char sellTowerCallbackID[] = "sellTowerCallbackID";

	// level up callbacks
	constexpr char returnToPlayCallbackID[] = "returnToPlayCallbackID";

	
	constexpr char animSpeed[] = "animSpeed";
#pragma endregion


#pragma region MapMenuButton params
	constexpr char mapLevelFileName[] = "mapLevelFileName";
#pragma endregion

#pragma region DifficultyButton params
	constexpr char difficulty[] = "difficulty";
#pragma endregion

	
#pragma region TowerButton params
	constexpr char towerName[] = "towerName";
	constexpr char towerColor[] = "towerColor";
	constexpr char towerButtonSuffix[] = "Button";
	constexpr char towerNameIDSuffix[] = "Tower";
#pragma endregion


#pragma region TowerUpgradedButton params
	constexpr char upgradeID[] = "upgradeID";
#pragma endregion


#pragma region enemies params
	constexpr char moveSpeed[] = "moveSpeed";
	constexpr char maxHealth[] = "maxHealth";
	constexpr char defence[] = "defence";
	constexpr char dropType[] = "dropType";
	constexpr char dropValue[] = "dropValue";
	constexpr char exp[] = "experience";
#pragma endregion


#pragma region towers params
	constexpr char name[] = "name";
	constexpr char projectileID[] = "projectileID";
	constexpr char damage[] = "damage";
	constexpr char radius[] = "radius";
	constexpr char costType[] = "costType";
	constexpr char costValue[] = "costValue";
	constexpr char attackSpeed[] = "attackSpeed";
	constexpr char canBeColored[] = "canBeColored";
	constexpr char color[] = "color";
	constexpr char towerUpgradesData[] = "towerUpgradesData";
#pragma endregion


#pragma region freeze tower
	constexpr char freezePercentage[] = "freezePercentage";
#pragma endregion



#pragma region towerUpgradesData params
	constexpr char statName[] = "statName";
	constexpr char values[] = "values";
	constexpr char costs[] = "costs";
	constexpr char maxLevel[] = "maxLevel";
	constexpr char nextLevel[] = "nextLevel";
#pragma endregion


#pragma region projectiles params
	constexpr char projectileSpeed[] = "projectileSpeed";
#pragma endregion


#pragma region Text and Texture params
	constexpr char hidden[] = "hidden";
#pragma endregion


#pragma region Text params
	constexpr char characterWidth[] = "characterWidth";
	constexpr char message[] = "message";
	constexpr char labelId[] = "labelId";
	constexpr char dynamic[] = "dynamic";
#pragma endregion

}