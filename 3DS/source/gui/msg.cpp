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

#include "common.hpp"
#include "msg.hpp"

extern C2D_Font font;

// Display a Message, which needs to be confirmed with A/B.
bool Msg::promptMsg(std::string promptMsg) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, BLACK);
	C2D_TargetClear(Bottom, BLACK);
	GFX::DrawTop();
	Gui::Draw_Rect(80, 80, 240, 80, C2D_Color32(159, 56, 15, 255));
	Gui::Draw_Rect(85, 85, 230, 70, C2D_Color32(226, 183, 54, 255));
	Gui::DrawStringCentered(0, 90, 0.6f, BLACK, promptMsg, 220, 70, font);
	GFX::DrawBottom();
	C3D_FrameEnd(0);

	while(1) {
		gspWaitForVBlank();
		hidScanInput();
		if ((hidKeysDown() & KEY_A)) {
			return true;
		} else if ((hidKeysDown() & KEY_B)) {
			return false;
		}
	}
}