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

#include <assets/sprites/sprites.h>
#include <common/openplex-gl.h>
#include <graphics/display.h>
#include <model/dynamic/core/murphyHit/HitExit.hh>
#include "model/static/Static.hh"

namespace op::core {
struct Exit : public Solid {
  void display(Renderer &renderer, GameState &gameState, Index index) override;

  char print() override { return 'E'; }

  std::unique_ptr<Dynamic> getDynamicOn(GameState &gameState, Intent intent, Index self) const override {
    switch (intent.variant) {
      case Variant::MurphyTryToMove:
        if (gameState.infotronsCollected >= gameState.infotronsRequirement) {
          return std::make_unique<HitExit>(gameState, intent.source, self);
        } else {
          return nullptr;
        }
      default:
        return nullptr;
    }
  }
};
}  // namespace op::core
