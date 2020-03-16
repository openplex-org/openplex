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

#include <vector>
#include <memory>

#include <model/static/Static.hh>
#include <model/static/solid/Hardware.hh>
#include <iostream>
#include "Index.hh"


using std::vector;
using std::unique_ptr;

struct Level {
    int width = 60;
    int height = 24;
    vector<unique_ptr<Static>> storage;

    unique_ptr<Static> &loc(int i) {
        return storage[i];
    }

    Level(int width = 60, int height = 24) : width(width),
                                             height(height),
                                             storage(width * height) {
        repairBorder();
    }

    void repairBorder() {
        for (int i = 1; i < width - 1; i++) {
            storage[i] = std::make_unique<Hardware>(Hardware::Style::Wall);
            storage[width * (height - 1) + i] = std::make_unique<Hardware>(Hardware::Style::Wall);
        }
        for (int i = 0; i < height; i++) {
            storage[i * width] = std::make_unique<Hardware>(Hardware::Style::Wall);
            storage[(i + 1) * width - 1] = std::make_unique<Hardware>(Hardware::Style::Wall);
        }
    }

    Index above(Index i) { return i - width; }

    Index below(Index i) { return i + width; }

    Index leftof(Index i) { return i - 1; }

    Index rightof(Index i) { return i + 1; }

    Index follow(Index i, Index j) { return 2 * j - i; }

    void console() {
        for (int iy = 0; iy < height; iy++) {
            for (int ix = 0; ix < width; ix++) {
                std::cout << storage[ix * height + iy]->print() << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    bool inside(int i) {
        return i >= 0 && i < width * height;
    }
};
