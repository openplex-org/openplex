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

#include <engine/timing.h>
#include <engine/game/GameState.hh>
#include <model/level/Level.hh>

namespace op::core {
struct Explosion {
  static void explode_region(GameState &gameState, int loc) {
    int j;
    for (j = -1; j < 2; j++) {
      explode_tile(gameState, gameState.level.above(loc) + j);
      explode_tile(gameState, loc + j);
      explode_tile(gameState, gameState.level.below(loc) + j);
    }
  }

  static void explode_tile(GameState &gameState, int loc) {
    /*        int typ = gameState.level.ldt[loc].typ;
            if (gameState.level.ldt[loc].typ & TF_SOLID) return;
            gameState.level.ldt[loc].set(TX_VANISHING | TV_EXPLODE, gameState.gameTime.explosion);
            gameState.sfxexplodeleft = gameState.sfxexploderight = 1;*/
  }
};
}  // namespace op::core