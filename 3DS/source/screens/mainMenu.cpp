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

#include "gameScreen.hpp"
#include "mainMenu.hpp"

extern bool exiting;
extern bool buttonTouch(touchPosition touch, Button button);

void MainMenu::Draw(void) const {
	GFX::DrawTop();
	GFX::DrawSprite(sprites_logo_idx, 50, this->yLogo);
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
	GFX::DrawBottom();
	for (int i = 0; i < (int)this->buttons.size(); i++) {
		GFX::DrawButton(this->buttons[i]);
	}

	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
}

void MainMenu::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_START) {
		fadeout = true;
		fadecolor = 0;
		exiting = true;
	}

	if (!this->doUp) {
		this->yLogo++;
		if (this->yLogo == 100)	this->doUp = true;
	}

	if (this->doUp) {
		this->yLogo--;
		if (this->yLogo == 30)	this->doUp = false;
	}

	if (hDown & KEY_TOUCH) {
		if (buttonTouch(touch, buttons[0])) {
			if (Msg::promptMsg("Do you like to start the game?\n\nPress A for Yes, B for No.")) {
				Gui::setScreen(std::make_unique<GameScreen>(), true, true);
			}
		}
	}
}