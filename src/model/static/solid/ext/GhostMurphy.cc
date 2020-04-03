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

#include <model/dynamic/ext/npc/GhostMurphyMove.hh>
#include "GhostMurphy.hh"

#include "engine/game/GameState.hh"

namespace op::ext {
void GhostMurphy::init(GameState &gameState, Index index) {
  gameState.intents.emplace_back(index, Variant::SpawnGhostMurphyMove);
}

std::unique_ptr<Dynamic> GhostMurphy::getDynamicOn(GameState &gameState, Intent intentEntry, Index self) const {
  switch (intentEntry.variant) {
    case Variant::SpawnGhostMurphyMove: {
      if (intentEntry.source == self) {
        return std::make_unique<op::ext::GhostMurphyMove>(gameState, self);
      } else {
        return nullptr;
      }
    }
    default:
      return nullptr;
  }
}

void GhostMurphy::display(Renderer &renderer, GameState &gameState, Index index) {
  renderer.paintTile(gameState, StaticTile::GhostMurphy, index);
};
}  // namespace op::ext