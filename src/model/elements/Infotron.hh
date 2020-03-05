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

#include <common/openplex-gl.h>
#include <graphics/display.h>
#include <assets/sprites/sprites.h>
#include <engine/gamedata.h>
#include <engine/anim.h>
#include "Element.hh"

struct Infotron : public Element {
    void init(GameState & gameState, int loc) override {
        gameState.infotrons++;
    }

    void display(GameState& gameState, int loc) override {
        GLfloat x, y;
        int rotate = 0;
        computeloc(gameState, loc, x, y);
/*
        if ((gameState.level.ldt[loc].typ & 0x0f) == TH_LEFT + TH_MOVEIN)
            rotate = animprogress(gameState.level.ldt[loc].counter, gameState.gameTime.zonkmove, spritecount(gameState.gameContext, TT_tronroll), 0);
        if ((gameState.level.ldt[loc].typ & 0x0f) == TH_RIGHT + TH_MOVEIN)
            rotate = animprogress(gameState.level.ldt[loc].counter, gameState.gameTime.zonkmove, 0, spritecount(gameState.gameContext, TT_tronroll));
        if (rotate == spritecount(gameState.gameContext, TT_tronroll)) rotate = 0;*/
        painttex(gameState, x, y, rotate, Tileset::InfotronRoll, 0);
    }

    char print() override { return '&';}
};

