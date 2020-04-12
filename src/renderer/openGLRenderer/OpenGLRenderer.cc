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
#include <common/SystemClock.hh>

#include "engine/game/GameState.hh"

#include "context/GameContext.hh"

namespace op {
inline constexpr float getAlphaMix(float f0, float f1, int count, int total) {
  return (f0 * static_cast<float>(count) + f1 * static_cast<float>(total - count)) / total;
}

inline constexpr float getAlphaMix(float f0, float f1, Progress progress) {
  return getAlphaMix(f0, f1, progress.count, progress.total);
}

inline constexpr int getSpriteIndex(int sprites, Progress progress) {
  return (sprites * progress.count) / progress.total;
}

namespace {
void computeloc(op::GameState &gameState, Index index, GLfloat &locx, GLfloat &locy) {
  auto &display = gameState.gameContext.display;
  auto lvlwidth = gameState.level.width;
  int loc = static_cast<int>(index);
  locx = (loc % lvlwidth) * display.ts - display.scrdx;
  locy = (loc / lvlwidth) * display.ts - display.scrdy;
}

enum class VerticalFlip { None, Flip };
void painttex(op::GameState &gameState, GLfloat x, GLfloat y, int tileindex, TileSet tileset, int angleDegrees = 0,
              VerticalFlip flip = VerticalFlip::None) {
  auto &display = gameState.gameContext.display;

  GLfloat texl = 0;
  GLfloat texr = 1.0;
  GLfloat xCentered = display.ts * 0.5f;
  GLfloat yCentered = display.ts * 0.5f;

  if (tileset == TileSet::SniksnakCut || tileset == TileSet::SniksnakTurn) {
    angleDegrees -= 90;
  }

  if (tileset == TileSet::GhostMurphyWalk) {
    angleDegrees += 180;
  }

  if (tileset == TileSet::GhostMurphyTurn) {
    //angleDegrees += 180;
/*    if (flip == VerticalFlip::Flip) {
      flip = VerticalFlip::None;
    } else {
      flip = VerticalFlip::Flip;
    }*/
  }

  auto texid = gettex(gameState.gameContext, tileset, tileindex);

  if (texid != 0) {
    glBindTexture(GL_TEXTURE_2D, texid);
  } else {
    glBindTexture(GL_TEXTURE_2D, 0);
    glColor4f(1, 0, 0, 1);
  }
  glPushMatrix();
  glTranslatef(x + xCentered, y + yCentered, 0);
  if (angleDegrees) {
    glRotatef(angleDegrees, 0, 0, 1);
  }
  if (flip == VerticalFlip::Flip) {
    std::swap(texl, texr);
  }
  glBegin(GL_TRIANGLE_STRIP);
  glTexCoord2f(texl, 0.0);
  glVertex3f(-xCentered, -yCentered, 0);
  glTexCoord2f(texr, 0.0);
  glVertex3f(xCentered, -yCentered, 0);
  glTexCoord2f(texl, 1.0);
  glVertex3f(-xCentered, yCentered, 0);
  glTexCoord2f(texr, 1.0);
  glVertex3f(xCentered, yCentered, 0);
  glTexCoord2f(texl, 0.0);
  glVertex3f(-xCentered, -yCentered, 0);
  glTexCoord2f(texr, 0.0);
  glVertex3f(xCentered, -yCentered, 0);
  glEnd();
  glPopMatrix();
  glColor4f(1, 1, 1, 1);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void painttext(op::GameState &gameState, GLfloat x, GLfloat y, int tileindex, TileSet tileset) {
  auto &display = gameState.gameContext.display;

  GLfloat texl = 0;
  GLfloat texr = 1.0;
  GLfloat xCentered = display.ts * 0.8f;
  GLfloat yCentered = display.ts * 1.4f;

  auto texid = gettex(gameState.gameContext, tileset, tileindex);

  if (texid != 0) {
    glBindTexture(GL_TEXTURE_2D, texid);
  } else {
    glBindTexture(GL_TEXTURE_2D, 0);
    glColor4f(1, 0, 0, 1);
  }
  glPushMatrix();
  glTranslatef(x + xCentered, y + yCentered, 0);

  glBegin(GL_TRIANGLE_STRIP);
  glTexCoord2f(texl, 0.0);
  glVertex3f(-xCentered, -yCentered, 0);
  glTexCoord2f(texr, 0.0);
  glVertex3f(xCentered, -yCentered, 0);
  glTexCoord2f(texl, 1.0);
  glVertex3f(-xCentered, yCentered, 0);
  glTexCoord2f(texr, 1.0);
  glVertex3f(xCentered, yCentered, 0);
  glTexCoord2f(texl, 0.0);
  glVertex3f(-xCentered, -yCentered, 0);
  glTexCoord2f(texr, 0.0);
  glVertex3f(xCentered, -yCentered, 0);
  glEnd();
  glPopMatrix();
  glColor4f(1, 1, 1, 1);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void painttex(GameState &gameState, GLfloat x, GLfloat y, StaticTile staticTile, int angleDegrees,
              VerticalFlip flip = VerticalFlip::None) {
  painttex(gameState, x, y, static_cast<int>(staticTile), TileSet::Static, angleDegrees, flip);
}

void painttex(GameState &gameState, GLfloat x, GLfloat y, StaticTile staticTile) {
  painttex(gameState, x, y, static_cast<int>(staticTile), TileSet::Static, 0, VerticalFlip::None);
}

void display_status(GameState &gameState, int infotronsneeded) {
  auto &display = gameState.gameContext.display;
  int posx = display.scr_width - display.ts;
  int x = infotronsneeded;
  int digitnr = 0;
  while (x > 0) {
    painttext(gameState, display.scr_width - display.ts * 0.7 * digitnr - display.ts, display.ts, x % 10,
              TileSet::Digits);
    x /= 10;
    digitnr++;
  }
}

void display_fps(GameState &gameState, int fps) {
  auto &display = gameState.gameContext.display;
  int x = fps;  // gameState.infotronsneeded;
  int digitnr = 0;
  while (x > 0) {
    painttext(gameState, display.scr_width - display.ts * 0.7 * digitnr - display.ts, display.ts + 100, x % 10,
              TileSet::Digits);
    x /= 10;
    digitnr++;
  }
}
}  // namespace

void OpenGLRenderer::doRenderOverlay(GameState &gameState) {
  display_status(gameState, std::max(gameState.infotronsRequirement - gameState.infotronsCollected, 0));
  display_fps(gameState, SystemClock::get_fps());
}

void OpenGLRenderer::paintTile(GameState &gameState, StaticTile tile, Index index) {
  GLfloat x, y;
  computeloc(gameState, index, x, y);
  if (tile == StaticTile::GhostMurphy) {
    painttex(gameState, x, y, 0, TileSet::GhostMurphyWalk);
    return;
  }
  if (tile == StaticTile::GhostBase) {
    painttex(gameState, x, y, 0, TileSet::GhostBaseVanish);
    return;
  }
  if (tile == StaticTile::LightweightZonk) {
    painttex(gameState, x, y, 0, TileSet::LightweightZonk);
    return;
  }
  painttex(gameState, x, y, tile);
}

void OpenGLRenderer::paintTile(GameState &gameState, TileSet tileset, Index index, Progress progress) {
  GLfloat x, y;
  computeloc(gameState, index, x, y);
  const int spriteFrames = gameState.gameContext.sprites.tiles[tileset].size();
  const int spriteIndex = getSpriteIndex(spriteFrames, progress);
  painttex(gameState, x, y, spriteIndex, tileset, 0, VerticalFlip::None);
}

void OpenGLRenderer::paintDirectedTile(GameState &gameState, TileSet tileset, Direction direction, Index index,
                                       Progress progress, AllowVerticalFlip allowVerticalFlip) {
  GLfloat x, y;
  computeloc(gameState, index, x, y);

  const int spriteFrames = gameState.gameContext.sprites.tiles[tileset].size();
  const int spriteIndex = getSpriteIndex(spriteFrames, progress);

  if (allowVerticalFlip == AllowVerticalFlip::True) {
    switch (direction) {
      case Direction::Right:
        painttex(gameState, x, y, spriteIndex, tileset, 0, VerticalFlip::None);
        break;
      case Direction::Left:
        painttex(gameState, x, y, spriteIndex, tileset, 0, VerticalFlip::Flip);
        break;
      case Direction::Up:
        painttex(gameState, x, y, spriteIndex, tileset, 90, VerticalFlip::None);
        break;
      case Direction::Down:
        painttex(gameState, x, y, spriteIndex, tileset, -90, VerticalFlip::None);
        break;
      default:
        break;
    }
  } else {
    painttex(gameState, x, y, spriteIndex, tileset, getRotationDegrees(direction), VerticalFlip::None);
  }
}

void OpenGLRenderer::paintMovingTile(GameState &gameState, TileSet tileset, Index src, Index dst, Progress progress,
                                     AllowVerticalFlip allowVerticalFlip) {
  GLfloat x, y;
  GLfloat src_x, src_y;
  GLfloat dst_x, dst_y;
  computeloc(gameState, src, src_x, src_y);
  computeloc(gameState, dst, dst_x, dst_y);
  x = getAlphaMix(dst_x, src_x, progress);
  y = getAlphaMix(dst_y, src_y, progress);

  const Direction direction = gameState.level.getDirection(src, dst);

  const int spriteFrames = gameState.gameContext.sprites.tiles[tileset].size();
  const int spriteIndex = getSpriteIndex(spriteFrames, progress);

  if (allowVerticalFlip == AllowVerticalFlip::True) {
    switch (direction) {
      case Direction::Right:
        painttex(gameState, x, y, spriteIndex, tileset, 0, VerticalFlip::None);
        break;
      case Direction::Left:
        painttex(gameState, x, y, spriteIndex, tileset, 0, VerticalFlip::Flip);
        break;
      case Direction::Up:
        painttex(gameState, x, y, spriteIndex, tileset, 90, VerticalFlip::Flip);
        break;
      case Direction::Down:
        painttex(gameState, x, y, spriteIndex, tileset, -90, VerticalFlip::Flip);
        break;
      default:
        break;
    }
  } else {
    painttex(gameState, x, y, spriteIndex, tileset, getRotationDegrees(direction), VerticalFlip::None);
  }
}

void OpenGLRenderer::paintMovingTile(GameState &gameState, StaticTile staticTile, Index src, Index dst,
                                     Progress progress) {
  GLfloat x, y;
  GLfloat src_x, src_y;
  GLfloat dst_x, dst_y;
  computeloc(gameState, src, src_x, src_y);
  computeloc(gameState, dst, dst_x, dst_y);
  x = getAlphaMix(dst_x, src_x, progress);
  y = getAlphaMix(dst_y, src_y, progress);

  painttex(gameState, x, y, staticTile);
}

void OpenGLRenderer::paintRotatedTile(GameState &gameState, StaticTile tile, Direction direction, Clock clock,
                                      Index index, Progress progress) {
  GLfloat x, y;
  computeloc(gameState, index, x, y);

  const Direction towardsDirection = rotate(direction, clock);
  const int fromAngle = getRotationDegrees(direction);
  const int towardsAngle = getRotationDegrees(towardsDirection);
  const int angle = getAlphaMix(fromAngle, towardsAngle, progress);

  painttex(gameState, x, y, tile, angle);
}

void OpenGLRenderer::paintRotatedTile(GameState &gameState, TileSet tileset, Direction direction, Clock clock,
                                      Index index, Progress progress, AllowVerticalFlip allowVerticalFlip) {
  GLfloat x, y;
  computeloc(gameState, index, x, y);

  const int angle = getRotationDegrees(direction);
  const VerticalFlip flip = ((allowVerticalFlip == AllowVerticalFlip::True) && (clock != Clock::Clockwise))
                                ? VerticalFlip::Flip
                                : VerticalFlip::None;
  const int spriteFrames = gameState.gameContext.sprites.tiles[tileset].size();
  const int spriteIndex = getSpriteIndex(spriteFrames, progress);

  painttex(gameState, x, y, spriteIndex, tileset, angle, flip);
}
}  // namespace op