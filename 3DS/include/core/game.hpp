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

#ifndef _PUFFLE_PADDLE_DELUXE_GAME_HPP
#define _PUFFLE_PADDLE_DELUXE_GAME_HPP

#include "paddle.hpp"
#include "puffle.hpp"
#include <3ds.h>
#include <memory>
#include <vector>

class Game {
public:
	Game();

	// General.
	int getTickets() { return this->tickets; }
	void setTickets(int tickets) { this->tickets = tickets; }

	// Paddle.
	int getPaddleX() { return this->paddle->getX(); }
	int getPaddleY() { return this->paddle->getY(); }
	void setPaddleX(int x) { this->paddle->setX(x); }
	void setPaddleY(int y) { this->paddle->setY(y); }
	PaddleState getPaddleState() { return this->paddle->getState(); }
	void setPaddleState(PaddleState state) { this->paddle->setState(state); }

	// Puffle.
	int getPuffleX(int puffle);
	int getPuffleY(int puffle);
	int getPuffleSpeed(int puffle);
	void setPuffleX(int puffle, int x);
	void setPuffleY(int puffle, int y);
	void setPuffleSpeed(int puffle, int speed);
	void addPuffle(PuffleType puffletype = PuffleType::Gray);
	void removePuffle(int puffle);
	int getPuffleAmount() { return (int)this->puffles.size(); }
	PuffleState getPuffleState(int puffle);
	void setPuffleState(int puffle, PuffleState state);
	PuffleType getPuffleType(int puffle);
	int getPuffleHeight(int puffle);
	int getPuffleWidth(int puffle);
	int getPuffleBounces(int puffle);
	void setPuffleBounces(int puffle, int bounces);
	bool getPuffleBounced(int puffle);
	void setPuffleBounced(int puffle, bool bounced);
	bool getDown(int puffle);
	void setDown(int puffle, bool down);
private:
	std::vector<std::unique_ptr<Puffle>> puffles;
	std::vector<bool> doDown;
	std::unique_ptr<Paddle> paddle;
	int tickets = 0;
};

#endif