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
#include <model/elements/NPC.hh>
#include <model/level/Level.hh>
#include <model/elements/Base.hh>
#include <model/elements/Bug.hh>
#include <model/elements/Electron.hh>
#include <model/elements/Exit.hh>
#include <model/elements/FloppyOrange.hh>
#include <model/elements/FloppyRed.hh>
#include <model/elements/FloppyYellow.hh>
#include <model/elements/GravityPort.hh>
#include <model/elements/Hardware.hh>
#include <model/elements/Infotron.hh>
#include <model/elements/Murphy.hh>
#include <model/elements/Port.hh>
#include <model/elements/RAMChip.hh>
#include <model/elements/SnikSnak.hh>
#include <model/elements/Terminal.hh>
#include <model/elements/Zonk.hh>
#include "loadlevel.h"
#include "engine/gamedata.h"
#include "common/utils.h"
#include "engine/timing.h"
#include <context/GameContext.hh>


unique_ptr<Element> decodeElement(unsigned char c) {
    switch (c) {
        case 0x00:
            return make_unique<Element>();
        case 0x01:
            return make_unique<Zonk>();
        case 0x02:
            return make_unique<Base>();
        case 0x03:
            return make_unique<Murphy>();
        case 0x04:
            return make_unique<Infotron>();
        case 0x05:
            return make_unique<RAMChip>(RAMChip::Style::Single);
        case 0x07:
            return make_unique<Exit>();
        case 0x08:
            return make_unique<FloppyOrange>();
        case 0x09:
            return make_unique<Port>(Port::Style::Right);
        case 0x0a:
            return make_unique<Port>(Port::Style::Down);
        case 0x0b:
            return make_unique<Port>(Port::Style::Left);
        case 0x0c:
            return make_unique<Port>(Port::Style::Up);
        case 0x0d:
            return make_unique<GravityPort>(GravityPort::Style::Right);
        case 0x0e:
            return make_unique<GravityPort>(GravityPort::Style::Down);
        case 0x0f:
            return make_unique<GravityPort>(GravityPort::Style::Left);
        case 0x10:
            return make_unique<GravityPort>(GravityPort::Style::Up);
        case 0x11:
            return make_unique<SnikSnak>();
        case 0x12:
            return make_unique<FloppyYellow>();
        case 0x13:
            return make_unique<Terminal>();
        case 0x14:
            return make_unique<FloppyRed>();
        case 0x15:
            return make_unique<Port>(Port::Style::Vertical);
        case 0x16:
            return make_unique<Port>(Port::Style::Horizontal);
        case 0x17:
            return make_unique<Port>(Port::Style::All);
        case 0x18:
            return make_unique<Electron>();
        case 0x19:
            return make_unique<Bug>();
        case 0x1a:
            return make_unique<RAMChip>(RAMChip::Style::Left);
        case 0x1b:
            return make_unique<RAMChip>(RAMChip::Style::Right);
        case 0x06:
            return make_unique<Hardware>(Hardware::Style::Wall);
        case 0x1c:
            return make_unique<Hardware>(Hardware::Style::Hardware1);
        case 0x1d:
            return make_unique<Hardware>(Hardware::Style::Hardware2);
        case 0x1e:
            return make_unique<Hardware>(Hardware::Style::Hardware3);
        case 0x1f:
            return make_unique<Hardware>(Hardware::Style::Hardware4);
        case 0x20:
            return make_unique<Hardware>(Hardware::Style::Hardware5);
        case 0x21:
            return make_unique<Hardware>(Hardware::Style::Hardware6);
        case 0x22:
            return make_unique<Hardware>(Hardware::Style::Hardware7);
        case 0x23:
            return make_unique<Hardware>(Hardware::Style::Hardware8);
        case 0x24:
            return make_unique<Hardware>(Hardware::Style::Hardware9);
        case 0x25:
            return make_unique<Hardware>(Hardware::Style::Hardware10);
        case 0x26:
            return make_unique<RAMChip>(RAMChip::Style::Top);
        case 0x27:
            return make_unique<RAMChip>(RAMChip::Style::Bottom);
        default:
            return make_unique<Element>();
    }
}

int loadLevel(GameContext &gameContext, const uint8_t *levdat) {
    GameState &gameState = gameContext.gameState;
    gameState.init();
    auto &level = gameState.level;
    auto width = level.width;
    auto height = level.height;


    for (int i = 0; i < height * width; i++) {
        level.loc(i) = decodeElement(levdat[i]);
    }

    level.repairBorder();

    for (int i = 0; i < height * width; i++) {
        level.loc(i)->init(gameState, i);
    }

    if (levdat[1470]) {
        gameState.infotronsneeded = levdat[1470];
    } else {
        gameState.infotronsneeded = gameState.infotrons;
    }

    gameState.gravity = levdat[1444] & 1;

    gameState.level.console();

    return 1;
}




