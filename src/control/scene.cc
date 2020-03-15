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


bool debounce() {
    static int millis = SystemClock::millis() - 1000;
    int now = SystemClock::millis() - 1000;
    if (now - millis > 100) {
        millis = now;
        return false;
    }
    return true;
}

void directionPressed(GameState &gameState, Direction directon) {
    if (gameState.isSpacePressed) {
        gameState.scheduleSwallow = directon;
        gameState.continueSwallow = true;
        gameState.pressedFrames = 0;
    } else {
        gameState.scheduleMove = directon;
        gameState.continueMove = true;
    }
}

void directionReleased(GameState &gameState, Direction direction) {
    if (direction == gameState.scheduleMove) {
        gameState.continueMove = false;
        gameState.pressedFrames = 0;
    }
    if (direction == gameState.scheduleSwallow) {
        gameState.continueSwallow = false;
    }
}

void spacePressed(GameState &gameState) {
    gameState.scheduleSwallow = gameState.scheduleMove;
    gameState.scheduleMove = Direction::None;
    gameState.continueMove = false;
    gameState.isSpacePressed = true;
}

void spaceReleased(GameState &gameState) {
    gameState.scheduleSwallow = Direction::None;
    gameState.continueSwallow = false;
    gameState.isSpacePressed = false;
}

void scenehandleevent(SDL_Event &event, GameContext &gameContext) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                return directionPressed(gameContext.gameState, Direction::Up);
            case SDLK_RIGHT:
                return directionPressed(gameContext.gameState, Direction::Right);
            case SDLK_DOWN:
                return directionPressed(gameContext.gameState, Direction::Down);
            case SDLK_LEFT:
                return directionPressed(gameContext.gameState, Direction::Left);
            case SDLK_SPACE:
                return spacePressed(gameContext.gameState);
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                return directionReleased(gameContext.gameState, Direction::Up);
            case SDLK_RIGHT:
                return directionReleased(gameContext.gameState, Direction::Right);
            case SDLK_DOWN:
                return directionReleased(gameContext.gameState, Direction::Down);
            case SDLK_LEFT:
                return directionReleased(gameContext.gameState, Direction::Left);
            case SDLK_SPACE:
                return spaceReleased(gameContext.gameState);
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
        }
    }
}



