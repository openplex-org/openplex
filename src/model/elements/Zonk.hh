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
#include <engine/gamedata.h>
#include <engine/timing.h>
#include <assets/sprites/sprites.h>
#include <engine/anim.h>
#include "Element.hh"

struct Zonk : public Element {
/*
    int zonktryfall(GameState& gameState, int loc) {
        int base = gameState.level.ldt[loc].xtyp();
        int BELOW = gameState.level.below(loc);
        if (gameState.level.ldt[BELOW].isfree()) {
            gameState.level.ldt[loc].set(TX_MOVEOUT | TH_DOWN, gameState.gameTime.zonkfall);
            gameState.level.ldt[BELOW].set(base | TH_MOVEIN | TH_DOWN, gameState.gameTime.zonkfall);
            return 1;
        }
        return 0;
    }

    int freeforroll(GameState& gameState, int loc) {
        int BELOWROLL = gameState.level.below(loc);
        return gameState.level.ldt[loc].isfree() && gameState.level.ldt[BELOWROLL].isfree();
    }

    int zonktryslip(GameState& gameState, int loc) {
        int base = gameState.level.ldt[loc].xtyp();
        int BELOW = gameState.level.below(loc);
        int LEFTOF = gameState.level.leftof(loc);
        int RIGHTOF = gameState.level.rightof(loc);

        if (gameState.level.ldt[BELOW].basetyp() != TX_INFOTRON &&
            gameState.level.ldt[BELOW].basetyp() != TX_ZONK &&
            !gameState.level.ldt[BELOW].isic())
            return 0;
        if (freeforroll(gameState, RIGHTOF)) {
            gameState.level.ldt[RIGHTOF].set(base | TH_MOVEIN | TH_RIGHT, gameState.gameTime.zonkmove);
            gameState.level.ldt[loc].set(TX_MOVEOUT | TH_RIGHT, gameState.gameTime.zonkmove);
            return 1;
        }
        if (freeforroll(gameState, LEFTOF)) {
            gameState.level.ldt[LEFTOF].set(base | TH_MOVEIN | TH_LEFT, gameState.gameTime.zonkmove);
            gameState.level.ldt[loc].set(TX_MOVEOUT | TH_LEFT, gameState.gameTime.zonkmove);
            return 1;
        }
        return 0;
    }

    int zonkhit(GameState& gameState, int loc, int base) {
        int BELOW = gameState.level.below(loc);
        gameState.sfxzonkleft = gameState.sfxzonkright = 1;
        if (gameState.level.ldt[BELOW].xtyp() == TX_ORANGE) {
            Explosion::explode_region(gameState, BELOW);
            return 1;
        }
        if (gameState.level.ldt[BELOW].xtyp() == TX_YELLOW && base == TX_INFOTRON) {
            Explosion::explode_region(gameState, BELOW);
            return 1;
        }
        if (gameState.level.ldt[BELOW].xtyp() == TX_MURPH) {
            Explosion::explode_region(gameState, BELOW);
            gameState.ended = 1;
            return 1;
        }
        return 0;
    }
*/
    void step(GameState &gameState, int loc) override {
        /*
        int base = gameState.level.ldt[loc].xtyp();
        int th = gameState.level.ldt[loc].typ & 0x0f;
        int BELOW = gameState.level.below(loc);
        if (gameState.level.ldt[loc].counter > 0) return;
        if (gameState.freezezonks) return;
        switch (th) {
            case TH_NORMAL:
                if (gameState.level.ldt[BELOW].isfree()) gameState.level.ldt[loc].set(base | TH_PREPAREFALL);
                if (zonktryslip(gameState, loc)) return;
                return;
            case TH_PREPAREFALL:
                if (zonktryfall(gameState, loc)) return;
                return;
            case TH_MOVEIN + TH_LEFT:
            case TH_MOVEIN + TH_RIGHT:
            case TH_MOVEIN + TH_DOWN:
                if (zonktryfall(gameState, loc)) return;
                if (zonkhit(gameState, loc, base)) return;
                if (zonktryslip(gameState, loc)) return;
                gameState.level.ldt[loc].set(base);
                return;
            default:
                gameState.level.ldt[loc].set(base);
                return;
        }
        */
    }

    void display(GameState& gameState, int loc) override {
        GLfloat x, y;
        int rotate = 0;
        computeloc(gameState, loc, x, y);
        /*
        if ((gameState.level.ldt[loc].typ & 0x0f) == TH_LEFT + TH_MOVEIN)
            rotate = animprogress(gameState.level.ldt[loc].counter, gameState.gameTime.zonkmove, spritecount(gameState.gameContext, TT_zonkroll), 0);
        if ((gameState.level.ldt[loc].typ & 0x0f) == TH_RIGHT + TH_MOVEIN)
            rotate = animprogress(gameState.level.ldt[loc].counter, gameState.gameTime.zonkmove, 0, spritecount(gameState.gameContext, TT_zonkroll));
        if (rotate == spritecount(gameState.gameContext, TT_zonkroll)) rotate = 0;
         */
        painttex(gameState, x, y, rotate, Tileset::ZonkRoll, 0);
    }

    char print() override { return 'o';}
};
