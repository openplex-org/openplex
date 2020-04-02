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

#include <engine/game/GameState.hh>
#include <model/dynamic/Deterministic.hh>
#include <model/static/marker/core/ZonkEntering.hh>
#include <model/static/marker/core/ZonkLeaving.hh>
#include <model/static/solid/core/Void.hh>
#include <model/static/solid/core/Zonk.hh>

#include <renderer/Renderer.hh>

namespace op::core {
void ZonkEdgeSlip::clean() {
  gameState.level.storage[slipFrom] = std::make_unique<Void>();
  gameState.level.storage[slipInto] = std::make_unique<Zonk>();
  gameState.intents.emplace_back(slipFrom, Variant::BecomesVoid);
  gameState.intents.emplace_back(slipVoid, Variant::BecomesVoid);
}
}  // namespace op::core
