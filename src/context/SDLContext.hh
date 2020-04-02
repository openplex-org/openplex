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


//#include <assets/fonts/font.h>
#include <engine/game/GameState.hh>
#include <control/keyboard.h>
#include <SDL.h>
#include <cassert>
#include "GameContext.hh"
#include "GLContext.hh"

struct SDLContext {
    Display &display;
    GLContext glContext;

    SDL_Rect **videomodesdl;
    const SDL_VideoInfo *origmode;
    GLint maxTexSize;
    SDL_Surface *scrsurface;
    int fullscreenmode = 1;

    std::vector<tConfigurable *> videomodes;
    tVideoMode *fsvideomode;
    tVideoMode origres;


    SDLContext(Configuration &configuration)
            : display(configuration.display) {
        assert(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)); //, "Unable to initialize SDL: %s\n");
        findvideomodes();
//        init_fonts();
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        SDL_WM_SetCaption("OpenPlex - open source Supaplex", "SDL");
        scrsurface = SDL_SetVideoMode(
                display.scr_width, display.scr_height,
                0, SDL_OPENGL | SDL_RESIZABLE); // | SDL_FULLSCREEN);
//                   (video_dofullscreen ? SDL_FULLSCREEN : 0));
        //       fullscreenmode = video_dofullscreen;
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glContext = GLContext(configuration.display);
//        default_font.open(configuration.datadir + "/default.ttf");
    }

    ~SDLContext() {
        //     done_joysticks();
        SDL_Quit();
    }

    SDL_Event event;

    void events(op::GameContext &gameContext) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                gameContext.gameover = 1;
            else if (event.type == SDL_VIDEORESIZE) {
                glContext.doResize(display, event.resize.w, event.resize.h);
            } else {
                translateandhandleevent(event, gameContext);
            }

            switch (event.type) {
                case SDL_QUIT:
                    gameContext.gameover = 1;
                    break;
            }
        }
    }

    void update() {
        glContext.update();
        SDL_GL_SwapBuffers();

    }

    void findvideomodes() {
        tVideoMode tmp;
        int i;
        origmode = SDL_GetVideoInfo();
        tmp.bpp = origmode->vfmt->BitsPerPixel;
        tmp.width = origmode->current_w;
        tmp.height = origmode->current_h;
        videomodesdl = SDL_ListModes(NULL, SDL_FULLSCREEN | SDL_HWSURFACE);
        tmp.name = "Desktop";
        origres = tmp;
        fsvideomode = new tVideoMode(tmp);
        videomodes.push_back(fsvideomode);
        if (videomodesdl == (void *) -1) {
            return;
        }
        if (videomodesdl)
            for (i = 0; videomodesdl[i]; i++) {
                char a[32];
                tmp.width = videomodesdl[i]->w;
                tmp.height = videomodesdl[i]->h;
                sprintf(a, "%dx%dx%d", tmp.width, tmp.height, tmp.bpp);
                tmp.name = a;
                videomodes.push_back(new tVideoMode(tmp));
            }
    }
};