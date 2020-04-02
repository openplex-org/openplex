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

#include "ConsoleRenderer.hh"

#include "model/render/StaticTile.hh"

namespace op {
namespace {
char getChar(StaticTile staticTile) {
  switch (staticTile) {
    case StaticTile::Void:
      return ' ';
    case StaticTile::Zonk:
      return 'o';
    case StaticTile::Base:
      return '.';
    case StaticTile::Murphy:
      return '@';
    case StaticTile::Infotron:
      return '&';
    case StaticTile::RAMChip:
      return '#';
    case StaticTile::Wall:
      return 'X';
    case StaticTile::Exit:
      return 'E';
    case StaticTile::FloppyOrange:
      return '!';
    case StaticTile::PortRight:
      return '>';
    case StaticTile::PortDown:
      return 'v';
    case StaticTile::PortLeft:
      return '<';
    case StaticTile::PortUp:
      return '^';
    case StaticTile::GravityPortRight:
      return '>';
    case StaticTile::GravityPortDown:
      return 'v';
    case StaticTile::GravityPortLeft:
      return '<';
    case StaticTile::GravityPortUp:
      return '^';
    case StaticTile::SnikSnak:
      return 'Y';
    case StaticTile::FloppyYellow:
      return '%';
    case StaticTile::Terminal:
      return 'T';
    case StaticTile::FloppyRed:
      return '~';
    case StaticTile::PortVertical:
      return '-';
    case StaticTile::PortHorizontal:
      return '|';
    case StaticTile::PortCross:
      return '+';
    case StaticTile::Electron:
      return '*';
    case StaticTile::Bug:
      return ',';
    case StaticTile::RAMChipLeft:
      return '#';
    case StaticTile::RAMChipRight:
      return '#';
    case StaticTile::Hardware1:
      return 'X';
    case StaticTile::Hardware2:
      return 'X';
    case StaticTile::Hardware3:
      return 'X';
    case StaticTile::Hardware4:
      return 'X';
    case StaticTile::Hardware5:
      return 'X';
    case StaticTile::Hardware6:
      return 'X';
    case StaticTile::Hardware7:
      return 'X';
    case StaticTile::Hardware8:
      return 'X';
    case StaticTile::Hardware9:
      return 'X';
    case StaticTile::Hardware10:
      return 'X';
    case StaticTile::RAMChipTop:
      return '#';
    case StaticTile::RAMChipBottom:
      return '#';
    default:
      return '?';
  }
}

char getChar(TileSet tileSet) {
  switch (tileSet) {
    case TileSet::BaseVanish:
      return ' ';
    case TileSet::Bug:
      return ',';
    case TileSet::Electron:
      return '*';
    case TileSet::Explode:
      return 'z';
    case TileSet::FloppyVanish:
      return ' ';
    case TileSet::InfotronExplode:
      return 'z';
    case TileSet::InfotronRoll:
      return '&';
    case TileSet::InfotronVanish:
      return ' ';
    case TileSet::MurphyFaces:
      return '@';
    case TileSet::MurphyVanish:
      return ' ';
    case TileSet::MurphyWalk:
      return '@';
    case TileSet::MurphyYawn:
      return '@';
    case TileSet::SniksnakCut:
      return 'Y';
    case TileSet::SniksnakTurn:
      return 'y';
    case TileSet::Static:
      return ' ';
    case TileSet::Terminal:
      return 'T';
    case TileSet::ZonkRoll:
      return 'o';
    default:
      return '?';
  }
}
}  // namespace
}  // namespace op

namespace op {
void ConsoleRenderer::paintTile(GameState &gameState, StaticTile tile, Index index) {
  auto x = gameState.level.getX(index);
  auto y = gameState.level.getY(index);
  canvas[y][x] = getChar(tile);
}

void ConsoleRenderer::paintTile(GameState &gameState, TileSet tileset, Index index, Progress anim) {
  auto x = gameState.level.getX(index);
  auto y = gameState.level.getY(index);
  canvas[y][x] = getChar(tileset);
}

void ConsoleRenderer::paintDirectedTile(GameState &gameState, TileSet tileset, Direction direction, Index index,
                                        Progress anim) {
  auto x = gameState.level.getX(index);
  auto y = gameState.level.getY(index);
  canvas[y][x] = getChar(tileset);
}

void ConsoleRenderer::paintMovingTile(GameState &gameState, TileSet tileset, Index src, Index dst, Progress anim) {
  auto index = (anim.count < anim.total / 2) ? src : dst;
  auto x = gameState.level.getX(index);
  auto y = gameState.level.getY(index);
  canvas[y][x] = getChar(tileset);
}

void ConsoleRenderer::paintMovingTile(GameState &gameState, StaticTile staticTile, Index src, Index dst,
                                      Progress anim) {
  auto index = (anim.count < anim.total / 2) ? src : dst;
  auto x = gameState.level.getX(index);
  auto y = gameState.level.getY(index);
  canvas[y][x] = getChar(staticTile);
}

void ConsoleRenderer::paintRotatedTile(GameState &gameState, StaticTile tile, Direction direction, Clock clock,
                                       Index index, Progress anim) {
  auto x = gameState.level.getX(index);
  auto y = gameState.level.getY(index);
  canvas[y][x] = getChar(tile);
}

void ConsoleRenderer::paintRotatedTile(GameState &gameState, TileSet tileset, Direction direction, Clock clock,
                                       Index index, Progress anim) {
  auto x = gameState.level.getX(index);
  auto y = gameState.level.getY(index);
  canvas[y][x] = getChar(tileset);
}
}  // namespace op