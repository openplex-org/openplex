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

#include "MurphyHit.hh"

#include <renderer/Renderer.hh>
#include <engine/game/GameState.hh>
#include <model/static/marker/MurphyVanishing.hh>
#include <model/static/solid/core/Void.hh>

namespace op::core {
struct HitExit : public MurphyHit {
  Index src;
  Index dst;
  const int FRAMES = 80;
  int frameCountdown = FRAMES;

  HitExit(GameState &gameState, Index src, Index dst) : MurphyHit(gameState), src(src), dst(dst) {}

  std::vector<Index> area() const override { return {src, dst}; }

  void spawn() override { gameState.level.storage[src] = std::make_unique<MurphyVanishing>(); }

  void update() override { frameCountdown--; }

  bool ready() override { return frameCountdown == 0; }

  void clean() override {
    gameState.level.storage[dst] = std::make_unique<Void>();
    gameState.intents.emplace_back(dst, Variant::BecomesVoid);
  }

  void display(Renderer &renderer) override {
    auto anim = Progress{frameCountdown, FRAMES};
    renderer.paintTile(gameState, TileSet::MurphyVanish, dst, anim);
  }
};
}  // namespace op::core
