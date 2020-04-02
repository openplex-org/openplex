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

#include <renderer/Renderer.hh>
#include <engine/game/GameState.hh>
#include <model/static/marker/core/MurphyEntering.hh>
#include <model/static/marker/core/MurphyLeaving.hh>
#include <model/static/solid/core/Murphy.hh>
#include <model/static/solid/core/Void.hh>
#include "MurphyMove.hh"

namespace op::core {
struct MoveOnVoid : public MurphyMove {
  Index src;
  Index dst;
  int FRAMES = 15;
  int frameCountdown = FRAMES;

  MoveOnVoid(GameState &gameState, Index src, Index dst) : MurphyMove(gameState), src(src), dst(dst) {}

  std::vector<Index> area() const override { return {src, dst}; }

  void spawn() override {
    gameState.level.storage[src] = std::make_unique<MurphyLeaving>();
    gameState.level.storage[dst] = std::make_unique<MurphyEntering>();
    gameState.allowMove = false;
    gameState.murphloc = dst;
  }

  void update() override { frameCountdown--; }

  bool ready() override { return frameCountdown == 0; }

  void clean() override {
    gameState.level.storage[src] = std::make_unique<Void>();
    gameState.level.storage[dst] = std::make_unique<Murphy>();

    gameState.intents.emplace_back(src, Variant::BecomesVoid);
    gameState.allowMove = true;
  }

  float alpha(float f0, float f1) { return (f0 * frameCountdown + f1 * (FRAMES - frameCountdown)) / FRAMES; }

  void display(Renderer &renderer) override {
    auto anim = Progress{frameCountdown, FRAMES};
    renderer.paintMovingTile(gameState, TileSet::MurphyWalk, src, dst, anim);
  }
};
}  // namespace op::core