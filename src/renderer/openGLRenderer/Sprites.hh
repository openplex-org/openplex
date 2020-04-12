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
#include <renderer/openGLRenderer/sprites/readpng.h>
#include <renderer/openGLRenderer/sprites/sprites.h>
#include <iostream>
#include <unordered_map>

#include "model/rendering/TileSet.hh"

namespace op {
struct Sprites {
  std::unordered_map<TileSet, std::vector<GLuint> > tiles;
  std::string sprites_dir;

  Sprites(Configuration &configuration) : sprites_dir(configuration.datadir + "/graphics/") { init_sprites(); }

  std::string sprites_name(TileSet tileset) {
    switch (tileset) {
      case TileSet::Static:
        return "static";
      case TileSet::MurphyFaces:
        return "murphy-faces";
      case TileSet::MurphyWalk:
        return "murphy-walk";
      case TileSet::MurphyVanish:
        return "murphy-vanish";
      case TileSet::MurphyYawn:
        return "murphy-yawn";
      case TileSet::InfotronRoll:
        return "infotron-roll";
      case TileSet::ZonkRoll:
        return "zonk-roll";
      case TileSet::SniksnakCut:
        return "sniksnak-cut";
      case TileSet::SniksnakTurn:
        return "sniksnak-turn";
      case TileSet::Explode:
        return "explode";
      case TileSet::InfotronExplode:
        return "infotron-explode";
      case TileSet::Electron:
        return "electron";
      case TileSet::FloppyVanish:
        return "floppy-vanish";
      case TileSet::InfotronVanish:
        return "infotron-vanish";
      case TileSet::BaseVanish:
        return "base-vanish";
      case TileSet::Terminal:
        return "terminal";
      case TileSet::Bug:
        return "bug";
      case TileSet::Digits:
        return "digits";

        // ext
      case TileSet::GhostMurphyWalk:
        return "ghost-murphy-walk";
      case TileSet::GhostMurphyTurn:
        return "ghost-murphy-turn";
      case TileSet::GhostBaseVanish:
        return "ghost-base-vanish";
      case TileSet::LightweightZonk:
        return "lightweight-zonk-roll";

      default:
        return "static";
    };
  }

  std::string sprites_file(TileSet tileset) { return sprites_dir + sprites_name(tileset) + ".png"; }

  void load_tileset(TileSet tileset) { loadImageSet(sprites_file(tileset), tiles[tileset], 0); }

  void init_sprites() {
    load_tileset(TileSet::Static);
    load_tileset(TileSet::BaseVanish);
    load_tileset(TileSet::Bug);
    load_tileset(TileSet::Digits);
    load_tileset(TileSet::Electron);
    load_tileset(TileSet::Explode);
    load_tileset(TileSet::FloppyVanish);
    load_tileset(TileSet::InfotronExplode);
    load_tileset(TileSet::InfotronRoll);
    load_tileset(TileSet::InfotronVanish);
    load_tileset(TileSet::MurphyFaces);
    load_tileset(TileSet::MurphyVanish);
    load_tileset(TileSet::MurphyWalk);
    load_tileset(TileSet::MurphyYawn);
    load_tileset(TileSet::SniksnakCut);
    load_tileset(TileSet::SniksnakTurn);
    load_tileset(TileSet::Static);
    load_tileset(TileSet::Terminal);
    load_tileset(TileSet::ZonkRoll);

    load_tileset(TileSet::GhostMurphyWalk);
    load_tileset(TileSet::GhostMurphyTurn);
    load_tileset(TileSet::GhostBaseVanish);
    load_tileset(TileSet::LightweightZonk);

    /*
    auto& tileset = tiles[TileSet::SniksnakCut];
    for(auto i : tileset) { std::cout << i << " "; }
    std::cout << std::endl;
    tileset.reserve(tileset.size()*2);
    std::copy(tileset.rbegin(), tileset.rend(), std::back_inserter(tileset));
    for(auto i : tileset) { std::cout << i << " "; }
    std::cout << std::endl;
     */
  }
};
}  // namespace op