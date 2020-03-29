/*******************************************************************
(C) 2011 by Radu Stefan
radu124@gmail.com

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*******************************************************************/

#include <model/level/Level.hh>
#include <model/static/solid/core/Terminal.hh>
#include <context/GameContext.hh>

void moveMurphy(GameState &gameState, Index src) {
    auto &level = gameState.level;

/*    if (gameState.escape) {
        // explode - restart level;
        return;
    }
*/
    if (!gameState.allowMove) {
        return;
    }

    auto &input = gameState.gameContext.input;
    if (input.direction != Direction::None) {
        if (!input.snap) {
            auto dst = gameState.level.follow(src, input.direction);
            auto &tile = gameState.level.storage[dst];
            auto dynamic = tile->getDynamicOn(gameState, Intent(src, Variant::MurphyTryToMove), dst);
            if (dynamic) {
                gameState.futureDynamics.push_back(std::move(dynamic));
            }
        }
    } else {
        auto dst = gameState.level.follow(src, input.direction);
        auto &tile = gameState.level.storage[dst];
        auto dynamic = tile->getDynamicOn(gameState, Intent(src, Variant::MurphyTryToSnap), dst);
        if (dynamic) {
            gameState.futureDynamics.push_back(std::move(dynamic));
        }
    }
};
