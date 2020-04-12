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

#include <engine/game/GameState.hh>
#include "MurphyHit.hh"

namespace op::core {
struct HitTerminal : public MurphyHit {
  explicit HitTerminal(GameState& gameState) : MurphyHit(gameState) {}

  void spawn() {}

  void update() {}

  bool ready() { return true; }

  void clean() {
    Index index = 0;
    for (auto& tile : gameState.level.storage) {
      if (tile->isYellowFloppy()) {
        gameState.intents.emplace_back(index, Variant::NormalExplosionIgnition);
      }
      index++;
    }
  }

  void display(Renderer& renderer) {}

  std::vector<Index> area() const { return {}; }
};
}  // namespace op::core