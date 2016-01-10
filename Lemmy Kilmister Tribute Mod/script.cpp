/*
CONTRIBUTORS:
- Christian Brandes: idea and some textures
- FunGt: script and textures
- jedijosh920: script for animations
- Alexander Blade: scripthookv and some script parts
*/

#include "script.h"
#include "keyboard.h"
#include <string>
#include <ctime>
#include "iostream"
#include "iniReader.h"

#pragma warning(disable : 4244 4305) // double <-> float conversions

//IniReader reader(".\\LemmyKilmister.ini");

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
	int keyLemmy = 0x4C;
	int keyHooker = 0x48;
	int keyBike = 0x42;
	int keySmoke = 0x4F;
	int keyDrink = 0x4B;
	int keyGuitar = 0x49;
	int keyShirt = 0x4A;
	int keyStop = 0x51;

	char iniPath[260];
	GetFullPathName("LemmyKilmister.ini", 261, iniPath, NULL);
	IniReader ini(iniPath);
	if (ini.fileExists()) {
		ini.readInt("Controls", "Lemmy", 0x4C, 16, keyLemmy);
		ini.readInt("Controls", "Hooker", 0x48, 16, keyHooker);
		ini.readInt("Controls", "Bike", 0x42, 16, keyBike);
		ini.readInt("Controls", "Smoke", 0x4F, 16, keySmoke);
		ini.readInt("Controls", "Drink", 0x4B, 16, keyDrink);
		ini.readInt("Controls", "Guitar", 0x49, 16, keyGuitar);
		ini.readInt("Controls", "Shirt", 0x4A, 16, keyShirt);
		ini.readInt("Controls", "Stop", 0x51, 16, keyStop);
	}

	Ped playerPed;
	Player playerID;
	Vector3 position;
	bool widescreen = GRAPHICS::GET_IS_WIDESCREEN();

	while (true) {
		// INIT
		playerID = PLAYER::PLAYER_ID();
		playerPed = PLAYER::PLAYER_PED_ID();
		position = ENTITY::GET_ENTITY_COORDS(playerPed, 1);

		// reset to normal skin if dies or get arrested
		Hash model = ENTITY::GET_ENTITY_MODEL(playerPed);
		if (ENTITY::IS_ENTITY_DEAD(playerPed) || PLAYER::IS_PLAYER_BEING_ARRESTED(playerID, TRUE)) {
			if (model != GAMEPLAY::GET_HASH_KEY("player_zero") &&
				model != GAMEPLAY::GET_HASH_KEY("player_one") &&
				model != GAMEPLAY::GET_HASH_KEY("player_two")) {
				WAIT(1000);
				model = GAMEPLAY::GET_HASH_KEY("player_zero");
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model))	WAIT(0);
				PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
				PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				while (ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(playerID, TRUE))
					WAIT(0);
			}
		}

		// CHANGE SKIN
		if (IsKeyDown(VK_SHIFT) && IsKeyJustUp(keyLemmy)) {
			DWORD freemodeMale = GAMEPLAY::GET_HASH_KEY((char *)"mp_m_freemode_01");
			if (STREAMING::IS_MODEL_IN_CDIMAGE(freemodeMale) && STREAMING::IS_MODEL_VALID(freemodeMale)) {
				STREAMING::REQUEST_MODEL(freemodeMale);
				while (!STREAMING::HAS_MODEL_LOADED(freemodeMale))
					WAIT(0);
				PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), freemodeMale);

				playerPed = PLAYER::PLAYER_PED_ID();
				PED::SET_PED_DEFAULT_COMPONENT_VARIATION(playerPed);

				// CLOTHES and FACE
				PED::SET_PED_HEAD_BLEND_DATA(playerPed, 0, 0, 0, 0, 0, 0, 1.0, 1.0, 1.0, true);
				PED::SET_PED_HEAD_OVERLAY(playerPed, 1, 27, 1.0); // bread
				PED::_0x497BF74A7B9CB952(playerPed, 1, 1, 0, 0); // beard color
				PED::SET_PED_HEAD_OVERLAY(playerPed, 2, 19, 1.0); // eyebrow
				PED::_0x497BF74A7B9CB952(playerPed, 2, 1, 0, 0); // eyebrow color
				PED::SET_PED_HEAD_OVERLAY(playerPed, 3, 14, 1.0); // ageing
				PED::SET_PED_HEAD_OVERLAY(playerPed, 10, 0, 1.0); // peli
				PED::_0x497BF74A7B9CB952(playerPed, 10, 1, 0, 0); // peli color
				
				PED::SET_PED_COMPONENT_VARIATION(playerPed, 2, 22, 0, 2); // hair
				PED::_0x4CFFC65454C93A49(playerPed, 0, 0); // hair color
				PED::SET_PED_COMPONENT_VARIATION(playerPed, 3, 11, 0, 2); // torso
				PED::SET_PED_COMPONENT_VARIATION(playerPed, 4, 4, 0, 2); // pants
				PED::SET_PED_COMPONENT_VARIATION(playerPed, 8, 15, 0, 2); // acc
				//PED::SET_PED_COMPONENT_VARIATION(playerPed, 6, 15, 0, 2); // shoes
				//PED::SET_PED_COMPONENT_VARIATION(playerPed, 11, 13, 2, 2); // t2
				PED::IS_PED_COMPONENT_VARIATION_VALID(playerPed, 6, 37, 0) ? PED::SET_PED_COMPONENT_VARIATION(playerPed, 6, 37, 0, 2) : PED::SET_PED_COMPONENT_VARIATION(playerPed, 6, 15, 0, 2);
				PED::IS_PED_COMPONENT_VARIATION_VALID(playerPed, 11, 95, 2) ? PED::SET_PED_COMPONENT_VARIATION(playerPed, 11, 95, 1, 2) : PED::SET_PED_COMPONENT_VARIATION(playerPed, 11, 13, 2, 2);

				// TATTOOS
				DWORD coll1 = GAMEPLAY::GET_HASH_KEY("multiplayer_overlays");
				DWORD tattoo1 = GAMEPLAY::GET_HASH_KEY("FM_Tat_Award_F_001");
				PED::_0x5F5D1665E352A839(playerPed, coll1, tattoo1);
				DWORD coll2 = GAMEPLAY::GET_HASH_KEY("multiplayer_overlays");
				DWORD tattoo2 = GAMEPLAY::GET_HASH_KEY("FM_Tat_M_038");
				PED::_0x5F5D1665E352A839(playerPed, coll2, tattoo2);

				// PROPS
				PED::SET_PED_PROP_INDEX(playerPed, 0, 13, 0, true); // hat
				PED::SET_PED_PROP_INDEX(playerPed, 1, 5, 0, true); // glasses

				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(freemodeMale);
			}
		}

		// WEAR MOTORHEAD SHIRT
		if (IsKeyDown(VK_SHIFT) && IsKeyJustUp(keyShirt)) {
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, 0, 0, 2); // torso
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, 0, 2, 2); // t2
		}

		// SPAWN HEXER MOTORBIKE
		if (IsKeyDown(VK_SHIFT) && IsKeyJustUp(keyBike)) {
			// from Alexander Blade native trainer code
			DWORD model = GAMEPLAY::GET_HASH_KEY((char *)"HEXER");
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model)) {
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model))
					WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);
			}
		}

		// SPAWN HOOKERS
		if (IsKeyDown(VK_SHIFT) && IsKeyJustUp(keyHooker)) {
			DWORD hooker = GAMEPLAY::GET_HASH_KEY((char *)"s_f_y_hooker_01");
			if (STREAMING::IS_MODEL_IN_CDIMAGE(hooker) && STREAMING::IS_MODEL_VALID(hooker)) {
				STREAMING::REQUEST_MODEL(hooker);
				while (!STREAMING::HAS_MODEL_LOADED(hooker))
					WAIT(0);
				playerPed = PLAYER::PLAYER_PED_ID();
				Vector3 pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.0, 3.0, 0.0);
				Ped ped = PED::CREATE_PED(5, hooker, pos.x, pos.y, pos.z, 1, false, true);

				// the hooker is YOUR hooker
				int groupIndex = PED::GET_PED_GROUP_INDEX(playerPed);
				PED::SET_PED_AS_GROUP_LEADER(playerPed, groupIndex);
				PED::SET_PED_AS_GROUP_MEMBER(ped, groupIndex);
				PED::SET_PED_NEVER_LEAVES_GROUP(ped, true);

				WAIT(100);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hooker);
			}
		}

		// ANIMATIONS
		// SMOKING
		if (IsKeyDown(VK_SHIFT) && IsKeyJustUp(keySmoke)) {
			playerPed = PLAYER::PLAYER_PED_ID();
			AI::TASK_START_SCENARIO_IN_PLACE(playerPed, "WORLD_HUMAN_SMOKING", 0, 1);
		}

		// DRINKING
		if (IsKeyDown(VK_SHIFT) && IsKeyJustUp(keyDrink)) {
			playerPed = PLAYER::PLAYER_PED_ID();
			AI::TASK_START_SCENARIO_IN_PLACE(playerPed, "WORLD_HUMAN_DRINKING", 0, 1);
		}

		// GUITAR
		if (IsKeyDown(VK_SHIFT) && IsKeyJustUp(keyGuitar)) {
			playerPed = PLAYER::PLAYER_PED_ID();
			AI::TASK_START_SCENARIO_IN_PLACE(playerPed, "WORLD_HUMAN_MUSICIAN", 0, 1);
		}

		// STOP ANIMATIONS
		if (IsKeyDown(VK_SHIFT) && IsKeyJustUp(keyStop)) {
			playerPed = PLAYER::PLAYER_PED_ID();
			AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
		}
		
		// DEBUGGING
		/*
		if (IsKeyDown(0x31)) {
			playerPed = PLAYER::PLAYER_PED_ID();
			int numVar = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(playerPed, 0);

			int face = PED::GET_PED_DRAWABLE_VARIATION(playerPed, 0);
			int head = PED::GET_PED_DRAWABLE_VARIATION(playerPed, 1);
			int hair = PED::GET_PED_DRAWABLE_VARIATION(playerPed, 2);
			int tors = PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3);
			int leg = PED::GET_PED_DRAWABLE_VARIATION(playerPed, 4);
			int hand = PED::GET_PED_DRAWABLE_VARIATION(playerPed, 5);
			int feet = PED::GET_PED_DRAWABLE_VARIATION(playerPed, 6);
			int eye = PED::GET_PED_DRAWABLE_VARIATION(playerPed, 7);
			int acc = PED::GET_PED_DRAWABLE_VARIATION(playerPed, 8);
			int task = PED::GET_PED_DRAWABLE_VARIATION(playerPed, 9);
			int tex = PED::GET_PED_DRAWABLE_VARIATION(playerPed, 10);
			int t2 = PED::GET_PED_DRAWABLE_VARIATION(playerPed, 11);

			int hat = PED::GET_PED_PROP_INDEX(playerPed, 0);
			int glasses = PED::GET_PED_PROP_INDEX(playerPed, 1);

			int ov0 = PED::_0xA60EF3B6461A4D43(playerPed, 0);
			int ov1 = PED::_0xA60EF3B6461A4D43(playerPed, 1);
			int ov2 = PED::_0xA60EF3B6461A4D43(playerPed, 2);
			int ov3 = PED::_0xA60EF3B6461A4D43(playerPed, 3);
			int ov4 = PED::_0xA60EF3B6461A4D43(playerPed, 4);
			int ov5 = PED::_0xA60EF3B6461A4D43(playerPed, 5);
			int ov6 = PED::_0xA60EF3B6461A4D43(playerPed, 6);
			int ov7 = PED::_0xA60EF3B6461A4D43(playerPed, 7);
			int ov8 = PED::_0xA60EF3B6461A4D43(playerPed, 8);
			int ov9 = PED::_0xA60EF3B6461A4D43(playerPed, 9);
			int ov10 = PED::_0xA60EF3B6461A4D43(playerPed, 10);
			int ov11 = PED::_0xA60EF3B6461A4D43(playerPed, 11);

			DWORD coll1 = GAMEPLAY::GET_HASH_KEY("mpchristmas2_overlays");
			DWORD tattoo1 = GAMEPLAY::GET_HASH_KEY("MP_Xmas2_M_Tat_000");
			int zone = PED::_0x9FD452BFBE7A7A8B(coll1, tattoo1);

			char text1[300], text2[300];
			sprintf_s(text1, "FAC:%d HED:%d HAIR:%d TOR:%d LEG:%d HAND:%d FEET:%d EYE:%d ACC:%d TASK:%d TEX:%d TORSO2:%d", face, head, hair, tors, leg, hand, feet, eye, acc, task, tex, t2);
			draw_text(text1, 0.5, 0, 0.3);
			sprintf_s(text1, "HAT:%d GLASSES:%d", hat, glasses);
			draw_text(text1, 0.6, 0, 0.3);
			sprintf_s(text2, "ov0:%d ov1:%d ov2:%d ov3:%d ov4:%d ov5:%d ov6:%d ov7:%d ov8:%d ov9:%d ov10:%d ov11:%d", ov0, ov1, ov2, ov3, ov4, ov5, ov6, ov7, ov8, ov9, ov10, ov11);
			draw_text(text2, 0.7, 0, 0.3);
		}
		*/

		WAIT(0);
	}
}

void ScriptMain() {
	srand(GetTickCount());
	main();
}