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

#include <common/configuration.h>
#include <engine/objMurphy.h>
#include <algorithm>
#include <assets/Levels.hh>
#include <control/Input.hh>
#include <engine/game/GameState.hh>
#include <model/dynamic/Deterministic.hh>
#include <renderer/openGLRenderer/Sprites.hh>
#include <unordered_set>
#include "renderer/Renderer.hh"

namespace op {
struct GameContext {
  int levelIndex = 34;
  Input input;
  GameState gameState;
  Display &display;
  Sprites &sprites;
  Levels &levels;
  Renderer &renderer;

  GameContext(Configuration &configuration, Renderer &renderer, Sprites &sprites, Levels &levels)
      : gameState(*this), display(configuration.display), sprites(sprites), levels(levels), renderer(renderer) {
    levels.load(*this, levelIndex);
    renderer.initialize(gameState);
  }

  void reset() {
    gameover = false;
    gameState.reset();
  }

  bool gameover = false;

  void updateDynamics() {
    std::vector<std::unique_ptr<op::Dynamic>> nextFrameDynamics;
    for (auto &dynamic : gameState.activeDynamics) {
      dynamic->update();
      if (dynamic->ready()) {
        dynamic->clean();
      } else {
        nextFrameDynamics.emplace_back(std::move(dynamic));
      }
    }
    swap(gameState.activeDynamics, nextFrameDynamics);
  }

  std::unordered_set<Index> getActiveIndices() {
    std::unordered_set<Index> result;
    for (auto &dynamic : gameState.activeDynamics) {
      auto dynamicIndices = dynamic->area();
      for (auto &index : dynamicIndices) {
        result.insert(index);
      }
    }
    return result;
  }

  void generateDynamicsFromIntents() {
    auto activeIndices = getActiveIndices();

    for (auto &intent : gameState.intents) {
      for (auto &impact : intent.propagate(gameState)) {
        auto dynamic = gameState.level.storage[impact]->getDynamicOn(gameState, intent, impact);
        if (dynamic) {
          auto indices = dynamic->area();
          if (std::all_of(indices.begin(), indices.end(),
                          [&](Index index) { return activeIndices.find(index) == activeIndices.end(); })) {
            gameState.futureDynamics.emplace_back(std::move(dynamic));
          }
        }
      }
    }

    gameState.intents.clear();
  }

  void resolveConflictingDynamics() {
    std::vector<std::unique_ptr<op::Dynamic>> keepFutureDynamics;
    std::unordered_map<Index, int> futureAreaLookup;
    for (auto &dynamic : gameState.futureDynamics) {
      auto indices = dynamic->area();
      std::unordered_set<int> conflictFutures;
      for (auto &index : indices) {
        auto fit = futureAreaLookup.find(index);
        if (fit != futureAreaLookup.end()) {
          conflictFutures.insert(fit->second);
        }
      }
      if (conflictFutures.empty()) {
        for (auto &index : indices) {
          futureAreaLookup.insert(std::make_pair(index, keepFutureDynamics.size()));
        }
        keepFutureDynamics.emplace_back(std::move(dynamic));
      }
    }
    std::swap(gameState.futureDynamics, keepFutureDynamics);
  }

  void initiateDynamics() {
    for (auto &dynamic : gameState.futureDynamics) {
      gameState.activeDynamics.emplace_back(move(dynamic));
      gameState.activeDynamics.back()->spawn();
    }
    gameState.futureDynamics.clear();
  }

  void playFrame() {
    //    gameState.timenow = SDL_GetTicks();

    gameState.frame++;
    moveMurphy(gameState, gameState.murphloc);
    updateDynamics();
    generateDynamicsFromIntents();
    resolveConflictingDynamics();
    initiateDynamics();
  }
};
}  // namespace op