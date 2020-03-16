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

#include <memory>

#include <common/openplex-gl.h>
#include <graphics/display.h>
#include <assets/sprites/sprites.h>
#include <model/dynamic/murphySnap/SnapBase.hh>
#include <model/dynamic/murphyMove/MoveOnBase.hh>
#include "model/static/Static.hh"
#include "Solid.hh"

struct Base : public Solid {

    void display(GameState &gameState, int loc) override {
        GLfloat x;
        GLfloat y;
        computeloc(gameState, loc, x, y);
        painttex(gameState, x, y, StaticTile::Base, 0);
    }

    char print() override { return '.'; }

    bool canEnter() const override {
        return true;
    }

    bool canSwallow() const override {
        return true;
    }

    bool isDeadly() const override {
        return false;
    }

    std::unique_ptr<Dynamic> getDynamicOn(GameState &gameState, Intent intent, Index self) const override {
        switch (intent.variant) {
            case Variant::MurphyTryToEnter:
                return std::make_unique<MoveOnBase>(gameState, intent.source, self);
            case Variant::MurphyTryToSwallow:
                return std::make_unique<SnapBase>(gameState, intent.source, self);
            default:
                return nullptr;
        }
    }
};

