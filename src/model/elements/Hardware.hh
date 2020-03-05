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

#include <graphics/display.h>
#include <assets/sprites/sprites.h>
#include <assets/Sprites.hh>

struct Hardware : public Element {
    enum class Style {
        Wall = static_cast<int>(StaticTile::Wall),
        Hardware1 = static_cast<int>(StaticTile::Hardware1),
        Hardware2 = static_cast<int>(StaticTile::Hardware2),
        Hardware3 = static_cast<int>(StaticTile::Hardware3),
        Hardware4 = static_cast<int>(StaticTile::Hardware4),
        Hardware5 = static_cast<int>(StaticTile::Hardware5),
        Hardware6 = static_cast<int>(StaticTile::Hardware6),
        Hardware7 = static_cast<int>(StaticTile::Hardware7),
        Hardware8 = static_cast<int>(StaticTile::Hardware8),
        Hardware9 = static_cast<int>(StaticTile::Hardware9),
        Hardware10 = static_cast<int>(StaticTile::Hardware10)
    };

    Style style;

    explicit Hardware(Style style) : style(style) {}

    void display(GameState &gameState, int loc) override {
        GLfloat x;
        GLfloat y;
        int rotate = 0;
        computeloc(gameState, loc, x, y);
        painttex(gameState, x, y, static_cast<StaticTile>(style), 0);
    }

    char print() override { return '#'; }
};

