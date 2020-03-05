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

#include <common/configuration.h>
#include <assets/sprites/sprites.h>
#include <assets/sprites/readpng.h>
#include <unordered_map>


enum class Tileset {
    BaseVanish,
    Bug,
    Digits,
    Electron,
    Explode,
    FloppyVanish,
    InfotronExplode,
    InfotronRoll,
    InfotronVanish,
    MurphyFaces,
    MurphyVanish,
    MurphyWalk,
    MurphyYawn,
    SniksnakCut,
    SniksnakTurn,
    Static,
    Terminal,
    ZonkRoll
};

enum class StaticTile {
    Void,
    Zonk,
    Base,
    Murphy,
    Infotron,
    RAMChip,
    Wall,
    Exit,
    FloppyOrange,
    PortRight,
    PortDown,
    PortLeft,
    PortUp,
    GravityPortRight,
    GravityPortDown,
    GravityPortLeft,
    GravityPortUp,
    SnikSnak,
    FloppyYellow,
    Terminal,
    FloppyRed,
    PortVertical,
    PortHorizontal,
    PortAll,
    Electron,
    Bug,
    RAMChipLeft,
    RAMChipRight,
    Hardware1,
    Hardware2,
    Hardware3,
    Hardware4,
    Hardware5,
    Hardware6,
    Hardware7,
    Hardware8,
    Hardware9,
    Hardware10,
    RAMChipTop,
    RAMChipBottom
};

struct Sprites {
    unordered_map<Tileset, vector<GLuint>> tiles;
    string sprites_dir;

    Sprites(Configuration &configuration) : sprites_dir(configuration.datadir + "/graphics/") {
        init_sprites();
    }

    string sprites_name(Tileset tileset) {
        switch (tileset) {
            case Tileset::Static:
                return "static";
            case Tileset::MurphyFaces:
                return "murphy-faces";
            case Tileset::MurphyWalk:
                return "murphy-walk";
            case Tileset::MurphyVanish:
                return "murphy-vanish";
            case Tileset::MurphyYawn:
                return "murphy-yawn";
            case Tileset::InfotronRoll:
                return "infotron-roll";
            case Tileset::ZonkRoll:
                return "zonk-roll";
            case Tileset::SniksnakCut:
                return "sniksnak-cut";
            case Tileset::SniksnakTurn:
                return "sniksnak-turn";
            case Tileset::Explode:
                return "explode";
            case Tileset::InfotronExplode:
                return "infotron-explode";
            case Tileset::Electron:
                return "electron";
            case Tileset::FloppyVanish:
                return "floppy-vanish";
            case Tileset::InfotronVanish:
                return "infotron-vanish";
            case Tileset::BaseVanish:
                return "base-vanish";
            case Tileset::Terminal:
                return "terminal";
            case Tileset::Bug:
                return "bug";
            case Tileset::Digits:
                return "digits";
            default:
                return "static";
        };

    }

    string sprites_file(Tileset tileset) {
        return sprites_dir + sprites_name(tileset) + ".png";
    }

    void load_tileset(Tileset tileset) {
        loadImageSet(sprites_file(tileset), tiles[tileset], 0);
    }

    void init_sprites() {
        load_tileset(Tileset::Static);
        load_tileset(Tileset::BaseVanish);
        load_tileset(Tileset::Bug);
        load_tileset(Tileset::Digits);
        load_tileset(Tileset::Electron);
        load_tileset(Tileset::Explode);
        load_tileset(Tileset::FloppyVanish);
        load_tileset(Tileset::InfotronExplode);
        load_tileset(Tileset::InfotronRoll);
        load_tileset(Tileset::InfotronVanish);
        load_tileset(Tileset::MurphyFaces);
        load_tileset(Tileset::MurphyVanish);
        load_tileset(Tileset::MurphyWalk);
        load_tileset(Tileset::MurphyYawn);
        load_tileset(Tileset::SniksnakCut);
        load_tileset(Tileset::SniksnakTurn);
        load_tileset(Tileset::Static);
        load_tileset(Tileset::Terminal);
        load_tileset(Tileset::ZonkRoll);
    }
};