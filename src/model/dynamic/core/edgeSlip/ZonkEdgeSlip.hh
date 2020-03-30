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
#include <model/static/marker/ZonkEntering.hh>
#include <model/static/marker/ZonkLeaving.hh>
#include <model/static/solid/core/Void.hh>

#include <renderer/Renderer.hh>
#include <model/dynamic/Infinite.hh>
#include "EdgeSlip.hh"

namespace op::core {
struct ZonkEdgeSlip : public EdgeSlip {
  int slipFrom;
  int slipInto;
  int slipVoid;
  const int FRAMES = 30;
  int frameCountdown = 30;

  ZonkEdgeSlip(GameState &gameState, int slipFrom, int slipInto, int slipVoid)
      : EdgeSlip(gameState), slipFrom(slipFrom), slipInto(slipInto), slipVoid(slipVoid) {}

  std::vector<Index> area() const override { return {slipFrom, slipInto}; }

  void spawn() override {
    gameState.level.storage[slipFrom] = std::make_unique<ZonkLeaving>();
    gameState.level.storage[slipInto] = std::make_unique<ZonkEntering>();
  }

  void update() override { frameCountdown--; }

  bool ready() override { return frameCountdown == 0; }

  void clean() override;

  void display(Renderer &renderer) override {
    auto anim = Progress{frameCountdown, FRAMES};
    renderer.paintMovingTile(gameState, TileSet::ZonkRoll, slipFrom, slipInto, anim);
  }
};
}  // namespace op::core
