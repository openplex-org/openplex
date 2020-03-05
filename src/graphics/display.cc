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

#include <iostream>
#include <model/elements/FloppyYellow.hh>
#include <model/elements/SnikSnak.hh>
#include <model/elements/Electron.hh>
#include <model/elements/Infotron.hh>
#include <model/level/Level.hh>
#include <model/elements/Element.hh>
#include <model/effects/Vanish.hh>
#include "display.h"
#include "../engine/gamedata.h"
#include <assets/levels/levelset.h>
#include "status.h"
#include "../engine/timing.h"
#include "assets/sprites/sprites.h"
#include "engine/anim.h"
#include "../common/configuration.h"
#include "assets/fonts/font.h"

#include "../model/objMurphy.h"
#include "../common/SystemClock.hh"
#include <context/GameContext.hh>
#include <model/game/GameState.hh>

void computeloc(GameState &gameState, int loc, GLfloat &locx, GLfloat &locy, int flags) {
    auto &display = gameState.gameContext.display;
    auto lvlwidth = gameState.level.width;
    locx = (loc % lvlwidth) * display.ts - display.scrdx;
    locy = (loc / lvlwidth) * display.ts - display.scrdy;
/*    int typ = gameState.level.ldt[loc].typ & 0xff;
//	return;
    if (typ < 0x40) return;
    if (flags & 1) return;
    int disp = animprogress(gameState.level.ldt[loc].counter, gameState.gameTime.o8, -display.ts);
    if (((typ & 0x0c) == TH_MOVEDOUBLE) && ((typ & 0xf0) == TX_MURPH)) typ -= 4;
    switch (typ & 0x0f) {
        case TH_MOVEIN + TH_UP:
            locy -= disp;
            return;
        case TH_MOVEIN + TH_DOWN:
            locy += disp;
            return;
        case TH_MOVEIN + TH_LEFT:
            locx -= disp;
            return;
        case TH_MOVEIN + TH_RIGHT:
            locx += disp;
            return;
    }*/
}

void painttex(GameState &gameState, GLfloat x, GLfloat y, StaticTile staticTile, int rot, int flags) {
    painttex(gameState, x, y, static_cast<int>(staticTile), Tileset::Static, rot, flags);
}

void painttex(GameState &gameState, GLfloat x, GLfloat y, int tileindex, Tileset tileset, int rot, int flags) {
    auto &display = gameState.gameContext.display;
    int texid;
    GLfloat texl = 0;
    GLfloat texr = 1.0;
    GLfloat sp_width = display.ts;
    GLfloat sp_height = display.ts;
    texid = gettex(gameState.gameContext, tileset, tileindex);
    if (texid != 0) glBindTexture(GL_TEXTURE_2D, texid);
    else {
        glBindTexture(GL_TEXTURE_2D, 0);
        glColor4f(1, 0, 0, 1);
    }
    glPushMatrix();
    glTranslatef(x + display.ts * 0.5, y + display.ts * 0.5, 0);
    if (rot) {
        glRotatef(rot, 0, 0, 1);
    }
    if (flags & 1) {
        texl = 1.0;
        texr = 0;
    }
    if (flags & 2) {
        sp_width = display.ts * 0.8;
        sp_height = display.ts * 1.4;
    }
    sp_width *= 0.5;
    sp_height *= 0.5;
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(texl, 0.0);
    glVertex3f(-sp_width, -sp_height, 0);
    glTexCoord2f(texr, 0.0);
    glVertex3f(sp_width, -sp_height, 0);
    glTexCoord2f(texl, 1.0);
    glVertex3f(-sp_width, sp_height, 0);
    glTexCoord2f(texr, 1.0);
    glVertex3f(sp_width, sp_height, 0);
    glTexCoord2f(texl, 0.0);
    glVertex3f(-sp_width, -sp_height, 0);
    glTexCoord2f(texr, 0.0);
    glVertex3f(sp_width, -sp_height, 0);
    glEnd();
    glPopMatrix();
    glColor4f(1, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void renderscene(GameState &gameState) {
    auto &display = gameState.gameContext.display;
    int i, j;
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    gameState.timenow = SDL_GetTicks();

    if (gameState.level.ldt == NULL) return;
/*
    for (i = 0; i < gameState.level.height * gameState.level.width; i++) {
        int typ = gameState.level.ldt[i].typ;
        int tf = typ & 0xff;
        int painttyp = tf;

        if (tf >= 0x40) painttyp = 0;
        //if ((tf&0xf0)==TX_KNIK) painttyp=TB_INFOTRON;
        if ((tf & 0xf0) == 0xf0)
            painttyp = TB_MYTILE + (tf & 3);

        GLfloat x, y;
        computeloc(gameState, i, y, x);
        if (typ == TB_LEVTITLE) {
            if (y < -display.ts || y > display.scr_height) continue;
            int lnum = i / gameState.level.width / 2 - 1;
            int st = levelstate(lnum);
            if (st == 0) glColor4f(1, 0, 0, 1);
            else if (st == 1) glColor4f(1, 1, 0, 1);
            else glColor4f(0, 1, 0, 1);
            painttyp = 0;
            default_font.displayString(getlevelname(lnum).c_str(), x, y + display.ts * 0.9,
                                       display.ts);
            glColor4f(1, 1, 1, 1);
        } else if (painttyp) {
            //painttex(gameState, y, x, painttyp);
        }
    }
*/
    int loc = 0;
    for (int iy = 0; iy < gameState.level.height; iy++) {
        for (int ix = 0; ix < gameState.level.width; ix++) {
            if (gameState.level.storage[ix][iy])
                gameState.level.storage[ix][iy]->display(gameState, loc++);
        }
    }
/*
    for (int i = 0; i < gameState.level.width * gameState.level.height; i++) {
        int tx = gameState.level.ldt[i].xtyp();
        if (tx == TX_VANISHING) Vanish::display(gameState, i);
    }
*/
    display_status(gameState, gameState.infotronsneeded);
    display_fps(gameState, SystemClock::get_fps());
}



