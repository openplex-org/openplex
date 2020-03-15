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
#include <model/static/solid/Terminal.hh>
#include <context/GameContext.hh>
#include <functional>

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

    static const auto dest = std::unordered_map<Direction, std::function<Index(Index)>>
            {
                    {Direction::Up,    [&](Index index) { return gameState.level.above(index); }},
                    {Direction::Right, [&](Index index) { return gameState.level.rightof(index); }},
                    {Direction::Down,  [&](Index index) { return gameState.level.below(index); }},
                    {Direction::Left,  [&](Index index) { return gameState.level.leftof(index); }}
            };

    if (gameState.scheduleMove != Direction::None) {
        Index dst = dest.at(gameState.scheduleMove)(src);
        auto &tile = gameState.level.storage[dst];
        auto dynamic = tile->getDynamicOn(gameState, Intent(src, Variant::MurphyTryToEnter), dst);
        if (dynamic) {
            gameState.futureDynamics.push_back(std::move(dynamic));
        }
        if (!gameState.continueMove) {
            gameState.scheduleMove = Direction::None;
        } else {
            gameState.pressedFrames++;
        }
    } else if (gameState.scheduleSwallow != Direction::None) {
        Index dst = dest.at(gameState.scheduleSwallow)(src);
        auto &tile = gameState.level.storage[dst];
        auto dynamic = tile->getDynamicOn(gameState, Intent(src, Variant::MurphyTryToSwallow), dst);
        if (dynamic) {
            gameState.futureDynamics.push_back(std::move(dynamic));
        }
        if (!gameState.continueSwallow) {
            gameState.scheduleSwallow = Direction::None;
            gameState.continueSwallow = false;
        }
    }
};
