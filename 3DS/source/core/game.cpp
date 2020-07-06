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

#include "game.hpp"

// Init with 1 puffle and paddle.
Game::Game() {
	this->addPuffle(); this->paddle = std::make_unique<Paddle>();
}

int Game::getPuffleX(int puffle) {
	if (puffle > (int)this->puffles.size()) return 0; // Out of scope.
	return this->puffles[puffle]->getX();
}

int Game::getPuffleY(int puffle) {
	if (puffle > (int)this->puffles.size()) return 0; // Out of scope.
	return this->puffles[puffle]->getY();
}

int Game::getPuffleSpeed(int puffle) {
	if (puffle > (int)this->puffles.size()) return 0; // Out of scope.
	return this->puffles[puffle]->getSpeed();
}

void Game::setPuffleX(int puffle, int x) {
	if (puffle > (int)this->puffles.size()) return; // Out of scope.
	this->puffles[puffle]->setX(x);
}

void Game::setPuffleY(int puffle, int y) {
	if (puffle > (int)this->puffles.size()) return; // Out of scope.
	this->puffles[puffle]->setY(y);
}

void Game::setPuffleSpeed(int puffle, int speed) {
	if (puffle > (int)this->puffles.size()) return; // Out of scope.
	this->puffles[puffle]->setSpeed(speed);
}

void Game::addPuffle(PuffleType puffletype) {
	this->puffles.push_back({std::make_unique<Puffle>(puffletype)});
	this->doDown.push_back({true});
}

void Game::removePuffle(int puffle) {
	if (puffle > (int)this->puffles.size()) return; // Out of scope.
	this->puffles.erase(this->puffles.begin() + puffle);
	this->doDown.erase(this->doDown.begin() + puffle);
}

PuffleState Game::getPuffleState(int puffle) {
	if (puffle > (int)this->puffles.size()) return PuffleState::Nothing; // Out of scope.
	return this->puffles[puffle]->getState();
}

void Game::setPuffleState(int puffle, PuffleState state) {
	if (puffle > (int)this->puffles.size()) return; // Out of scope.
	return this->puffles[puffle]->setState(state);
}

PuffleType Game::getPuffleType(int puffle) {
	if (puffle > (int)this->puffles.size()) return PuffleType::Nothing; // Out of scope.
	return this->puffles[puffle]->getType();
}

int Game::getPuffleHeight(int puffle) {
	if (puffle > (int)this->puffles.size()) return 0; // Out of scope.
	return this->puffles[puffle]->getHeight();
}

int Game::getPuffleWidth(int puffle) {
	if (puffle > (int)this->puffles.size()) return 0; // Out of scope.
	return this->puffles[puffle]->getWidth();
}

int Game::getPuffleBounces(int puffle) {
	if (puffle > (int)this->puffles.size()) return 0; // Out of scope.
	return this->puffles[puffle]->getBounces();
}

void Game::setPuffleBounces(int puffle, int bounces) {
	if (puffle > (int)this->puffles.size()) return; // Out of scope.
	this->puffles[puffle]->setBounces(bounces);
}

bool Game::getPuffleBounced(int puffle) {
	if (puffle > (int)this->puffles.size()) return false; // Out of scope.
	return this->puffles[puffle]->getBounced();
}

void Game::setPuffleBounced(int puffle, bool bounced) {
	if (puffle > (int)this->puffles.size()) return; // Out of scope.
	return this->puffles[puffle]->setBounced(bounced);
}

bool Game::getDown(int puffle) {
	if (puffle > (int)this->doDown.size()) return false; // Out of scope.
	return this->doDown[puffle];
}

void Game::setDown(int puffle, bool down) {
	if (puffle > (int)this->doDown.size()) return; // Out of scope.
	this->doDown[puffle] = down;
}