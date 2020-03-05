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

#include <model/elements/Element.hh>
#include <model/elements/Hardware.hh>
#include "Tile.hh"
#include <iostream>


using std::vector;
using std::unique_ptr;

struct Level {
    int width = 60;
    int height = 24;
    vector<vector<unique_ptr<Element>>> storage;

    vector<Tile> legacy_storage;
    Tile *ldt;

    unique_ptr<Element> &loc(int i) {
        return storage[i % width][i / width];
    }

    unique_ptr<Element> &decloc(int i) {
        return storage[i / height][i % height];
    }

    Level(int width = 60, int height = 24) : width(width),
                                             height(height),
                                             storage(width),
                                             legacy_storage(width * height),
                                             ldt(legacy_storage.data()) {
        for (auto &column : storage) {
            column.resize(height);
        }
        repairBorder();
    }

    void repairBorder() {
        for (auto &tile : storage.front()) {
            tile = make_unique<Hardware>(Hardware::Style::Wall);
        }
        for (auto &tile : storage.back()) {
            tile = make_unique<Hardware>(Hardware::Style::Wall);
        }
        for (auto &tileColumn : storage) {
            tileColumn.front() = make_unique<Hardware>(Hardware::Style::Wall);
            tileColumn.back() = make_unique<Hardware>(Hardware::Style::Wall);
        }
    }

    int above(int i) { return i - width; }

    int below(int i) { return i + width; }

    int leftof(int i) { return i - 1; }

    int rightof(int i) { return i - 1; }

    void console() {
        for (int iy = 0; iy < height; iy++) {
            for (int ix = 0; ix < width; ix++) {
                std::cout << storage[ix][iy]->print() << ' ';
            }
            std::cout << endl;
        }
        std::cout << endl;
    }
};
