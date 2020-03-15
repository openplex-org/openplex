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

#include "PushZonk.hh"

#include <model/dynamic/Dynamic.hh>
#include <engine/game/GameState.hh>
#include <model/static/solid/Void.hh>
#include <model/static/solid/Zonk.hh>
#include <model/static/marker/ZonkLeaving.hh>
#include <model/static/marker/ZonkEntering.hh>

#include <context/Renderer.hh>
#include <model/static/solid/Murphy.hh>

void PushZonk::clean() {
    if (!interrupted) {
        gameState.level.storage[src] = std::make_unique<Void>();
        gameState.level.storage[dst] = std::make_unique<Murphy>();
        gameState.level.storage[rollInto] = std::make_unique<Zonk>();
        gameState.intents.emplace_back(src, Variant::BecomesVoid);
        gameState.intents.emplace_back(rollInto, Variant::ZonkEntered);
        gameState.murphloc = dst;
    }
}

