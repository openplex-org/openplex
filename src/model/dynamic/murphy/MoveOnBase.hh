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

#include <model/dynamic/Dynamic.hh>
#include <engine/game/GameState.hh>
#include <model/static/marker/MurphyLeaving.hh>
#include <model/static/marker/BaseEaten.hh>
#include <model/static/solid/Murphy.hh>
#include <model/static/solid/Void.hh>

#include <context/Renderer.hh>

struct MoveOnBase : public Dynamic {
    GameState &gameState;
    Index src;
    Index dst;
    const int FRAMES = 15;
    int frameCountdown = FRAMES;

    MoveOnBase(GameState &gameState, Index src, Index dst) : gameState(gameState), src(src), dst(dst) {
    }

    std::vector<Index> area() const override {
        return {src, dst};
    }


    void spawn() override {
        gameState.level.storage[src] = std::make_unique<MurphyLeaving>();
        gameState.level.storage[dst] = std::make_unique<BaseEaten>();
        gameState.allowMove = false;
        gameState.murphloc = dst;
    }

    void update() override {
        frameCountdown--;
    }

    bool ready() override {
        return frameCountdown == 0;
    }

    void clean() override {
        gameState.level.storage[src] = std::make_unique<Void>();
        gameState.level.storage[dst] = std::make_unique<Murphy>();

        gameState.intents.emplace_back(src, Variant::BecomesVoid);
        gameState.allowMove = true;
    }

    float alpha(float f0, float f1) {
        return (f0 * frameCountdown + f1 * (FRAMES - frameCountdown)) / FRAMES;
    }

    void display(const Renderer &renderer) override {
        GLfloat x, y;
        GLfloat src_x, src_y;
        GLfloat dst_x, dst_y;
        int rotate = 0;
        computeloc(gameState, src, src_x, src_y);
        computeloc(gameState, dst, dst_x, dst_y);
        x = alpha(src_x, dst_x);
        y = alpha(src_y, dst_y);
        int murphy_png_frames = 20;
        int murphy_frame = ((FRAMES - frameCountdown) * murphy_png_frames) / FRAMES;
        renderer.paint(gameState, x, y, murphy_frame, Tileset::MurphyWalk, 0, 0);
    }
};

