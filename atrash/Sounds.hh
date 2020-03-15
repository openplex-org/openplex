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


#include "common/configuration.h"
#include "media/audio.h"
#include "media/audiosfx.h"

#define NAMEDSFXLOAD(datadir, a) sfx_load(datadir+"/sounds/" #a ".wav",SE_##a)


struct Sounds {
    Sounds(Configuration &configuration) {
        //init_effects(configuration.datadir);
        //    init_audio();
//    Sounds sounds(configuration);
//    song_start(datadir + "/music/orig.ogg");
//    audio_yield();

    }

    void init_effects(string &datadir) {
        NAMEDSFXLOAD(datadir, bugzap);
        NAMEDSFXLOAD(datadir, explosion);
        NAMEDSFXLOAD(datadir, hit);
        NAMEDSFXLOAD(datadir, infotron);
        NAMEDSFXLOAD(datadir, pcb);
        NAMEDSFXLOAD(datadir, push);
        NAMEDSFXLOAD(datadir, victory);
    }


};