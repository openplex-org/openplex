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

#include "Renderer.hh"

void Renderer::renderStatics(GameState &gameState) {
  const auto &height = gameState.level.height;
  const auto &width = gameState.level.width;
  for (int iy = 0; iy < gameState.level.height; iy++) {
    for (int ix = 0; ix < gameState.level.width; ix++) {
      if (gameState.level.storage[iy * width + ix])
        gameState.level.storage[iy * width + ix]->display(*this, gameState, gameState.level.getIndex(ix, iy));
    }
  }
}

void Renderer::renderDynamics(GameState &gameState) {
  for (auto &dynamic : gameState.activeDynamics) {
    dynamic->display(*this);
  }
}

void Renderer::renderFrame(GameState &gameState) {
  doBeforeFrame(gameState);
  renderStatics(gameState);
  renderDynamics(gameState);
  doRenderOverlay(gameState);
  doRenderFrame(gameState);
}
