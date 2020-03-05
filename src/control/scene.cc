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
#include "scene.h"

#include "engine/gamedata.h"

void scenehandleevent(SDL_Event &event, GameContext &gameContext) {
    int downval = 0;
    if (event.type == SDL_KEYDOWN) downval = 1;
    if (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                gameContext.gameState.keydown[0] = downval;
                break;
            case SDLK_RIGHT:
                gameContext.gameState.keydown[1] = downval;
                break;
            case SDLK_DOWN:
                gameContext.gameState.keydown[2] = downval;
                break;
            case SDLK_LEFT:
                gameContext.gameState.keydown[3] = downval;
                break;
            case SDLK_SPACE:
                gameContext.gameState.keydown[4] = downval;
                break;
            case SDLK_ESCAPE:
                gameContext.gameState.keydown[5] = downval;
                break;
            case SDLK_RETURN:
                gameContext.gameState.keydown[6] = downval;
                break;
            case SDLK_PAGEUP:
                gameContext.levelIndex--;
                if (gameContext.levelIndex < 0) {
                    gameContext.levelIndex += 111;
                }
                gameContext.levels.load(gameContext, gameContext.levelIndex);
                break;
            case SDLK_PAGEDOWN:
                gameContext.levelIndex++;
                if (gameContext.levelIndex >= 111) {
                    gameContext.levelIndex -= 111;
                }
                gameContext.levels.load(gameContext, gameContext.levelIndex);
                break;
        }
    }
}



