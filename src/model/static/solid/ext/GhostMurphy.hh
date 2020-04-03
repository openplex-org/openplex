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

#include <model/static/marker/ext/GhostMurphyEntering.hh>
#include <model/static/marker/ext/GhostMurphyLeaving.hh>
#include "model/static/solid/Solid.hh"

namespace op::ext {
struct GhostMurphy : public Solid {
  using EnteringType = GhostMurphyEntering;
  using LeavingType = GhostMurphyLeaving;

  void init(GameState &gameState, Index index) override;

  std::unique_ptr<Dynamic> getDynamicOn(GameState &gameState, Intent intentEntry, Index self) const;

  void display(Renderer &renderer, GameState &gameState, Index index) override;

  static bool canEnter(Static &tile) { return tile.canGhostEnter(); }
};
}  // namespace op::ext