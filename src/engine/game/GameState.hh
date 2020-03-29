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

#include <deque>

#include <model/level/Level.hh>
#include <engine/timing.h>
#include <context/Display.hh>
#include <model/dynamic/Deterministic.hh>
#include <model/intent/Variant.hh>
#include <model/intent/Intent.hh>
#include <SDL_timer.h>
#include <SDL_keysym.h>

struct GameContext;

struct GameState {
    GameState(GameContext &gameContext) : gameContext(gameContext) {}

    GameContext &gameContext;
    op::Level level;
    std::vector<std::unique_ptr<op::Dynamic>> activeDynamics;
    std::vector<std::unique_ptr<op::Dynamic>> futureDynamics;
    std::vector<Intent> intents;

    GameTime gameTime;

    int frame = 0;
    bool allowMove = true;

    int infotronsInLevel = 0;
    int infotronsCollected = 0;
    int infotronsRequirement;  /// infotrons needed to finish the level
    int murphloc;         /// murphyMove's location
    int timestarted;      /// the time the level was started in milliseconds
    int timenow;          /// time at current level updated

    bool gravity = false;

    void init() {
        murphloc = 0;
        timestarted = SDL_GetTicks();
    }
};

