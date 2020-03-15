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

struct PreparePush : public Dynamic {
    GameState &gameState;
    Index src;
    Index dst;
    const int FRAMES = 30;
    int frameCountdown = FRAMES;

    PreparePush(GameState &gameState, Index src, Index dst) : gameState(gameState), src(src), dst(dst) {
    }

    std::vector<Index> area() const override {
        return {src, dst};
    }


    void spawn() override {
//        gameState.level.storage[src] = std::make_unique<ZonkLeaving>();
//        gameState.level.storage[dst] = std::make_unique<ZonkEntering>();
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
        computeloc(gameState, src, src_x, src_y);
        computeloc(gameState, dst, dst_x, dst_y);
        x = alpha(src_x, dst_x);
        y = alpha(src_y, dst_y);
        renderer.paint(gameState, x, y, StaticTile::Zonk, 0, 0);
    }

};