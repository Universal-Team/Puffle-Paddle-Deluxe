/*
*   This file is part of Puffle Paddle Deluxe
*   Copyright (C) 2020 Universal-Team
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#include "init.hpp"
#include "gui.hpp"
#include "mainMenu.hpp"
#include "screenCommon.hpp"
#include "sound.h"

#include <3ds.h>
#include <unistd.h>

bool exiting = false;
bool dspFound = false;
touchPosition touch;
sound *bgm = NULL;
bool songIsFound = false;

// Include all spritesheet's.
C2D_SpriteSheet BG, Puffles, Sprites;
C2D_Font font;

// If button Position pressed -> Do something.
bool touching(touchPosition touch, Structs::ButtonPos button) {
	if (touch.px >= button.x && touch.px <= (button.x + button.w) && touch.py >= button.y && touch.py <= (button.y + button.h))
		return true;
	else
		return false;
}

bool buttonTouch(touchPosition touch, Button button) {
	if (touch.px >= button.x && touch.px <= (button.x + button.xSize) && touch.py >= button.y && touch.py <= (button.y + button.ySize))
		return true;
	else
		return false;
}

void Init::loadSoundEffects(void) {
	if (dspFound) {
		bgm = new sound("romfs:/Music.wav", 1, true);
		songIsFound = true;
	}
}

void Init::playMusic(void) {
	if (songIsFound) bgm->play();
}

void Init::stopMusic(void) {
	if (songIsFound) bgm->stop();
}


Result Init::Initialize() {
	gfxInitDefault();
	romfsInit();
	Gui::init();
	cfguInit();
	fadein = true;
	fadealpha = 255;

	Gui::loadFont(font, "romfs:/gfx/font.bcfnt");
	Gui::loadSheet("romfs:/gfx/background.t3x", BG);
	Gui::loadSheet("romfs:/gfx/sprites.t3x", Sprites);
	Gui::loadSheet("romfs:/gfx/puffle.t3x", Puffles);
	osSetSpeedupEnable(true);	// Enable speed-up for New 3DS users

	if (access("sdmc:/3ds/dspfirm.cdc", F_OK ) != -1) {
		ndspInit();
		dspFound = true;
		loadSoundEffects();
		playMusic();
	}

	Gui::setScreen(std::make_unique<MainMenu>(), false, true);

	return 0;
}

Result Init::MainLoop() {
	// Initialize everything.
	Initialize();
	// Loop as long as the status is not exiting.
	while (aptMainLoop()) {
		hidScanInput();
		u32 hHeld = hidKeysHeld();
		u32 hDown = hidKeysDown();
		hidTouchRead(&touch);
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(Top, BLACK);
		C2D_TargetClear(Bottom, BLACK);
		Gui::clearTextBufs();
		Gui::DrawScreen(true);
		Gui::ScreenLogic(hDown, hHeld, touch, true, true);
		C3D_FrameEnd(0);
		gspWaitForVBlank();
		if (exiting) {
			if (!fadeout)	break;
		}

		Gui::fadeEffects(16, 16, true);
	}
	// Exit all services and exit the app.
	Exit();
	return 0;
}

Result Init::Exit() {
	// Music.
	if (songIsFound) stopMusic();
	delete bgm;
	if (dspFound) ndspExit();
	Gui::unloadFont(font);
	Gui::exit();
	Gui::unloadSheet(BG);
	Gui::unloadSheet(Sprites);
	Gui::unloadSheet(Puffles);
	gfxExit();
	cfguExit();
	romfsExit();
	return 0;
}