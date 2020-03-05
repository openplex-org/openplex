// This file is a part of OpenPlex project.

// This is an open source port of Supaplex created in 1991 by:
//   Program ... Philip Jespersen
//   Graphics ..... Michael Stopp
//   PC Code ....... Robin Meydon
//   PC Graphics ..... Matt Smith
//   Music/FX ... David Whittaker
// Copyright (C) 2011 Radu Stefan <radu124@gmail.com>,
// Copyright (C) 2020 Aleksander Gajewski <aleksander@gajewski.fr>.

/*******************************************************************
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*******************************************************************/

#pragma once

#include <engine/gamedata.h>
#include "Element.hh"
#include <graphics/display.h>
#include <assets/sprites/sprites.h>

struct Terminal : public Element {
    static void touch_console(GameState& gameState) {
        /*int i, j;
        for (i = gameState.level.width + 1; i < (gameState.level.height - 1) * gameState.level.width; i++) {
            if (gameState.level.ldt[i].xtyp() == TX_YELLOW) Explosion::explode_region(gameState, i);
        }*/
    };

    void display(GameState& gameState, int loc) override {
        GLfloat x, y;
        int rotate = 0;
        computeloc(gameState, loc, x, y);
        painttex(gameState, x, y, rotate, Tileset::Terminal, 0);
    }

    char print() override { return 'T';}
};

