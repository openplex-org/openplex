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

#include <common/openplex-gl.h>
#include <graphics/display.h>
#include <assets/sprites/sprites.h>
#include "model/static/Tile.hh"

struct Port : public Tile {
    enum class Style {
        Right = static_cast<int>(StaticTile::PortRight),
        Down = static_cast<int>(StaticTile::PortDown),
        Left = static_cast<int>(StaticTile::PortLeft),
        Up = static_cast<int>(StaticTile::PortUp),
        Vertical = static_cast<int>(StaticTile::PortVertical),
        Horizontal = static_cast<int>(StaticTile::PortHorizontal),
        Cross = static_cast<int>(StaticTile::PortCross)
    };

    Style style;

    Port(Style style) : style(style) {}

    void display(GameState &gameState, int loc) override {
        GLfloat x;
        GLfloat y;
        computeloc(gameState, loc, x, y);
        painttex(gameState, x, y, static_cast<StaticTile>(style), 0);
    }

    char print() override {
        switch(style) {
            case Style::Up:
                return 30; //'A';
            case Style::Down:
                return 31; //'V';
            case Style::Left:
                return 17; //'<';
            case Style::Right:
                return 16; ////'>';
            case Style::Vertical:
                return 18; ////'H';
            case Style::Horizontal:
                return 29; ////'=';
            case Style::Cross:
                return 4; ////'+';
            default:
                return ' ';
        }
    }
};
