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

#include <model/dynamic/core/explode/NormalExplosion.hh>
#include <model/dynamic/core/freeFall/FloppyOrangeFreeFall.hh>
#include <model/dynamic/core/murphyPush/PreparePush.hh>
#include "model/static/solid/Solid.hh"

#include "engine/game/GameState.hh"

namespace op::core {
struct FloppyOrange : public Solid {
  void display(Renderer &renderer, GameState &gameState, Index index) override;

  std::unique_ptr<Dynamic> getDynamicOn(GameState &gameState, Intent intentEntry, Index self) const override {
    switch (intentEntry.variant) {
      case Variant::BecomesVoid:
        if (gameState.level.above(intentEntry.source) == self) {
          return std::make_unique<FloppyOrangeFreeFall>(gameState, self, intentEntry.source);
        } else {
          return nullptr;
        }
      case Variant::FloppyOrangeFallen: {
        Index dst = gameState.level.below(intentEntry.source);
        if (gameState.level.storage[dst]->isVoid()) {
          return std::make_unique<FloppyOrangeFreeFall>(gameState, intentEntry.source, dst);
        } else {
          return nullptr;
        }
      }
      case Variant::NormalExplosionIgnition: {
        if (intentEntry.source == self) {
          return std::make_unique<NormalExplosion>(gameState, self, NormalExplosion::AllowChainReaction::False);
        } else {
          return std::make_unique<NormalExplosion>(gameState, self, NormalExplosion::AllowChainReaction::True);
        }
      }
      case Variant::MurphyTryToMove: {
        Index next = gameState.level.follow(intentEntry.source, self);
        if (gameState.level.storage[next]->isVoid()) {
          return std::make_unique<PreparePush>(gameState, intentEntry.source, self);
        } else {
          return nullptr;
        }
      }
      default:
        return nullptr;
    }
  }
};
}  // namespace op::core