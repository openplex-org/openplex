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

#include "SnikSnak.hh"

#include "model/dynamic/core/npc/SnikSnakMove.hh"

namespace op::core {
void SnikSnak::init(GameState &gameState, Index index) {
  gameState.intents.emplace_back(index, Variant::SpawnSnikSnakMove);
}

std::unique_ptr<Dynamic> SnikSnak::getDynamicOn(GameState &gameState, Intent intentEntry, Index self) const {
  switch (intentEntry.variant) {
    case Variant::SpawnSnikSnakMove: {
      if (intentEntry.source == self) {
        return std::make_unique<SnikSnakMove>(gameState, self);
      } else {
        return nullptr;
      }
    }
    default:
      return nullptr;
  }
}

void SnikSnak::display(Renderer &renderer, GameState &gameState, Index index) {
  renderer.paintTile(gameState, StaticTile::SnikSnak, index);
}
}  // namespace op::core