/*
  SHOW COORDS XYZ AND ANGLE
  Author: FunGt
  Author ScriptHookV: Alexander Blade
*/

#include "script.h"
#include <string>

#pragma warning(disable : 4244 4305) // double <-> float conversions

void main() {
	while (true) {
		if (ENTITY::GET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID()) >= 200 || PED::IS_PED_SWIMMING(PLAYER::PLAYER_PED_ID())) {
			PED::CLEAR_PED_BLOOD_DAMAGE(PLAYER::PLAYER_PED_ID());
		}
		WAIT(0);
	}
}

void ScriptMain() {
	srand(GetTickCount());
	main();
}
