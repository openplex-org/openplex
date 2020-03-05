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
#include <model/effects/Explosion.hh>
#include <model/level/Level.hh>
#include <model/elements/Terminal.hh>
#include "objMurphy.h"

#include "../common/includes.h"
#include "../engine/gamedata.h"
#include "../engine/timing.h"
#include "engine/anim.h"
#include "../graphics/display.h"
#include "assets/sprites/sprites.h"
#include "../common/configuration.h"

#include <context/GameContext.hh>
#include <assets/media/effects.h>
#include <assets/media/audiosfx.h>

/**
 * Try moving into a tile by eating its contents
 * (works even when the tile is empty)
 * @param loc - the location of Murphy
 * @param i - direction of movement
 * @param dest - destination tile
 * @return 1 on success
 */
int tryeating(GameState &gameState, int loc, int i, int dest) {
    auto &level = gameState.level;
/*    int result = level.ldt[dest].ispcb() || level.ldt[dest].isfree() || level.ldt[dest].xtyp() == TX_INFOTRON ||
                 level.ldt[dest].basetyp() == TB_RED;
    if (level.ldt[dest].isdeadly()) {
        gameState.ended = 1;
        Explosion::explode_region(gameState, loc);
        return 1;
    }
    if (!result) return 0;
    gameState.murphsdinner = level.ldt[dest].basetyp();
    level.ldt[dest].set(TX_MURPH + TH_MOVEIN + i, gameState.gameTime.murphmove);
    level.ldt[loc].set(TX_MOVEOUT + i, gameState.gameTime.murphmove);
    if ((gameState.murphsdinner & 0xf0) == TX_INFOTRON) {
        sfx_start(SE_infotron);
        if (gameState.infotronsneeded) gameState.infotronsneeded--;
        gameState.murphsdinner = TB_INFOTRON;
        if (gameState.mode == 1) gameState.lastlevel = gameState.loadlevel = (loc / gameState.level.width) / 2;
    }
    if (gameState.murphsdinner == TB_BASE) {
        sfx_start(SE_pcb);
    }
    if (gameState.murphsdinner == TB_RED) gameState.reddiskcount++;
    gameState.murphloc = dest;
    if (gameState.murphsdinner >= 0x40) gameState.murphsdinner = 0;
    if (i == 1) gameState.murphlastleft = 0;
    if (i == 3) gameState.murphlastleft = 1;*/
    return 1;
}

/**
 * Try moving through a port, the cell at the other side of the port
 * must be empty
 * @param loc - the location of Murphy
 * @param i - direction of movement
 * @param dest - port tile
 * @return 1 on success
 */
int tryport(GameState &gameState, int loc, int i, int dest) {
    auto &level = gameState.level;
/*    int fardest = dest * 2 - loc; // amplify delta
    if (i == 0 && !level.ldt[dest].isportup()) return 0;
    if (i == 1 && !level.ldt[dest].isportright()) return 0;
    if (i == 2 && !level.ldt[dest].isportdown()) return 0;
    if (i == 3 && !level.ldt[dest].isportleft()) return 0;
    if (!level.ldt[fardest].isfree()) return 0;
    gameState.murphloc = fardest;
    level.ldt[loc].set(TX_MOVEOUT | i, gameState.gameTime.murphmove);
    level.ldt[fardest].set(TX_MURPH | TH_MOVEDOUBLE | i, gameState.gameTime.murphmove);
    if (i == 1) gameState.murphlastleft = 0;
    if (i == 3) gameState.murphlastleft = 1;*/
}

/**
 * Try grabbing the contents of an adjacent tile
 * (works with pcb, red disks, and infotrons)
 * @param loc - the location of Murphy
 * @param i - direction of movement
 * @param dest - destination tile
 * @return 1 on success
 */
int trygrab(GameState &gameState, int loc, int i, int dest) {
    auto &level = gameState.level;
/*    if (level.ldt[dest].ispcb()) {
        // mind the bugs
        level.ldt[dest].set(TX_VANISHING | TB_BASE, gameState.gameTime.zonkmove);
        sfx_start(SE_pcb);
        return 1;
    }
    if (level.ldt[dest].basetyp() == TX_INFOTRON) {
        // only for infotrons at rest
        level.ldt[dest].set(TX_VANISHING | TB_INFOTRON, gameState.gameTime.zonkmove);
        sfx_start(SE_infotron);
        if (gameState.infotronsneeded) gameState.infotronsneeded--;
        return 1;
    }
    if (level.ldt[dest].basetyp() == TB_RED) {
        level.ldt[dest].set(TX_VANISHING | TV_REDDISK, gameState.gameTime.zonkmove);
        return 1;
    }*/
    return 0;
}

/**
 * Try pushing the contents of a tile
 * (works with zonks, orange disks and yellow disks,
 * yellow disks can also be pushed vertically)
 * @param loc - the location of Murphy
 * @param i - direction of movement
 * @param dest - destination tile
 * @return 1 on success
 */
int trypush(GameState &gameState, int loc, int i, int dest) {
    auto &level = gameState.level;
    // pushing should actually be done in two stages
    // we ignore that for now
/*    int typ = level.ldt[dest].basetyp();
    int fardest = dest * 2 - loc; // amplify displacement
    if (typ != TX_YELLOW && (i == TH_UP || i == TH_DOWN)) return 0;
    if (typ != TX_YELLOW && typ != TX_ORANGE && typ != TX_ZONK) return 0;
    if (!level.ldt[fardest].isfree()) return 0;
    level.ldt[fardest].set(typ | TH_MOVEIN | i, gameState.gameTime.zonkmove);
    level.ldt[dest].set(TX_MURPH | TH_MOVEIN | i, gameState.gameTime.zonkmove);
    level.ldt[loc].set(TX_MOVEOUT | i, gameState.gameTime.zonkmove);
    gameState.murphloc = dest;*/
    return 1;
}

/*
 * This is where the player actions are handled
 * very important
 *
 * actions, tested in this order can be
 * touch or run into EXIT
 * touch or run into CONSOLE
 * grab: PCB, REDDISK or Infotron
 */
void doobj_murphy(GameState &gameState, int loc) {
    auto &level = gameState.level;
    int dest[4];
    int i;
/*    if (gameState.ended) {
        if (level.ldt[loc].counter == 0) gameState.loadlevel = -1;
        return;
    }*/
    if (gameState.keydown[5]) {
        if (gameState.mode == 1) gameState.gameContext.gameover = 1;
        gameState.ended = 1;
        Explosion::explode_region(gameState, loc);
    }
    //if (level.ldt[loc].counter > 0) return;
    dest[0] = level.above(loc);
    dest[1] = level.rightof(loc);
    dest[2] = level.below(loc);
    dest[3] = level.leftof(loc);
    gameState.murphsdinner = 0;
/*    level.ldt[loc].set(TX_MURPH);
    for (i = 0; i < 4; i++)
        if (gameState.keydown[i]) {
            if (level.ldt[dest[i]].basetyp() == TB_EXIT && !gameState.infotronsneeded) {
                sfx_start(SE_victory);
                gameState.ended = 1;
                gameState.victory = 1;
                level.ldt[loc].set(TX_VANISHING | TB_MURPHY, gameState.gameTime.murphvanishing);
                return;
            }
            if (level.ldt[dest[i]].basetyp() == TB_CONSOLE) {
                gameState.murphlookat = i;
                Terminal::touch_console(gameState);
                return;
            }
            if (gameState.keydown[4]) {
                trygrab(gameState, loc, i, dest[i]);
                gameState.murphlookat = i;
                return;
            }
            if (tryeating(gameState, loc, i, dest[i])) return;
            if (tryport(gameState, loc, i, dest[i])) return;
            if (trypush(gameState, loc, i, dest[i])) return;
        }*/
};

void zoomon_murphy(GameState &gameState, int loc) {
    auto &display = gameState.gameContext.display;
    auto &level = gameState.level;
/*    GLfloat locx, locy;
    if (level.ldt[loc].xtyp() != TX_MURPH) return;
    locx = display.ts * (loc % gameState.level.width);
    locy = display.ts * (loc / gameState.level.width);
    int delta = animprogress(level.ldt[loc].counter, gameState.gameTime.murphmove, display.ts * 2, 0);
    if (level.ldt[loc].movtyp() == TH_MOVEIN) delta = trunc(delta / 2);
    else if (level.ldt[loc].movtyp() != TH_MOVEDOUBLE) delta = 0;
    switch (level.ldt[loc].movdirection()) {
        case TH_UP:
            locy += delta;
            break;
        case TH_DOWN:
            locy -= delta;
            break;
        case TH_LEFT:
            locx += delta;
            break;
        case TH_RIGHT:
            locx -= delta;
            break;
    }
    display.scrdx = locx - trunc(display.scr_width / 2 - display.ts / 2);
    display.scrdy = locy - trunc(display.scr_height / 2 - display.ts / 2);
    if (gameState.forcecenter) return;
    display.scrdx = max(0.0f, min((GLfloat) display.scrdx,
                                  static_cast<GLfloat>(display.ts * (gameState.level.width + 1) - display.scr_width)));
    display.scrdy = max(0.0f, min((GLfloat) display.scrdy,
                                  static_cast<GLfloat>(display.ts * (gameState.level.height) - display.scr_height)));
                                  */
}



