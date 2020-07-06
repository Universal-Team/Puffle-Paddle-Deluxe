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

extern C2D_Font font;

void GameScreen::Draw(void) const {
	GFX::DrawTop();
	// Drawing box and Tickets.
	Gui::Draw_Rect(270, 15, 100, 50, C2D_Color32(159, 56, 15, 255));
	Gui::Draw_Rect(275, 20, 90, 40, C2D_Color32(226, 183, 54, 255));
	Gui::DrawString(288, 23, 0.6f, BLACK, "Tickets", 80, 20, font);
	Gui::DrawString(305, 40, 0.6f, WHITE, std::to_string(this->currentGame->getTickets()), 80, 20, font);

	for (int i = 0; i < this->currentGame->getPuffleAmount(); i++) {
		GFX::DrawPuffle(this->currentGame->getPuffleType(i), this->currentGame->getPuffleState(i), this->currentGame->getPuffleX(i), this->currentGame->getPuffleY(i));
	}

	GFX::DrawPaddle(this->currentGame->getPaddleState(), this->currentGame->getPaddleX(), this->currentGame->getPaddleY());
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
	GFX::DrawBottom();
	Gui::DrawStringCentered(0, 50, 0.6f, BLACK, "PaddleX: " + std::to_string(this->currentGame->getPaddleX()) + "  |  " + "PuffleX: " + std::to_string(this->currentGame->getPuffleX(0)), 320, 20, font);
	Gui::DrawStringCentered(0, 90, 0.6f, BLACK, "PaddleY: " + std::to_string(this->currentGame->getPaddleY()) + "  |  " + "PuffleY: " + std::to_string(this->currentGame->getPuffleY(0)), 320, 20, font);
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
}

void GameScreen::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	this->PaddleLogic(hDown, hHeld, touch);
	this->GameLogic();
}

void GameScreen::PaddleLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hHeld & KEY_TOUCH) {
		this->currentGame->setPaddleX((touch.px * 1.25)); // * 1.25 -> from 320 to 400.
		this->currentGame->setPaddleY(touch.py);
	}
}

void GameScreen::GameLogic() {
	if (this->currentGame->getPuffleAmount() > 0) {

		// Test animation function.
		for (int i = 0; i < this->currentGame->getPuffleAmount(); i++) {
			if (this->currentGame->getPuffleBounced(i)) {
				this->currentGame->setPuffleY(i, this->currentGame->getPuffleY(i) - this->currentGame->getPuffleSpeed(i));
				if (this->currentGame->getPuffleY(i) < 1)	this->currentGame->setPuffleBounced(i, false);
			} else {
				this->currentGame->setPuffleY(i, this->currentGame->getPuffleY(i) + this->currentGame->getPuffleSpeed(i));
				this->currentGame->setPuffleSpeed(i, (this->currentGame->getPuffleSpeed(i) * 1.25));
			}
		}

		// Remove puffle, if Y larger than 240.
		for (int i = 0; i < this->currentGame->getPuffleAmount(); i++) {
			if (this->currentGame->getPuffleY(i) >= 240)	this->currentGame->removePuffle(i);
		}

		for (int i = 0; i < this->currentGame->getPuffleAmount(); i++) {
			if (this->touched(i)) {
				this->currentGame->setPuffleBounces(i, this->currentGame->getPuffleBounces(i) + 1);
				this->currentGame->setTickets(this->currentGame->getTickets() + 1);
				this->currentGame->setPuffleBounced(i, true);
			}
		}

	} else {
		Msg::promptMsg("Game is over!\n\nYou got " + std::to_string(this->currentGame->getTickets()) + " Ticket(s)!");
		Gui::screenBack(true);
		return;
	}
}

bool GameScreen::touched(int puffle) {
	if (this->currentGame->getPuffleBounced(puffle)) return false;
	if ((this->currentGame->getPuffleX(puffle) >= this->currentGame->getPaddleX())
	 && (this->currentGame->getPuffleX(puffle) <= (this->currentGame->getPaddleX() + PADDLE_WIDTH))) {
		if (((this->currentGame->getPuffleY(puffle) + this->currentGame->getPuffleHeight(puffle)) >= this->currentGame->getPaddleY() - 1)
		 && (((this->currentGame->getPuffleY(puffle) + this->currentGame->getPuffleHeight(puffle)) + PADDLE_HEIGHT - 1))) {
			return true;
		}
	}
	return false;
}