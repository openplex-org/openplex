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

#include "Clock.hh"

enum class Direction { None, Up, Right, Left, Down };

inline constexpr Direction opposite(const Direction& direction) {
  switch (direction) {
    case Direction::None:
      return Direction::None;
    case Direction::Up:
      return Direction::Down;
    case Direction::Right:
      return Direction::Left;
    case Direction::Down:
      return Direction::Up;
    case Direction::Left:
      return Direction::Right;
    default:
      return Direction::None;
  }
}

inline constexpr Direction rotateClockwise(const Direction& direction) {
  switch (direction) {
    case Direction::None:
      return Direction::None;
    case Direction::Up:
      return Direction::Right;
    case Direction::Right:
      return Direction::Down;
    case Direction::Down:
      return Direction::Left;
    case Direction::Left:
      return Direction::Up;
    default:
      return Direction::None;
  }
}

inline constexpr Direction rotateCounterClockwise(const Direction& direction) {
  switch (direction) {
    case Direction::None:
      return Direction::None;
    case Direction::Up:
      return Direction::Left;
    case Direction::Left:
      return Direction::Down;
    case Direction::Down:
      return Direction::Right;
    case Direction::Right:
      return Direction::Up;
    default:
      return Direction::None;
  }
}

inline constexpr Direction rotate(const Direction& direction, const Clock& clock) {
  switch (clock) {
    case Clock::Clockwise:
      return rotateClockwise(direction);
    case Clock::CounterClockwise:
      return rotateCounterClockwise(direction);
    default:
      return Direction::None;
  }
}

inline constexpr int getRotationDegrees(const Direction& direction) {
  switch (direction) {
    case Direction::None:
      return 0;
    case Direction::Left:
      return 0;
    case Direction::Up:
      return 90;
    case Direction::Right:
      return 180;
    case Direction::Down:
      return 270;
    default:
      return 0;
  }
}

inline std::string toString(const Direction& direction) {
  switch (direction) {
    case Direction::None:
      return "None";
    case Direction::Up:
      return "Up";
    case Direction::Right:
      return "Right";
    case Direction::Down:
      return "Down";
    case Direction::Left:
      return "Left";
    default:
      return "EROR";
  }
}
