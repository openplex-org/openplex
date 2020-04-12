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

#include "ZonkFreeFall.hh"

#include <engine/game/GameState.hh>
#include <model/dynamic/Deterministic.hh>
#include <model/static/marker/core/ZonkEntering.hh>
#include <model/static/marker/core/ZonkLeaving.hh>
#include <model/static/solid/core/Void.hh>
#include <model/static/solid/core/Zonk.hh>

#include <model/static/solid/core/FloppyOrange.hh>
#include <renderer/Renderer.hh>

namespace op::core {
void FloppyOrangeFreeFall::clean() {
  gameState.level.storage[src] = std::make_unique<Void>();
  gameState.level.storage[dst] = std::make_unique<FloppyOrange>();
  gameState.intents.emplace_back(src, Variant::BecomesVoid);
  if (gameState.level.storage[gameState.level.below(dst)]->isVoid()) {
    gameState.intents.emplace_back(dst, Variant::FloppyOrangeFallen);
  } else {
    gameState.intents.emplace_back(dst, Variant::NormalExplosionIgnition);
  }
}

}  // namespace op::core