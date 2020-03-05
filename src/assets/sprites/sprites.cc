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
#include "sprites.h"

#include "common/includes.h"
#include "common/configuration.h"
#include "readpng.h"
#include <context/GameContext.hh>

int gettex(GameContext &gameContext, Tileset tileset, int tileindex) {
    if (tileindex >= gameContext.sprites.tiles[tileset].size()) return 0;
    return gameContext.sprites.tiles[tileset][tileindex];
}

int getelectronid(GameContext &gameContext, int time) {
    if (!gameContext.sprites.tiles[Tileset::Electron].size()) return 0;
    time /= 10;
    return time % gameContext.sprites.tiles[Tileset::Electron].size();
}

int spritecount(GameContext &gameContext, Tileset tileset) {
    return gameContext.sprites.tiles[tileset].size();
}




