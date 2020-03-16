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

#include "MurphyPush.hh"

#include <engine/game/GameState.hh>
#include <model/static/marker/ZonkEntering.hh>
#include <model/static/marker/MurphyEntering.hh>
#include <model/static/marker/MurphyLeaving.hh>

#include <context/Renderer.hh>


struct PushZonk : public MurphyPush {
    GameState &gameState;
    Index src;
    Index dst;
    Index rollInto;
    const int PREP_FRAMES = 30;
    const int PUSH_FRAMES = 30;
    int prepFrameCountdown = PREP_FRAMES;
    int pushFrameCountdown = PUSH_FRAMES;
    bool interrupted = false;

    PushZonk(GameState &gameState, Index src, Index dst) : gameState(gameState), src(src), dst(dst) {
        rollInto = 2 * dst - src;
    }

    std::vector<Index> area() const override {
        if (prepFrameCountdown == 0) {
            return {src, dst};
        } else {
            return {src, dst, rollInto};
        }
    }


    void spawn() override {
    }

    void postponedSpawn() {
        if (gameState.level.storage[rollInto]->isVoid()) {
            gameState.level.storage[src] = std::make_unique<MurphyLeaving>();
            gameState.level.storage[dst] = std::make_unique<MurphyEntering>();
            gameState.level.storage[dst] = std::make_unique<ZonkEntering>();
        } else {
            interrupted = true;
        }
    }

    void update() override {
        if (interrupted) {
            return;
        }
        if (prepFrameCountdown > 0) {
            if (gameState.pressedFrames < PREP_FRAMES - prepFrameCountdown) {
                interrupted = true;
                return;
            }
            prepFrameCountdown--;
        } else {
            if (pushFrameCountdown == PUSH_FRAMES) {
                postponedSpawn();
            }
            pushFrameCountdown--;
        }
    }

    bool ready() override {
        if (interrupted) {
            return true;
        } else {
            return pushFrameCountdown == 0;
        }
    }

    void clean() override;

    float alpha(float f0, float f1) {
        return (f0 * pushFrameCountdown + f1 * (PUSH_FRAMES - pushFrameCountdown)) / PUSH_FRAMES;
    }

    void display(const Renderer &renderer) override {
        if (!interrupted) {
            {
                GLfloat x, y;
                GLfloat src_x, src_y;
                GLfloat dst_x, dst_y;
                int rotate = 0;
                computeloc(gameState, src, src_x, src_y);
                computeloc(gameState, dst, dst_x, dst_y);
                x = alpha(src_x, dst_x);
                y = alpha(src_y, dst_y);
                renderer.paint(gameState, x, y, 0, Tileset::MurphyFaces, 0, 0);
            }
            {
                GLfloat x, y;
                GLfloat src_x, src_y;
                GLfloat dst_x, dst_y;
                int rotate = 0;
                computeloc(gameState, dst, src_x, src_y);
                computeloc(gameState, rollInto, dst_x, dst_y);
                x = alpha(src_x, dst_x);
                y = alpha(src_y, dst_y);
                int roll_png_frames = 20;
                int roll_frame = ((PUSH_FRAMES - pushFrameCountdown) * roll_png_frames) / PUSH_FRAMES;
                renderer.paint(gameState, x, y, roll_frame, Tileset::ZonkRoll, 0, dst > rollInto ? 1 : 0);
            }
        }
    }
};
