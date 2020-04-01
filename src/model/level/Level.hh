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

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include <iostream>
#include <model/static/Static.hh>
#include <model/static/solid/core/Hardware.hh>
#include "Direction.hh"
#include "Index.hh"

namespace op {

struct Level {
  int width = 60;
  int height = 24;
  std::vector<std::unique_ptr<Static>> storage;
  std::unordered_map<Direction, std::function<Index(Index)>> followLookup;

  std::unique_ptr<Static> &loc(int i) { return storage[i]; }

  Level(int width = 60, int height = 24) : width(width), height(height), storage(width * height) {
    repairBorder();

    followLookup = std::unordered_map<Direction, std::function<Index(Index)>>{
        {Direction::Up, [&](Index index) { return this->above(index); }},
        {Direction::Right, [&](Index index) { return this->rightof(index); }},
        {Direction::Down, [&](Index index) { return this->below(index); }},
        {Direction::Left, [&](Index index) { return this->leftof(index); }},
        {Direction::None, [&](Index index) { return index; }}};
  }

  void repairBorder() {
    for (int i = 1; i < width - 1; i++) {
      storage[i] = std::make_unique<core::Hardware>(core::Hardware::Style::Wall);
      storage[width * (height - 1) + i] = std::make_unique<core::Hardware>(core::Hardware::Style::Wall);
    }
    for (int i = 0; i < height; i++) {
      storage[i * width] = std::make_unique<core::Hardware>(core::Hardware::Style::Wall);
      storage[(i + 1) * width - 1] = std::make_unique<core::Hardware>(core::Hardware::Style::Wall);
    }
  }

  int getX(Index index) { return static_cast<int>(index) % width; }

  int getY(Index index) { return static_cast<int>(index) / width; }

  Index getIndex(int x, int y) { return y * width + x; }

  Index above(Index i) { return i - width; }

  Index below(Index i) { return i + width; }

  Index leftof(Index i) { return i - 1; }

  Index rightof(Index i) { return i + 1; }

  Index follow(Index i, Index j) { return follow(j, getDirection(i, j)); }

  Index follow(Index index, Direction direction) { return followLookup.at(direction)(index); }

  Direction getDirection(Index from, Index to) {
    if (to == rightof(from)) {
      return Direction::Right;
    } else if (to == leftof(from)) {
      return Direction::Left;
    } else if (to == above(from)) {
      return Direction::Up;
    } else if (to == below(from)) {
      return Direction::Down;
    } else {
      return Direction::None;
    }
  }

  bool inside(int i) { return i >= 0 && i < width * height; }
};
}  // namespace op