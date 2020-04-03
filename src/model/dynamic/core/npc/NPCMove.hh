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

#include "model/dynamic/NPC.hh"

#include <model/static/solid/core/Void.hh>

namespace op::core {

template <typename NPCType>
struct NPCMove : public NPC {
  enum class Behavior { None, Turn, Move };

  enum class Strategy { StickLeft, MoveForwardThenLeft, MoveForwardThenRight, StickRight };

  Behavior behavior = Behavior::Move;
  Strategy strategy = Strategy::StickLeft;

  Index index;
  Direction direction = Direction::None;

  // turn
  Direction previousDirection = Direction::None;
  const int TURN_FRAMES = 15;
  int turnCountdown = TURN_FRAMES;
  Clock turningDirection;

  // move
  Index previousIndex;
  const int MOVE_FRAMES = 15;
  int moveCountdown = MOVE_FRAMES;

  constexpr Clock getClock(Strategy strategy) {
    switch (strategy) {
      case Strategy::StickLeft:
        return Clock::CounterClockwise;
      case Strategy::StickRight:
        return Clock::Clockwise;
      case Strategy::MoveForwardThenLeft:
        return Clock::CounterClockwise;
      case Strategy::MoveForwardThenRight:
        return Clock::Clockwise;
      default:
        return Clock::CounterClockwise;
    }
  }

  constexpr Index getStickSideIndex(Index index, Direction direction, Strategy strategy) {
    auto clock = getClock(strategy);
    auto sideDirection = rotate(direction, clock);
    return gameState.level.follow(index, sideDirection);
  }

  bool canTurnFollowingStrategy() {
    return NPCType::canEnter(*gameState.level.storage[getStickSideIndex(index, direction, strategy)]);
  }

  bool canMoveForward() {
    return NPCType::canEnter(*gameState.level.storage[gameState.level.follow(index, direction)]);
  }

  void scheduleTurn(const Clock &clock) {
    previousDirection = direction;
    direction = rotate(direction, clock);
    turningDirection = clock;
    turnCountdown = TURN_FRAMES;
    behavior = Behavior::Turn;
  }

  void scheduleMove() {
    previousIndex = index;
    index = gameState.level.follow(index, direction);
    gameState.level.storage[previousIndex] = std::make_unique<typename NPCType::LeavingType>(*this);
    gameState.level.storage[index] = std::make_unique<typename NPCType::EnteringType>(*this);
    moveCountdown = MOVE_FRAMES;
    behavior = Behavior::Move;
  }

  enum PreventSpinInPlace { Enabled, Disabled };
  void determineBehavior(PreventSpinInPlace preventSpinInPlace) {
    if ((strategy == Strategy::MoveForwardThenLeft) || (strategy == Strategy::MoveForwardThenRight)) {
      // TODO
    } else {
      if ((preventSpinInPlace == Enabled) && canMoveForward()) {
        scheduleMove();
      } else if (canTurnFollowingStrategy()) {
        scheduleTurn(getClock(strategy));
      } else if ((preventSpinInPlace == Disabled) && canMoveForward()) {
        scheduleMove();
      } else {
        scheduleTurn(opposite(getClock(strategy)));
      }
    }
  }

  NPCMove(GameState &gameState, Index index, Direction direction, Behavior behavior, Strategy strategy)
      : NPC(gameState), index(index), direction(direction), behavior(behavior), strategy(strategy) {
    // if (behavior == Behavior::None) {
    determineBehavior(PreventSpinInPlace::Disabled);
    // }
  }

  std::vector<Index> area() const override {
    switch (behavior) {
      case Behavior::Turn:
        return {index};
      case Behavior::Move:
        return {previousIndex, index};
      default:
        return {};
    }
  }

  void spawn() override {}

  void update() override {
    switch (behavior) {
      case Behavior::Turn:
        updateTurn();
        return;
      case Behavior::Move:
        updateMove();
        return;
      default:
        return;
    }
  }

  void updateTurn() {
    turnCountdown--;
    if (turnCountdown == 0) {
      determineBehavior(PreventSpinInPlace::Enabled);
    }
  }

  void updateMove() {
    moveCountdown--;
    if (moveCountdown == 0) {
      gameState.level.storage[previousIndex] = std::make_unique<Void>();
      gameState.level.storage[index] = std::make_unique<NPCType>();
      gameState.intents.emplace_back(previousIndex, Variant::BecomesVoid);

      determineBehavior(PreventSpinInPlace::Disabled);
    }
  }

  bool ready() override { return false; }

  void clean() override {}

  void display(Renderer &renderer) override {
    switch (behavior) {
      case Behavior::Turn:
        displayTurn(renderer);
        return;
      case Behavior::Move:
        displayMove(renderer);
        return;
      default:
        return;
    }
  }

  virtual TileSet getTurnTileSet() = 0;
  virtual TileSet getMoveTileSet() = 0;

  void displayTurn(Renderer &renderer) {
    auto progress = Progress{TURN_FRAMES - turnCountdown, TURN_FRAMES};
    renderer.paintRotatedTile(gameState, getTurnTileSet(), previousDirection, turningDirection, index, progress,
                              Renderer::AllowVerticalFlip::True);
  }

  void displayMove(Renderer &renderer) {
    auto progress = Progress{MOVE_FRAMES - moveCountdown, MOVE_FRAMES};
    renderer.paintMovingTile(gameState, getMoveTileSet(), previousIndex, index, progress);
  }
};

}  // namespace op::core