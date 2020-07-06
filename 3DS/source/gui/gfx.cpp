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
#include "gfx.hpp"

extern C2D_SpriteSheet BG, Puffles, Sprites;
extern C2D_Font font;

void GFX::DrawBG(int bg, bool top) {
	(top ? Gui::ScreenDraw(Top) : Gui::ScreenDraw(Bottom));
	Gui::DrawSprite(BG, bg, 0, 0);
}

void GFX::DrawSprite(int index, int x, int y) {
	Gui::DrawSprite(Sprites, index, x, y);
}

void GFX::DrawPuffle(PuffleType puffle, PuffleState state, int x, int y) {
	switch(puffle) {
		case PuffleType::Nothing:
			break;
		case PuffleType::Gray:
			Gui::DrawSprite(Puffles, int(state) - 1, x, y);
			break;
	}
}

void GFX::DrawPaddle(PaddleState paddlestate, int x, int y) {
	switch(paddlestate) {
		case PaddleState::Normal:
			Gui::DrawSprite(Sprites, sprites_paddle_idx, x, y);
			break;
		case PaddleState::Hit:
			Gui::DrawSprite(Sprites, sprites_paddle_idx, x, y);
			break;
	}
}

void GFX::DrawTop(void) {
	Gui::ScreenDraw(Top);
	GFX::DrawBG(background_normal_idx, true);
}

void GFX::DrawBottom(void) {
	Gui::ScreenDraw(Bottom);
	GFX::DrawBG(background_opening_idx, false);
}

void GFX::DrawButton(Button btn) {
	GFX::DrawSprite(sprites_button_idx, btn.x, btn.y);
	Gui::DrawStringCentered(- (164/2) + btn.x, btn.y + (48/2) - (Gui::GetStringHeight(0.7f, btn.Text, font) / 2), 0.7f, BLACK, btn.Text, 160, 40, font);
}