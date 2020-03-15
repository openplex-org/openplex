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

#include <engine/objMurphy.h>
#include "model/static/Tile.hh"
#include <context/GameContext.hh>
#include <engine/anim.h>

/** Murphy
 * base 60 frames per seconds;
 * frames:
 *  - before yawn - 600
 *  - scheduleSwallow - 20
 *  - move/eat base - 30
 */
struct MurphyFrames {
    static const int moving = 30;
    static const int swallowing = 30;
    static const int pushing = 30;
    static const int startPushing = 30;
};
enum class MurphyState {
    Idle,
    Yawning,
    FromLeft,
    FromRight,
    MovingTop,
    MovingBottom,
    MovingLeft,
    MovingRight,
    SwallowTop,
    SwallowBottom,
    SwallowLeft,
    SwallowRight,
    PushingLeft,
    PushingRight
};
struct Murphy : public Tile {
    int counter = 0;

    void init(GameState & gameState, int loc) override {
        gameState.murphloc = loc;
    }

    void display(GameState &gameState, int loc) override {



        auto &display = gameState.gameContext.display;
        auto &level = gameState.level;
        int murphprogress = animprogress(counter, gameState.gameTime.murphmove, 0, 7);
        GLfloat x, y;
        computeloc(gameState, loc, x, y);
        int t;
        counter++;
        counter %= 10 * 50;
        if (counter >= 100) {
            painttex(gameState, x, y, 0, Tileset::MurphyYawn, 0);
        } else {
            painttex(gameState, x, y, counter / 10, Tileset::MurphyYawn, 0);
        }
/*
        if (level.ldt[loc].movfull() == TH_VANISHING) {
            computeloc(gameState, loc, x, y);
            murphprogress = animprogress(counter, gameState.gameTime.murphvanishing, 0,
                                         spritecount(gameState.gameContext, TT_murphvanishing) - 1);
            painttex(gameState, x, y, murphprogress, TT_murphvanishing, 0);
            return;
        }

        if (level.ldt[loc].movtyp() == TH_MOVEIN && gameState.murphsdinner) {
            computeloc(gameState, loc, x, y, 1);
            painttex(gameState, x, y, gameState.murphsdinner, TT_tiles, 0);
        }
        computeloc(gameState, loc, x, y);
        painttex(gameState, x, y, murphprogress, TT_murphwalk, 0, gameState.murphlastleft);

        // Murph is passing through a port, draw murph twice and the port over him

        if (level.ldt[loc].movtyp() == TH_MOVEDOUBLE) {
            switch (level.ldt[loc].movdirection()) {
                case TH_UP:
                    painttex(gameState, y + display.ts, x, murphprogress, TT_murphwalk, 0, gameState.murphlastleft);
                    t = level.below(loc);
                    computeloc(gameState, t, x, y);
                    painttex(gameState, x, y, level.ldt[t].basetyp());
                    break;
                case TH_DOWN:
                    painttex(gameState, y - display.ts, x, murphprogress, TT_murphwalk, 0, gameState.murphlastleft);
                    t = level.above(loc);
                    computeloc(gameState, t, x, y);
                    painttex(gameState, x, y, level.ldt[t].basetyp());
                    break;
                case TH_LEFT:
                    painttex(gameState, x, y + display.ts, murphprogress, TT_murphwalk, 0, gameState.murphlastleft);
                    t = level.rightof(loc);
                    computeloc(gameState, t, x, y);
                    painttex(gameState, x, y, level.ldt[t].basetyp());
                    break;
                case TH_RIGHT:
                    painttex(gameState, x, y - display.ts, murphprogress, TT_murphwalk, 0, gameState.murphlastleft);
                    t = level.leftof(loc);
                    computeloc(gameState, t, x, y);
                    painttex(gameState, x, y, level.ldt[t].basetyp());
                    break;
            }
        }*/
    };


    char print() override { return '@';}
};

