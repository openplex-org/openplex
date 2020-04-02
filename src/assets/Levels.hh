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

#include <assets/levels/levelset.h>
#include <assets/levels/core/LevelDecoder.hh>
#include <iomanip>
#include <iostream>

namespace op {
struct GameContext;
struct Levels {
  Levels() { load_levelset("data/levels/levels.dat"); }

  void load(GameContext &gameContext, int levelIndex) {
    std::cout << "[" << std::setfill('0') << std::setw(3) << (levelIndex + 1) << "] " << getlevelname(levelIndex)
              << std::endl;
    auto levelDecoder = op::core::LevelDecoder{};
    levelDecoder.loadLevel(gameContext, getleveldata(levelIndex));
  }
};
}  // namespace op