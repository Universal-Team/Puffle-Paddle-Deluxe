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

#ifndef _PUFFLE_PADDLE_DELUXE_PUFFLE_HPP
#define _PUFFLE_PADDLE_DELUXE_PUFFLE_HPP

#include <3ds.h>

enum class PuffleType {
	Nothing,
	Gray
};

// No idea how to call those modes. xD
enum class PuffleState {
	Nothing,
	Bounced,
	Normal,
	High,
	Down,
	FastDown
};

class Puffle {
public:
	Puffle(PuffleType Pt = PuffleType::Gray);
	int getX();
	int getY();
	int getSpeed();
	void setX(int x);
	void setY(int y);
	void setSpeed(int speed);
	PuffleState getState() { return this->pufflestate; }
	void setState(PuffleState state) { this->pufflestate = state; }
	PuffleType getType() { return this->puffletype; }
	int getHeight();
	int getWidth();
	int getBounces() { return this->bounces; }
	void setBounces(int bounces) { this->bounces = bounces; }
	bool getBounced() { return this->bounced; }
	void setBounced(bool bounced) { this->bounced = bounced; }
private:
	int x = 0, y = 0, speed = 1, bounces = 0;
	bool bounced = false;
	PuffleType puffletype;
	PuffleState pufflestate;
};

#endif