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
#include <engine/timing.h>
#include <engine/anim.h>
#include "model/static/Static.hh"
#include "model/dynamic/npc/NPC.hh"

struct SnikSnak : public Solid {
    void init(GameState &gameState, int loc) override {
        NPC::init(gameState, loc);
    }

    void display(GameState &gameState, int loc) override {
        GLfloat x, y;
        computeloc(gameState, loc, x, y);
        int rotation = 0;
/*        int typ=gameState.level.ldt[loc].typ;
        int thh=typ & 0x0c;
        int thd=typ & 0x03;
        if (thh==TH_ANTICLOCK) rotation=thd*90+animprogress(gameState.level.ldt[loc].counter,gameState.gameTime.enemyrotate,90);
        if (thh==TH_CLOCKWISE) rotation=thd*90-animprogress(gameState.level.ldt[loc].counter,gameState.gameTime.enemyrotate,90);
        if (thh==TH_MOVEIN) rotation=thd*90;*/
        painttex(gameState, x, y, 0, Tileset::SniksnakCut, rotation);
    }

    char print() override { return 'Y'; }
};

