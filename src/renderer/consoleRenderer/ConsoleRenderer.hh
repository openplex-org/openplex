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

#include "renderer/Renderer.hh"

#include <engine/game/GameState.hh>
#include <model/level/Clock.hh>
#include <model/render/Progress.hh>
#include <model/render/TileSet.hh>
#include "model/render/StaticTile.hh"

#include <iostream>

namespace op {
struct ConsoleRenderer : public Renderer {
  std::vector<std::string> canvas;
  std::string overlay;

  void initialize(GameState &gameState) override {
    canvas = std::vector<std::string>(gameState.level.height, std::string(gameState.level.width, ' '));
  }

  void doBeforeFrame(GameState &gameState) override {
    std::system("clear");
    for (auto &line : canvas) {
      std::fill(line.begin(), line.end(), ' ');
    }
  }

  void doRenderOverlay(GameState &gameState) override {
    overlay = "frame: " + std::to_string(gameState.frame);
  }

  void doRenderFrame(GameState &gameState) override {
    std::cout << "\n";
    for (auto &line : canvas) {
      std::cout << line << "\n";
    }
    std::cout << overlay << "\n";
    std::cout << std::flush;
  }

  void paintTile(GameState &gameState, StaticTile tile, Index index) override;

  void paintTile(GameState &gameState, TileSet tileset, Index index, Progress anim) override;

  void paintDirectedTile(GameState &gameState, TileSet tileset, Direction direction, Index index,
                         Progress anim) override;

  void paintMovingTile(GameState &gameState, TileSet tileset, Index src, Index dst, Progress anim) override;

  void paintMovingTile(GameState &gameState, StaticTile staticTile, Index src, Index dst, Progress anim) override;

  void paintRotatedTile(GameState &gameState, StaticTile tile, Direction direction, Clock clock, Index index,
                        Progress anim) override;

  void paintRotatedTile(GameState &gameState, TileSet tileset, Direction direction, Clock clock, Index index,
                        Progress anim) override;
};
}  // namespace op