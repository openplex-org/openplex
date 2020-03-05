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

#include <context/Display.hh>
#include <common/openplex-gl.h>

struct GLContext {
    Display *display;
    bool video_glflush = true;
    bool video_glfinish = true;

    GLContext() = default;
    GLContext(Display &display) : display(&display) {
        initviewport(display);
    }

    void update() {
        if (video_glflush) glFlush();
        if (video_glfinish) glFinish();
    }

    void initviewport(Display &display) {
        glViewport(0, 0, display.scr_width, display.scr_height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0f, display.scr_width, display.scr_height, 0.0f, -1.0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glEnable(GL_POLYGON_SMOOTH);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    }

    void doResize(Display &display, int w, int h) {
        display.scr_width = w;
        display.scr_height = h;

    /*
        scrsurface = SDL_SetVideoMode(scr_width, scr_height,
                                      ((fullscreenmode == 1) && fsvideomode->bpp != origres.bpp) ? fsvideomode->bpp : 0,
                                      SDL_HWSURFACE | SDL_OPENGL | SDL_RESIZABLE |
                                      ((fullscreenmode == 1) ? SDL_FULLSCREEN : 0));
                                      */
//	if (!scrsurface->flags & SDL_HWSURFACE)
//		WARN(VIDEO,"No hardware surface resizing to %d x %d\n", scr_width, scr_height);
        initviewport(display);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//	INFO(VIDEO,"RESIZE: %d %d\n", scr_width, scr_height);
    }
};