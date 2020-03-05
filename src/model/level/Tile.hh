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

#include <engine/gamedata.h>

/**
 * one map tile
 * typ - indicates the tile type
 * counter - indicates the progress of the current tile animation
 * xplode - indicates the time until an explosion will take place in that tile
 */

struct Tile {
    /*
    int typ;     // aka extd
    int counter; // aka basic, cdown
    int xplode;
    int oldtyp;

    inline int basetyp() { return typ & 0xff; } // base type
    inline int xtyp() { return typ & 0xf0; } // base type
    inline int movtyp() { return typ & 0x0c; }

    inline int movfull() { return typ & 0x0f; }

    inline int movdirection() { return typ & 0x03; }

    inline int isfree() { return typ == 0; }

    inline int isfreeormurph() { return typ == 0 || xtyp() == TX_MURPH; }

    inline int isic() { return (typ & TF_IC) != 0; }

    inline int ispcb() { return basetyp() == TB_BASE; }

    inline int isenemy() { return xtyp() == TX_KNIK || xtyp() == TX_ELECTRON; }

    inline int isportup() {
        int tb = basetyp();
        return tb == TB_PORTUP || tb == TB_PORTUPDN || tb == TB_PORTALL;
    }

    inline int isportdown() {
        int tb = basetyp();
        return tb == TB_PORTDOWN || tb == TB_PORTUPDN || tb == TB_PORTALL;
    }

    inline int isportleft() {
        int tb = basetyp();
        return tb == TB_PORTLEFT || tb == TB_PORTLR || tb == TB_PORTALL;
    }

    inline int isportright() {
        int tb = basetyp();
        return tb == TB_PORTRIGHT || tb == TB_PORTLR || tb == TB_PORTALL;
    }

    int isdeadly()
    {
        int tx=xtyp();
        int th=movfull();
        return (tx==TX_MOVEOUT && movdirection()!=TH_LEFT && movdirection()!=TH_RIGHT)
               || (tx==TB_INFOTRON && th!=0)
               //		|| (tx==TX_ZONK && th!=0)
               || tx==TX_KNIK
               || tx==TX_ELECTRON;

    }
*/

    /*
#define ISFREEFORZONK(coord) (ISFREE(coord) || ((base==0x10) && (level.ldt[coord].base==0x0200)))
#define ISLATRSVD(coord) (level.ldt[coord].b.extd==0xfd)
#define ISREDDISK(coord) (level.ldt[coord].b.extd==0xe2)
#define ISDETONATOR(coord) (level.ldt[coord].b.extd==0xe5)
#define ISEXIT(coord) (level.ldt[coord].b.extd==0xe4)
#define ISTKTRON(coord) (level.ldt[coord].b.extd==0x2f || level.ldt[coord].b.extd==0x2e)
#define ISFREEORMURPH(coord) (ISFREE(coord) || ISMURPHVULNERABLE(coord))
#define ISMURPHVULNERABLE(coord) (level.ldt[coord].b.extd>=0x80 && level.ldt[coord].b.extd<0xa0)
*/
/*
    void set(int vtyp = 0, int vcounter = 0, int vexplode = 0) {
        typ = vtyp;
        counter = vcounter;
        xplode = vexplode;
    }
    */

};

