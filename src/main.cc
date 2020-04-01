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

#include <common/SystemClock.hh>
#include <assets/Sprites.hh>
#include <assets/Levels.hh>
#include <context/Player.hh>
#include <renderer/openGLRenderer/OpenGLRenderer.hh>
#include <renderer/consoleRenderer/ConsoleRenderer.hh>
#include "common/configuration.h"
#include "context/SDLContext.hh"
#include "context/GameContext.hh"

#ifdef __MACOSX__
#define main SDL_main
#endif

int main(int argc, char *argv[]) {
    Configuration configuration;
    SDLContext sdlContext(configuration);

    // Assets
    Levels levels;
    Sprites sprites(configuration);

#ifdef CONSOLE
    ConsoleRenderer renderer;
#else
    OpenGLRenderer renderer;
#endif

    Player player;
    GameContext gameContext(configuration, renderer, sprites, levels);

    while (!gameContext.gameover) {
        sdlContext.events(gameContext);
        gameContext.playFrame();
        renderer.renderFrame(gameContext.gameState);
        sdlContext.update();
        SystemClock::keep_fps();
    }

    return 0;
}




