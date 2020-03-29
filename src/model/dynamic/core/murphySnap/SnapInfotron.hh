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
#include <model/dynamic/Deterministic.hh>
#include <model/static/marker/InfotronSnapped.hh>
#include <model/static/solid/core/Void.hh>
#include "MurphySnap.hh"

namespace op::core {
struct SnapInfotron : public MurphySnap {
  Index src;
  Index dst;
  const int FRAMES = 80;
  int frameCountdown = FRAMES;

  SnapInfotron(GameState &gameState, Index src, Index dst) : MurphySnap(gameState), src(src), dst(dst) {}

  std::vector<Index> area() const override { return {src, dst}; }

  void spawn() override {
    gameState.level.storage[dst] = std::make_unique<InfotronSnaped>();
    gameState.infotronsCollected++;
  }

  void update() override { frameCountdown--; }

  bool ready() override { return frameCountdown == 0; }

  void clean() override {
    gameState.level.storage[dst] = std::make_unique<Void>();
    gameState.intents.emplace_back(dst, Variant::BecomesVoid);
  }

  void display(const Renderer &renderer) override {
    auto progress = Progress{frameCountdown, FRAMES};
    renderer.paintTile(gameState, Tileset::InfotronVanish, dst, progress);
  }
};
}  // namespace op::core
