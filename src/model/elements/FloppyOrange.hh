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

#include <GL/gl.h>
#include <graphics/display.h>
#include <engine/gamedata.h>
#include <assets/sprites/sprites.h>
#include <engine/timing.h>
#include "Element.hh"

struct FloppyOrange : public Element {
    void step(GameState &gameState, int loc) override {
/*
        auto & level = gameState.level;
        auto & timing = gameState.gameTime;

        if (level.ldt[loc].counter != 0) return;
        if (level.ldt[level.below(loc)].isfree()) {
            level.ldt[level.below(loc)].set(TX_ORANGE | TH_MOVEIN | TH_DOWN, timing.zonkmove);
            level.ldt[loc].set(TX_MOVEOUT | TH_DOWN, timing.zonkmove);
            return;
        }
        if (level.ldt[loc].movdirection() == TH_DOWN) {
            // hit something
            Explosion::explode_region(gameState, loc);
        }
*/
    }

    void display(GameState& gameState, int loc) override {
        GLfloat x, y;
        computeloc(gameState, loc, y, x);
        painttex(gameState, y, x, StaticTile::FloppyOrange, 0);
    }

    char print() override { return '$';}
};