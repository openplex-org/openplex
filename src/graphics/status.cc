/*******************************************************************
(C) 2011 by Radu Stefan
radu124@gmail.com

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*******************************************************************/
#include "status.h"

#include "common/includes.h"
#include "assets/sprites/sprites.h"
#include "engine/gamedata.h"
#include "common/configuration.h"
#include "display.h"
#include <context/GameContext.hh>

void display_status(GameState &gameState, int infotronsneeded) {
    auto &display = gameState.gameContext.display;
    int posx = display.scr_width - display.ts;
    int x = infotronsneeded;
    int digitnr = 0;
    while (x > 0) {
        painttex(gameState, display.ts, display.scr_width - display.ts * 0.7 * digitnr - display.ts, x % 10, Tileset::Digits,
                 0, 2);
        x /= 10;
        digitnr++;
    }
}

void display_fps(GameState &gameState, int fps) {
    auto &display = gameState.gameContext.display;
    int x = fps;//gameState.infotronsneeded;
    int digitnr = 0;
    while (x > 0) {
        painttex(gameState, display.ts + 100, display.scr_width - display.ts * 0.7 * digitnr - display.ts, x % 10,
                 Tileset::Digits, 0, 2);
        x /= 10;
        digitnr++;
    }
}



