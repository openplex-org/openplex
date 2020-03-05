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

#include <model/effects/Explosion.hh>

struct NPC {
/**
 * Initialize knick-knack or electrons at the start of the level
 * the procedure is the following:
 *  - by default turn left anticlockwise
 *  - if left is free skip one turn, done
 *  - if above is free move above rightaway, done
 *  - if right is free move right rightaway
 */
    static void init(GameState &gameState, int loc) {
        auto &level = gameState.level;
        auto &timing = gameState.gameTime;
        /*int base = level.ldt[loc].typ & 0xf0;
        int ABOVE = level.above(loc);
        int LEFTOF = level.leftof(loc);
        int RIGHTOF = level.rightof(loc);
        level.ldt[loc].set(base | TH_ANTICLOCK | TH_LEFT, timing.enemymove);
        if (level.ldt[LEFTOF].isfree()) {
            level.ldt[loc].counter = timing.enemymoveshort;
            return;
        }
        if (level.ldt[ABOVE].isfree()) {
            level.ldt[ABOVE].set(base | TH_UP | TH_MOVEIN, timing.enemymove);
            level.ldt[loc].set(TX_MOVEOUT | TH_UP, timing.enemymove);
            return;
        }
        if (level.ldt[RIGHTOF].isfree()) {
            level.ldt[RIGHTOF].set(base | TH_RIGHT | TH_MOVEIN, timing.enemymove);
            level.ldt[loc].set(TX_MOVEOUT | TH_RIGHT, timing.enemymove);
        }*/
    }

    static void step(GameState &gameState, int loc) {
        auto &level = gameState.level;
        auto &timing = gameState.gameTime;
/*        int typ = level.ldt[loc].typ;
        int base = typ & 0xf0;
        int thh = typ & 0x0c;
        int thd = typ & 0x03;
        int AHEAD, LEFT, RIGHT;
        if (level.ldt[loc].counter) return;
        // set ahead and left from the point of view of the enemy
        switch (thd) {
            case TH_UP:
                AHEAD = level.above(loc);
                LEFT = level.leftof(loc);
                RIGHT = level.rightof(loc);
                break;
            case TH_RIGHT:
                AHEAD = level.rightof(loc);
                LEFT = level.above(loc);
                RIGHT = level.below(loc);
                break;
            case TH_DOWN:
                AHEAD = level.below(loc);
                LEFT = level.rightof(loc);
                RIGHT = level.leftof(loc);
                break;
            default: // TH_LEFT
                AHEAD = level.leftof(loc);
                LEFT = level.below(loc);
                RIGHT = level.above(loc);
        }
        if (level.ldt[AHEAD].xtyp() == TX_MURPH) {
            gameState.ended = 1;
            Explosion::explode_region(gameState, AHEAD);
            return;
        }
        switch (thh) {
            case TH_ANTICLOCK:
                if (level.ldt[AHEAD].isfreeormurph()) {
                    // move ahead
                    level.ldt[AHEAD].set(base | TH_MOVEIN | thd, timing.enemymove);
                    level.ldt[loc].set(TX_MOVEOUT | thd, timing.enemymove);
                } else {
                    level.ldt[loc].set(base | TH_ANTICLOCK | ((thd - 1) & 3), timing.enemyrotate);
                }
                return;
            case TH_CLOCKWISE:
                if (level.ldt[AHEAD].isfreeormurph()) {
                    // move ahead
                    level.ldt[AHEAD].set(base | TH_MOVEIN | thd, timing.enemymove);
                    level.ldt[loc].set(TX_MOVEOUT | thd, timing.enemymove);
                } else {
                    level.ldt[loc].set(base | TH_CLOCKWISE | ((thd + 1) & 3), timing.enemyrotate);
                }
                return;
            default: // MOVE, or INVALID
                if (level.ldt[AHEAD].isfreeormurph() && !level.ldt[LEFT].isfreeormurph()) {
                    // move ahead
                    level.ldt[AHEAD].set(base | TH_MOVEIN | thd, timing.enemymove);
                    level.ldt[loc].set(TX_MOVEOUT | thd, timing.enemymove);
                    return;
                }
                if (level.ldt[RIGHT].isfreeormurph() && !level.ldt[LEFT].isfreeormurph()) {
                    // turn clockwise
                    level.ldt[loc].set(base | TH_CLOCKWISE | ((thd + 1) & 3), timing.enemyrotate);
                    return;
                }
                // default is same as left-turn
                level.ldt[loc].set(base | TH_ANTICLOCK | ((thd - 1) & 3), timing.enemyrotate);
                return;
        }*/
    }
};
