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
#include <assets/sprites/sprites.h>
#include <engine/timing.h>
#include <graphics/display.h>
#include <engine/anim.h>
#include <model/game/GameState.hh>

struct Vanish {
    static void step(GameState &gameState, int loc) {
        auto &level = gameState.level;
/*        if (level.ldt[loc].counter) return;
        if (level.ldt[loc].movfull() == TV_EXPLODEINFO) level.ldt[loc].set(TX_INFOTRON);
        else level.ldt[loc].set(0);*/
    }

    static void display(GameState &gameState, int loc) {
/*
        int typ = gameState.level.ldt[loc].movfull();
        int tileset = TT_murphvanishing;
        int progress;
        progress = gameState.gameTime.zonkmove;
        switch (typ) {
            case TB_BASE:
                tileset = TT_vanishpcb;
                break;
            case TB_MURPHY:
                tileset = TT_murphvanishing;
                progress = gameState.gameTime.murphvanishing;
                break;
            case TB_INFOTRON:
                tileset = TT_vanishinfo;
                break;
            case TV_REDDISK:
                tileset = TT_vanishdisk;
                break;
            case TV_EXPLODE:
                tileset = TT_explode;
                progress = gameState.gameTime.explosion;
                break;
            case TV_EXPLODEINFO:
                tileset = TT_explodeinfo;
                progress = gameState.gameTime.explosion;
                break;
        }*/

        /*
        GLfloat x, y;
        computeloc(gameState, loc, y, x, 1);
        progress = animprogress(gameState.level.ldt[loc].counter, progress, 0,
                                spritecount(gameState.gameContext, tileset) - 1);
        painttex(gameState, y, x, progress, tileset, 0);
         */
    }
};