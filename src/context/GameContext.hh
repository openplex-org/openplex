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

#include <model/game/GameState.hh>
#include <model/objMurphy.h>
#include <common/configuration.h>
#include <assets/Sprites.hh>
#include <model/effects/Vanish.hh>
#include <assets/Levels.hh>

struct GameContext {
    int levelIndex = 0;
    GameState gameState;
    Display &display;
    Sprites& sprites;
    Levels& levels;

    GameContext(Configuration& configuration, Sprites& sprites, Levels& levels) : gameState(*this), display(configuration.display), sprites(sprites), levels(levels) {
        levels.load(*this, levelIndex);
    }

    bool gameover = false;

    void playGame() {
        /*if (gameState.loadlevel) {
            if (gameState.loadlevel < 0) {
                // this should only happen on a level exit
                if (gameState.lastlevel > 0 && gameState.mode == 0)
                    finishlevel(gameState.lastlevel - 1, gameState.victory, gameState.timenow - gameState.timestarted);
                genmenulevel();
            } else if (!loadLevel(getleveldata(gameState.loadlevel - 1))) genmenulevel();
        }*/

        //zoomon_murphy(gameState, gameState.murphloc);

        //if (gameState.timenow - gameState.timelastmove > 30) {



        step();
            doobj_murphy(gameState, gameState.murphloc);



            //zoomon_murphy(gameState, gameState.murphloc);
/*            if (gameState.sfxexplodeleft || gameState.sfxexploderight) {
                sfx_start(SE_explosion);
                gameState.sfxexplodeleft = gameState.sfxexploderight = 0;
            }
            if (gameState.sfxzonkleft || gameState.sfxzonkright) {
                sfx_start(SE_hit);
                gameState.sfxzonkleft = gameState.sfxzonkright = 0;
            }
*/
        //}
    }

    void step() {
/*        gameState.timelastmove = gameState.timenow;
        int i, typ, tb, tx;
        for (i = gameState.level.width + 1; i < (gameState.level.height - 1) * gameState.level.width; i++) {
            gameState.level.ldt[i].oldtyp = gameState.level.ldt[i].typ;
        }
        for (i = gameState.level.width + 1; i < (gameState.level.height - 1) * gameState.level.width; i++) {
            int cnt = gameState.level.ldt[i].counter;
            if (cnt && (gameState.level.ldt[i].xtyp() == (gameState.level.ldt[i].oldtyp & 0xf0))) gameState.level.ldt[i].counter = --cnt;
            typ = gameState.level.ldt[i].typ;
            tx = typ & 0xf0;
            tb = typ & 0xff;
            // call the appropriate function based on object time

        switch (tx) {
            case TX_MOVEOUT: {
                if (!cnt) gameState.level.ldt[i].set(0);
                break;
            }
            case TX_VANISHING: {
                Vanish::step(gameState, i);
                break;
            }
        }
        }

    int loc = 0;
    for (int ix = 0; ix < gameState.level.width; ix++) {
        for (int iy = 0; iy < gameState.level.height; iy++) {
            gameState.level.storage[ix][iy]->step(gameState, loc++);
        }
    }*/
    }

};