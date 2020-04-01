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
#include <model/dynamic/core/edgeSlip/InfotronEdgeSlip.hh>
#include <model/dynamic/core/freeFall/InfotronFreeFall.hh>
#include <model/dynamic/core/freeFall/InfotronFreeFall.hh>
#include <model/dynamic/core/murphyMove/MoveOnInfotron.hh>
#include <model/dynamic/core/murphySnap/SnapInfotron.hh>
#include "model/static/Static.hh"

namespace op::core {
struct Infotron : public Solid {
  bool isSlippery() const override { return true; }

  bool canEnter() const override { return true; }

  bool canSnap() const override { return true; }

  void init(GameState &gameState, int loc) override { gameState.infotronsInLevel++; }

  void display(Renderer &renderer, GameState &gameState, Index index) override;

  static std::unique_ptr<Deterministic> getFreeFallDynamic(GameState &gameState, Index fallFrom, Index fallInto) {
    if (gameState.level.storage[fallInto]->isVoid()) {
      return std::make_unique<InfotronFreeFall>(gameState, fallFrom, fallInto);
    } else {
      return nullptr;
    }
  }

  static std::unique_ptr<Dynamic> getSlipDynamic(GameState &gameState, Index slipBase, Index slipFrom, Index slipInto,
                                                 Index slipVoid) {
    if (gameState.level.storage[slipBase]->isSlippery() && gameState.level.storage[slipInto]->isVoid() &&
        gameState.level.storage[slipVoid]->isVoid()) {
      return std::make_unique<InfotronEdgeSlip>(gameState, slipFrom, slipInto, slipVoid);
    } else {
      return nullptr;
    }
  }

  // handle 5 cases:
  //  - empty below
  //  - empty right/left - check row below
  //  - empty below right / below left - check within a row
  // ###############
  // #      #      #
  // # slip # slip #
  // # from # into #
  // #      #      #
  // ###############
  // #      #      #
  // # slip # slip #
  // # base # void #
  // #      #      #
  // ###############
  static std::unique_ptr<Dynamic> getGravityDynamic(GameState &gameState, Index safetyCheck, Index self) {
    if (safetyCheck != self) {
      return nullptr;
    }

    Index below = gameState.level.below(self);

    auto freeFall = getFreeFallDynamic(gameState, self, below);
    if (freeFall) {
      return std::move(freeFall);
    }
    Index sideLeft = gameState.level.leftof(self);
    Index belowLeft = gameState.level.below(sideLeft);

    Index sideRight = gameState.level.rightof(self);
    Index belowRight = gameState.level.below(sideRight);

    auto slipLeft = getSlipDynamic(gameState, below, self, sideLeft, belowLeft);
    auto slipRight = getSlipDynamic(gameState, below, self, sideRight, belowRight);

    if (!slipLeft) {
      if (slipRight) {
        gameState.level.storage[below]->scheduleSlip(SlipperySide::Left);
        return slipRight;
      } else {
        return nullptr;
      }
    } else if (slipRight) {
      // play with swapping state of slippery object
      if (gameState.level.storage[below]->getSlipperySide() == SlipperySide::Right) {
        gameState.level.storage[below]->scheduleSlip(SlipperySide::Left);
        return slipRight;
      } else {
        gameState.level.storage[below]->scheduleSlip(SlipperySide::Right);
        return slipLeft;
      }
    } else {
      gameState.level.storage[below]->scheduleSlip(SlipperySide::Right);
      return slipLeft;
    }
  }

  std::unique_ptr<Dynamic> getDynamicOn(GameState &gameState, Intent intent, Index self) const override {
    switch (intent.variant) {
      case Variant::MurphyTryToMove:
        return std::make_unique<MoveOnInfotron>(gameState, intent.source, self);
      case Variant::MurphyTryToSnap:
        return std::make_unique<SnapInfotron>(gameState, intent.source, self);
      case Variant::BecomesVoid:
        // ignore source of intent - there is a precondition that it comes from a void nearby
        return getGravityDynamic(gameState, self, self);
      case Variant::InfotronEntered:
        return getGravityDynamic(gameState, intent.source, self);
      default:
        return nullptr;
    }
  }
};
}  // namespace op::core