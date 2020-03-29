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

struct Renderer {
 private:
  void paint(GameState &gameState, GLfloat x, GLfloat y, StaticTile staticTile, float rot, int flags) const {
    painttex(gameState, x, y, static_cast<int>(staticTile), Tileset::Static, rot, flags);
  }

  void paint(GameState &gameState, GLfloat x, GLfloat y, int tileindex, Tileset tileset, float rot, int flags) const {
    painttex(gameState, x, y, tileindex, tileset, rot, flags);
  }

 public:
  void paintTile(GameState &gameState, StaticTile tile, Index index) const;

  void paintTile(GameState &gameState, Tileset tileset, Index index, Progress anim) const;

  void paintDirectedTile(GameState &gameState, Tileset tileset, Direction direction, Index index, Progress anim) const;

  void paintMovingTile(GameState &gameState, Tileset tileset, Index src, Index dst, Progress anim) const;

  void paintMovingTile(GameState &gameState, StaticTile staticTile, Index src, Index dst, Progress anim) const;

  void paintRotatedTile(GameState &gameState, StaticTile tile, Direction direction, Clock clock, Index index,
                        Progress anim) const;

  void paintRotatedTile(GameState &gameState, Tileset tileset, Direction direction, Clock clock, Index index,
                        Progress anim) const;
};
