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

#include <model/dynamic/Deterministic.hh>
#include <model/static/marker/core/ExplodingTile.hh>

#include "renderer/Renderer.hh"

#include "engine/game/GameState.hh"

namespace op::core {
struct NormalExplosion : public Deterministic {
  enum class AllowChainReaction { True, False };
  Index index;
  AllowChainReaction allowChainReaction;
  const int FRAMES = 30;
  int frameCountdown = FRAMES;
  NormalExplosion(GameState &gameState, Index index, AllowChainReaction allowChainReaction)
      : Deterministic(gameState), index(index), allowChainReaction(allowChainReaction) {}

  std::vector<Index> area() const override { return {index}; }

  void spawn() override {
    if (allowChainReaction == AllowChainReaction::True && !gameState.level.storage[index]->canExplode()) {
      allowChainReaction = AllowChainReaction::False;
    }
    gameState.level.storage[index] = std::make_unique<ExplodingTile>(*this);
  }

  void update() override { frameCountdown--; }

  bool ready() override { return frameCountdown == 0; }

  void clean() override;

  void display(Renderer &renderer) override {
    auto progress = Progress{FRAMES - frameCountdown, FRAMES};
    renderer.paintTile(gameState, TileSet::Explode, index, progress);
  }
};
}  // namespace op::core
