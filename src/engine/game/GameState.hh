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
#include <model/dynamic/Dynamic.hh>
#include <deque>
#include <model/intent/Variant.hh>
#include <model/intent/Intent.hh>
#include <SDL_timer.h>

struct GameContext;

enum class Direction {
    None,
    Up,
    Right,
    Left,
    Down
};

struct GameState {
    GameState(GameContext &gameContext) : gameContext(gameContext) {}

    GameContext &gameContext;
    Level level;
    std::vector<std::unique_ptr<Dynamic>> activeDynamics;
    std::vector<std::unique_ptr<Dynamic>> futureDynamics;
    std::vector<Intent> intents;

    GameTime gameTime;

    int frame = 0;
    bool allowMove = true;

    Direction scheduleMove = Direction::None;
    bool continueMove = false;
    int pressedFrames = 0;
    Direction scheduleSwallow = Direction::None;
    bool continueSwallow = false;
    bool isSpacePressed = false;


    int infotronsInLevel = 0;
    int infotronsCollected = 0;
    int infotronsRequirement;  /// infotrons needed to finish the level
    int murphloc;         /// murphy's location
    int timestarted;      /// the time the level was started in milliseconds
    int timenow;          /// time at current level updated

    bool gravity = false;

    void init() {
        murphloc = 0;
        timestarted = SDL_GetTicks();
    }
};

