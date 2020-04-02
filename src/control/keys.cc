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
#include <context/GameContext.hh>
#include <common/SystemClock.hh>
#include <SDL_events.h>
#include "Input.hh"


bool debounce() {
    static int millis = SystemClock::millis() - 1000;
    int now = SystemClock::millis() - 1000;
    if (now - millis > 100) {
        millis = now;
        return false;
    }
    return true;
}
/*
void print(GameState &gameState) {
    std::cout << "KEYS: " <<
              toString(gameState.scheduleMove) << "\t" <<
              (gameState.continueMove ? "ContinueMove\t" : "             \t")
              << toString(gameState.scheduleSnap) << "\t" <<
              (gameState.continueSnap ? "ContinueSnap\t" : "             \t") << std::endl;

}
*/

void directionPressed(Input& input, Direction directon) {
    if (opposite(input.direction) != directon) {
        input.fallback = input.direction;
    } else {
        input.fallback = Direction::None;
    }
    input.direction = directon;
    input.pressedFrames[input.direction] = 0;
}

void directionReleased(Input &input, Direction direction) {
    if (direction == input.direction) {
        input.direction = input.fallback;
        input.fallback = Direction::None;
        input.pressedFrames[input.direction] = 0;
    } else if (direction == input.fallback) {
        input.fallback = Direction::None;
    }
}

void spacePressed(Input & input) {
    input.snap = true;
}

void spaceReleased(Input & input) {
    input.snap = false;
}

void handleKeys(SDL_Event &event, op::GameContext &gameContext) {
    auto &gameState = gameContext.gameState;
    auto &input = gameContext.input;
/*
    static const auto key_to_dir = std::unordered_map<SDLKey, Direction>{
            {SDLK_UP,    Direction::Up},
            {SDLK_RIGHT, Direction::Right},
            {SDLK_DOWN,  Direction::Down},
            {SDLK_LEFT,  Direction::Left}
    };

    const Uint8 *keystates = SDL_GetKeyState(nullptr);

    for (auto sdlk_dir : {SDLK_UP, SDLK_RIGHT, SDLK_DOWN, SDLK_LEFT}) {
        auto dir = key_to_dir.at(sdlk_dir);
        if (keystates[sdlk_dir]) {
            if (gameState.pressedFrames[dir] == 0) {
                directionPressed(gameState, dir);
            }
            gameState.pressedFrames[dir]++;
        } else {
            if (gameState.pressedFrames[dir] != 0) {
                directionReleased(gameState, dir);
            }
            gameState.pressedFrames[dir] = 0;
        }
    }

    if (keystates[SDLK_SPACE]) {
        if (!gameState.isSpacePressed) {
            spacePressed(gameState);
        }
        //gameState.isSpacePressed = true;
    } else {
        if (gameState.isSpacePressed) {
            spaceReleased(gameState);
        }
        //gameState.isSpacePressed = false;
    }

*/
   if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                return directionPressed(input, Direction::Up);
            case SDLK_RIGHT:
                return directionPressed(input, Direction::Right);
            case SDLK_DOWN:
                return directionPressed(input, Direction::Down);
            case SDLK_LEFT:
                return directionPressed(input, Direction::Left);
            case SDLK_SPACE:
                return spacePressed(input);
            default:
                return;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                return directionReleased(input, Direction::Up);
            case SDLK_RIGHT:
                return directionReleased(input, Direction::Right);
            case SDLK_DOWN:
                return directionReleased(input, Direction::Down);
            case SDLK_LEFT:
                return directionReleased(input, Direction::Left);
            case SDLK_SPACE:
                return spaceReleased(input);
            case SDLK_ESCAPE:
                break;
            case SDLK_RETURN:
                break;
            case SDLK_PAGEUP:
                if (debounce()) break;
                gameContext.levelIndex--;
                if (gameContext.levelIndex < 0) {
                    gameContext.levelIndex += 111;
                }
                gameContext.levels.load(gameContext, gameContext.levelIndex);
                break;
            case SDLK_PAGEDOWN:
                if (debounce()) break;
                gameContext.levelIndex++;
                if (gameContext.levelIndex >= 111) {
                    gameContext.levelIndex -= 111;
                }
                gameContext.levels.load(gameContext, gameContext.levelIndex);
                break;
            default:
                return;
        }
    }
}



void scenehandleevent(SDL_Event &event, op::GameContext &gameContext) {
    auto &gameState = gameContext.gameState;
    auto &input = gameContext.input;
    handleKeys(event, gameContext);
    if (input.snap) {
        input.dropFrames++;
    } else {
        input.dropFrames = 0;
    }
    if (input.direction != Direction::None) {
        input.pressedFrames[input.direction]++;
    }
}
