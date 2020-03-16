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

#include <model/dynamic/Deterministic.hh>
#include <engine/game/GameState.hh>
#include <model/static/solid/Void.hh>
#include <model/static/marker/ZonkLeaving.hh>
#include <model/static/marker/ZonkEntering.hh>

#include <context/Renderer.hh>
#include <model/dynamic/Infinite.hh>
#include "EdgeSlip.hh"

struct ZonkEdgeSlip : public EdgeSlip {
    GameState &gameState;
    int slipFrom;
    int slipInto;
    int slipVoid;
    const int FRAMES = 30;
    int frameCountdown = 30;

    ZonkEdgeSlip(GameState &gameState, int slipFrom, int slipInto, int slipVoid) : gameState(gameState), slipFrom(slipFrom), slipInto(slipInto), slipVoid(slipVoid) {
    }

    std::vector<Index> area() const override {
        return {slipFrom, slipInto};
    }


    void spawn() override {
        gameState.level.storage[slipFrom] = std::make_unique<ZonkLeaving>();
        gameState.level.storage[slipInto] = std::make_unique<ZonkEntering>();
    }

    void update() override {
        frameCountdown--;
    }

    bool ready() override {
        return frameCountdown == 0;
    }

    void clean() override;

    float alpha(float f0, float f1) {
        return (f0 * frameCountdown + f1 * (FRAMES - frameCountdown)) / FRAMES;
    }

    void display(const Renderer &renderer) override {
        GLfloat x, y;
        GLfloat src_x, src_y;
        GLfloat dst_x, dst_y;
        int rotate = 0;
        computeloc(gameState, slipFrom, src_x, src_y);
        computeloc(gameState, slipInto, dst_x, dst_y);
        x = alpha(src_x, dst_x);
        y = alpha(src_y, dst_y);
        int roll_png_frames = 20;
        int roll_frame = ((FRAMES - frameCountdown) * roll_png_frames) / FRAMES;
        renderer.paint(gameState, x, y, roll_frame, Tileset::ZonkRoll, 0, slipFrom > slipInto ? 1 : 0);
    }
};


