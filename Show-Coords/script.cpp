/*
  SHOW COORDS XYZ AND ANGLE
  Author: FunGt
  Author angle: PlasticTangerine
  Author ScriptHookV: Alexander Blade
*/

#include "script.h"
#include <string>

#pragma warning(disable : 4244 4305) // double <-> float conversions

void draw_text(char *text, float x, float y, float scale) {
	UI::SET_TEXT_FONT(0);
	UI::SET_TEXT_SCALE(scale, scale);
	UI::SET_TEXT_COLOUR(255, 255, 255, 245);
	UI::SET_TEXT_WRAP(0.0, 1.0);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(2, 2, 0, 0, 0);
	UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_DRAW_TEXT(y, x);
}

void main() {
	bool widescreen = GRAPHICS::GET_IS_WIDESCREEN();
	Ped playerPed;
	Vector3 position;

	while (true) {
		playerPed = PLAYER::PLAYER_PED_ID();
		position = ENTITY::GET_ENTITY_COORDS(playerPed, 1);
		widescreen = GRAPHICS::GET_IS_WIDESCREEN();

		char coords[100];
		sprintf_s(coords, "X: %.3f Y: %.3f Z: %.3f Angle: %.3f", position.x, position.y, position.z, ENTITY::GET_ENTITY_HEADING(playerPed));
		widescreen ? draw_text(coords, 0.978, 0.205 - 0.03, 0.3) : draw_text(coords, 0.978, 0.205, 0.3);

		WAIT(0);
	}
}

void ScriptMain() {
	srand(GetTickCount());
	main();
}
