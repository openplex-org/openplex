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

#include <memory>

#include <model/dynamic/Deterministic.hh>
#include <model/intent/Intent.hh>
#include <model/intent/Variant.hh>
#include <model/level/Index.hh>

#include "renderer/Renderer.hh"

struct GameState;

namespace op {
struct Static {
  virtual void init(GameState &gameState, Index index) {}

  virtual void display(Renderer &renderer, GameState &gameState, Index index) {}

  virtual bool isVoid() const { return false; }

  virtual bool isSlippery() const { return false; }

  /*
      virtual bool isSlippery(GameState& gameState, Index index) const {
          return false;
      }
  */
  enum SlipperySide { Left, Right } slipperySide;

  virtual SlipperySide getSlipperySide() const { return slipperySide; }

  virtual void scheduleSlip(SlipperySide nextSlipSide) { slipperySide = nextSlipSide; }

  virtual bool canMurphyEnter() const { return false; }
  virtual bool canNPCEnter() const { return false; }
  virtual bool canGhostEnter() const { return false; }

  virtual bool canMurphySnap() const { return false; }

  virtual bool canExplode() const { return true; }
  virtual bool isYellowFloppy() const { return false; }
  virtual bool isDeadly() const { return false; }

  virtual std::unique_ptr<Dynamic> getDynamicOn(GameState &gameState, Intent intentEntry, Index self) const {
    return nullptr;
  }
};
}  // namespace op