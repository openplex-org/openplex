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

#include <engine/game/GameState.hh>
#include <model/level/Clock.hh>
#include <model/render/Progress.hh>
#include <model/render/StaticTile.hh>

struct Renderer {
  virtual void initialize(GameState &gameState) = 0;

  virtual void renderFrame(GameState &gameState) = 0;

  virtual void paintTile(GameState &gameState, StaticTile tile, Index index) = 0;

  virtual void paintTile(GameState &gameState, TileSet tileset, Index index, Progress anim) = 0;

  virtual void paintDirectedTile(GameState &gameState, TileSet tileset, Direction direction, Index index,
                                 Progress anim) = 0;

  virtual void paintMovingTile(GameState &gameState, TileSet tileset, Index src, Index dst, Progress anim) = 0;

  virtual void paintMovingTile(GameState &gameState, StaticTile staticTile, Index src, Index dst, Progress anim) = 0;

  virtual void paintRotatedTile(GameState &gameState, StaticTile tile, Direction direction, Clock clock, Index index,
                                Progress anim) = 0;

  virtual void paintRotatedTile(GameState &gameState, TileSet tileset, Direction direction, Clock clock, Index index,
                                Progress anim) = 0;
};
