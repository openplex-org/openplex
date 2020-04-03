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

#include "model/static/solid/Solid.hh"

#include <memory>

#include <model/dynamic/core/murphyMove/MoveOnBase.hh>
#include <model/dynamic/core/murphySnap/SnapBase.hh>
#include <model/dynamic/ext/murphyMove/MoveOnGhostBase.hh>
#include <model/dynamic/ext/murphySnap/SnapGhostBase.hh>
#include "model/static/Static.hh"

namespace op::ext {
struct GhostBase : public Solid {
  void display(Renderer &renderer, GameState &gameState, Index index) override;

  bool canGhostEnter() const override { return true; }

  bool canMurphySnap() const override { return true; }

  bool isDeadly() const override { return false; }

  std::unique_ptr<Dynamic> getDynamicOn(GameState &gameState, Intent intent, Index self) const override {
    switch (intent.variant) {
      case Variant::MurphyTryToMove:
        return std::make_unique<MoveOnGhostBase>(gameState, intent.source, self);
      case Variant::MurphyTryToSnap:
        return std::make_unique<SnapGhostBase>(gameState, intent.source, self);
      default:
        return nullptr;
    }
  }
};
}  // namespace op::ext
