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
	constexpr char playbuttonCallbackID[] = "playbuttonCallbackID";
	constexpr char exitbuttonCallbackID[] = "exitbuttonCallbackID";
	constexpr char mainbuttonCallbackID[] = "mainbuttonCallbackID";
	constexpr char resumebuttonCallbackID[] = "resumebuttonCallbackID";
	constexpr char restartbuttonCallbackID[] = "restartbuttonCallbackID";
	constexpr char createTowerCallbackID[] = "createTowerCallbackID";
	constexpr char animSpeed[] = "animSpeed";
#pragma endregion

#pragma region enemies params
	constexpr char moveSpeed[] = "moveSpeed";
	constexpr char maxHealth[] = "maxHealth";
	constexpr char defence[] = "defence";
#pragma endregion


#pragma region towers params
	constexpr char towerName[] = "towerName";
#pragma endregion

}