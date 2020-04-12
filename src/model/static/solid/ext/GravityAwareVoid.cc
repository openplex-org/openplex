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



#include "GravityAwareVoid.hh"

#include <model/dynamic/core/freeFall/ZonkFreeFall.hh>
#include <model/dynamic/core/murphyMove/MoveOnVoid.hh>

namespace op::ext {
std::unique_ptr<Dynamic> GravityAwareVoid::getDynamicOn(GameState &gameState, Intent intent, Index self) const {
  switch (intent.variant) {
    case Variant::MurphyTryToMove:
      return std::make_unique<op::core::MoveOnVoid>(gameState, intent.source, self);
    case Variant::ZonkRolled: {
      if (intent.source == gameState.level.above(self)) {
        int fallSource = intent.source;
        int fallDestination = self;
        return std::make_unique<op::core::ZonkFreeFall>(gameState, fallSource, fallDestination);
      } else {
        return nullptr;
      }
    }
    default:
      return nullptr;
  }
}
}  // namespace op::core