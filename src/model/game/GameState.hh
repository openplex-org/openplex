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


#include <model/level/Level.hh>
#include <engine/timing.h>
#include <context/Display.hh>

struct GameContext;

struct GameState {
    GameState(GameContext &gameContext) : gameContext(gameContext) {}

    GameContext &gameContext;
    Level level;
    GameTime gameTime;

    int keydown[8];       /// keys currently being pressed: UP,RIGHT,DOWN,LEFT,SPACE
    int mode; //=0;
    int victory;          /// 1 if victory
    int ended;            /// whether the gameState ended, either win or lose
    int loadlevel;        /// whether a new level has to be loaded
    int lastlevel;        /// the last level that was loaded

    int gravity;          /// whether gravity is on
    int freezezonks;
    int freezeenemies;
    int infotrons;        /// infotrons in level
    int infotronsneeded;  /// infotrons needed to finish the level
    int reddiskcount;     /// number of red disks available
    int reddisklocation;  /// location of dropped red disk
    int reddisktimeout;   /// timeout of murphy laying a red disk

    int murphloc;         /// murphy's location
    int murphlastleft;    /// whether murphy's last move was to the left
    int murphsdinner;     /// type of tile currently being eaten
    int murphlookat;      /// direction murphy is looking into after grab
    int forcecenter = 1;      /// center on murphy at any cost

    int timestarted;      /// the time the level was started in milliseconds
    int timepaused;       /// the time the level was paused n/a
    int timenow;          /// time at current level updated
    int timelastmove;     /// time of the last step

    int sfxzonkleft;      /// for producing sound effects on zonk fall, stereo
    int sfxzonkright;
    int sfxexplodeleft;   /// for producing explosion sound effects, stereo
    int sfxexploderight;

    void init() {
        murphloc = 0;
        victory = 0;
        ended = 0;
        infotronsneeded = 0;
        loadlevel = 0;
        murphlastleft = 0;
        murphsdinner = 0;
        reddiskcount = 0;
        reddisktimeout = 0;
        reddisklocation = 0;
        timestarted = SDL_GetTicks();
        timelastmove = timestarted;
        freezeenemies = 0;
    }
};

