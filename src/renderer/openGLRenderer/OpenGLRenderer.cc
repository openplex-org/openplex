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

#include "OpenGLRenderer.hh"

#include "engine/game/GameState.hh"

#include "context/GameContext.hh"

inline constexpr float getAlphaMix(float f0, float f1, int count, int total) {
  return (f0 * static_cast<float>(count) + f1 * static_cast<float>(total - count)) / total;
}

inline constexpr float getAlphaMix(float f0, float f1, Progress anim) {
  return getAlphaMix(f0, f1, anim.count, anim.total);
}

inline constexpr int getSpriteIndex(int sprites, Progress anim) { return (sprites * anim.count) / anim.total; }

void OpenGLRenderer::paintTile(GameState &gameState, StaticTile tile, Index index) {
  GLfloat x, y;
  computeloc(gameState, index, x, y);
  painttex(gameState, x, y, tile, 0, 0);
}

void OpenGLRenderer::paintTile(GameState &gameState, TileSet tileset, Index index, Progress anim) {
  GLfloat x, y;
  computeloc(gameState, index, x, y);
  const int spriteFrames = gameState.gameContext.sprites.tiles[tileset].size();
  const int spriteIndex = getSpriteIndex(spriteFrames, anim);
  painttex(gameState, x, y, spriteIndex, tileset, 0, 0);
}

void OpenGLRenderer::paintDirectedTile(GameState &gameState, TileSet tileset, Direction direction, Index index,
                                       Progress anim) {
  GLfloat x, y;
  computeloc(gameState, index, x, y);

  const int spriteFrames = gameState.gameContext.sprites.tiles[tileset].size();
  const int spriteIndex = getSpriteIndex(spriteFrames, anim);
  switch (direction) {
    case Direction::Right:
      painttex(gameState, x, y, spriteIndex, tileset, 0, 0);
      break;
    case Direction::Left:
      painttex(gameState, x, y, spriteIndex, tileset, 0, 1);
      break;
    case Direction::Up:
      painttex(gameState, x, y, spriteIndex, tileset, 90, 0);
      break;
    case Direction::Down:
      painttex(gameState, x, y, spriteIndex, tileset, -90, 0);
      break;
    default:
      break;
  }
}

void OpenGLRenderer::paintMovingTile(GameState &gameState, TileSet tileset, Index src, Index dst, Progress anim) {
  GLfloat x, y;
  GLfloat src_x, src_y;
  GLfloat dst_x, dst_y;
  computeloc(gameState, src, src_x, src_y);
  computeloc(gameState, dst, dst_x, dst_y);
  x = getAlphaMix(src_x, dst_x, anim);
  y = getAlphaMix(src_y, dst_y, anim);

  const Direction direction = gameState.level.getDirection(src, dst);

  const int spriteFrames = gameState.gameContext.sprites.tiles[tileset].size();
  const int spriteIndex = getSpriteIndex(spriteFrames, anim);
  switch (direction) {
    case Direction::Right:
      painttex(gameState, x, y, spriteIndex, tileset, 0, 0);
      break;
    case Direction::Left:
      painttex(gameState, x, y, spriteIndex, tileset, 0, 1);
      break;
    case Direction::Up:
      painttex(gameState, x, y, spriteIndex, tileset, 90, 0);
      break;
    case Direction::Down:
      painttex(gameState, x, y, spriteIndex, tileset, -90, 0);
      break;
    default:
      break;
  }
}

void OpenGLRenderer::paintMovingTile(GameState &gameState, StaticTile staticTile, Index src, Index dst, Progress anim) {
  GLfloat x, y;
  GLfloat src_x, src_y;
  GLfloat dst_x, dst_y;
  computeloc(gameState, src, src_x, src_y);
  computeloc(gameState, dst, dst_x, dst_y);
  x = getAlphaMix(src_x, dst_x, anim);
  y = getAlphaMix(src_y, dst_y, anim);

  painttex(gameState, x, y, staticTile, 0, 0);
}

void OpenGLRenderer::paintRotatedTile(GameState &gameState, StaticTile tile, Direction direction, Clock clock,
                                      Index index, Progress anim) {
  GLfloat x, y;
  computeloc(gameState, index, x, y);

  const Direction towardsDirection = rotate(direction, clock);
  const int fromAngle = getRotationDegrees(direction);
  const int towardsAngle = getRotationDegrees(towardsDirection);
  const float angle = getAlphaMix(fromAngle, towardsAngle, anim);

  painttex(gameState, x, y, tile, angle);
}

void OpenGLRenderer::paintRotatedTile(GameState &gameState, TileSet tileset, Direction direction, Clock clock,
                                      Index index, Progress anim) {
  GLfloat x, y;
  computeloc(gameState, index, x, y);

  const int angle = getRotationDegrees(direction);
  const int flipFlag = (clock == Clock::Clockwise) ? 1 : 0;
  const int spriteFrames = gameState.gameContext.sprites.tiles[tileset].size();
  const int spriteIndex = getSpriteIndex(spriteFrames, anim);

  painttex(gameState, x, y, spriteIndex, tileset, angle, flipFlag);
}
