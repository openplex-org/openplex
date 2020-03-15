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

#include "Void.hh"

#include <model/static/Tile.hh>
#include <model/dynamic/murphy/MoveOnVoid.hh>
#include <model/dynamic/freeFall/ZonkFreeFall.hh>

std::unique_ptr<Dynamic>
Void::getDynamicOn(GameState &gameState, Intent intent, Index self) const {
    switch (intent.variant) {
        case Variant::MurphyTryToEnter:
            return std::make_unique<MoveOnVoid>(gameState, intent.source, self);
        case Variant::ZonkEntered: {
            if (intent.source == gameState.level.above(self)) {
                int fallSource = intent.source;
                int fallDestination = self;
                return std::make_unique<ZonkFreeFall>(gameState, fallSource, fallDestination);
            } else {
                return nullptr;
            }
        }
        default:
            return nullptr;
    }
}
