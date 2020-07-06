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

#include "puffle.hpp"

Puffle::Puffle(PuffleType Pt) {
	this->speed = 2; this->x = 0; this->y = 0;
	this->puffletype = Pt; this->pufflestate = PuffleState::Normal;
}

// Getter.
int Puffle::getX() { return this->x; }
int Puffle::getY() { return this->y; }
int Puffle::getSpeed() { return this->speed; }

// Setter.
void Puffle::setX(int x) { this->x = x; }
void Puffle::setY(int y) { this->y = y; }
void Puffle::setSpeed(int speed) { this->speed = speed; }

int Puffle::getHeight() {
	switch(this->pufflestate) {
		case PuffleState::Nothing:
			return 0;
		case PuffleState::Bounced:
			return 45;
		case PuffleState::Normal:
			return 42;
		case PuffleState::High:
			return 75;
		case PuffleState::Down:
			return 92;
		case PuffleState::FastDown:
			return 94;
	}

	return 0;
}

int Puffle::getWidth() {
	switch(this->pufflestate) {
		case PuffleState::Nothing:
			return 0;
		case PuffleState::Bounced:
			return 96;
		case PuffleState::Normal:
			return 48;
		case PuffleState::High:
			return 75;
		case PuffleState::Down:
			return 55;
		case PuffleState::FastDown:
			return 56;
	}

	return 0;
}