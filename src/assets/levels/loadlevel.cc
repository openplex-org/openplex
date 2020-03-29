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
#include <model/dynamic/NPC.hh>
#include <model/level/Level.hh>
#include <model/static/solid/core/Base.hh>
#include <model/static/solid/core/Bug.hh>
#include <model/static/solid/core/Electron.hh>
#include <model/static/solid/core/Exit.hh>
#include <model/static/solid/core/FloppyOrange.hh>
#include <model/static/solid/core/FloppyRed.hh>
#include <model/static/solid/core/FloppyYellow.hh>
#include <model/static/solid/core/GravityPort.hh>
#include <model/static/solid/core/Hardware.hh>
#include <model/static/solid/core/Infotron.hh>
#include <model/static/solid/core/Murphy.hh>
#include <model/static/solid/core/Port.hh>
#include <model/static/solid/core/RAMChip.hh>
#include <model/static/solid/core/SnikSnak.hh>
#include <model/static/solid/core/Terminal.hh>
#include <model/static/solid/core/Zonk.hh>
#include <context/GameContext.hh>


std::unique_ptr<op::Static> decodeTile(unsigned char c) {
    switch (c) {
        case 0x00:
            return std::make_unique<op::core::Void>();
        case 0x01:
            return std::make_unique<op::core::Zonk>();
        case 0x02:
            return std::make_unique<op::core::Base>();
        case 0x03:
            return std::make_unique<op::core::Murphy>();
        case 0x04:
            return std::make_unique<op::core::Infotron>();
        case 0x05:
            return std::make_unique<op::core::RAMChip>(op::core::RAMChip::Style::Single);
        case 0x07:
            return std::make_unique<op::core::Exit>();
        case 0x08:
            return std::make_unique<op::core::FloppyOrange>();
        case 0x09:
            return std::make_unique<op::core::Port>(op::core::Port::Style::Right);
        case 0x0a:
            return std::make_unique<op::core::Port>(op::core::Port::Style::Down);
        case 0x0b:
            return std::make_unique<op::core::Port>(op::core::Port::Style::Left);
        case 0x0c:
            return std::make_unique<op::core::Port>(op::core::Port::Style::Up);
        case 0x0d:
            return std::make_unique<op::core::GravityPort>(op::core::GravityPort::Style::Right);
        case 0x0e:
            return std::make_unique<op::core::GravityPort>(op::core::GravityPort::Style::Down);
        case 0x0f:
            return std::make_unique<op::core::GravityPort>(op::core::GravityPort::Style::Left);
        case 0x10:
            return std::make_unique<op::core::GravityPort>(op::core::GravityPort::Style::Up);
        case 0x11:
            return std::make_unique<op::core::SnikSnak>();
        case 0x12:
            return std::make_unique<op::core::FloppyYellow>();
        case 0x13:
            return std::make_unique<op::core::Terminal>();
        case 0x14:
            return std::make_unique<op::core::FloppyRed>();
        case 0x15:
            return std::make_unique<op::core::Port>(op::core::Port::Style::Vertical);
        case 0x16:
            return std::make_unique<op::core::Port>(op::core::Port::Style::Horizontal);
        case 0x17:
            return std::make_unique<op::core::Port>(op::core::Port::Style::Cross);
        case 0x18:
            return std::make_unique<op::core::Electron>();
        case 0x19:
            return std::make_unique<op::core::Bug>();
        case 0x1a:
            return std::make_unique<op::core::RAMChip>(op::core::RAMChip::Style::Left);
        case 0x1b:
            return std::make_unique<op::core::RAMChip>(op::core::RAMChip::Style::Right);
        case 0x06:
            return std::make_unique<op::core::Hardware>(op::core::Hardware::Style::Wall);
        case 0x1c:
            return std::make_unique<op::core::Hardware>(op::core::Hardware::Style::Hardware1);
        case 0x1d:
            return std::make_unique<op::core::Hardware>(op::core::Hardware::Style::Hardware2);
        case 0x1e:
            return std::make_unique<op::core::Hardware>(op::core::Hardware::Style::Hardware3);
        case 0x1f:
            return std::make_unique<op::core::Hardware>(op::core::Hardware::Style::Hardware4);
        case 0x20:
            return std::make_unique<op::core::Hardware>(op::core::Hardware::Style::Hardware5);
        case 0x21:
            return std::make_unique<op::core::Hardware>(op::core::Hardware::Style::Hardware6);
        case 0x22:
            return std::make_unique<op::core::Hardware>(op::core::Hardware::Style::Hardware7);
        case 0x23:
            return std::make_unique<op::core::Hardware>(op::core::Hardware::Style::Hardware8);
        case 0x24:
            return std::make_unique<op::core::Hardware>(op::core::Hardware::Style::Hardware9);
        case 0x25:
            return std::make_unique<op::core::Hardware>(op::core::Hardware::Style::Hardware10);
        case 0x26:
            return std::make_unique<op::core::RAMChip>(op::core::RAMChip::Style::Top);
        case 0x27:
            return std::make_unique<op::core::RAMChip>(op::core::RAMChip::Style::Bottom);
        default:
            return std::make_unique<op::core::Void>();
    }
}

int loadLevel(GameContext &gameContext, const uint8_t *levdat) {
    GameState &gameState = gameContext.gameState;
    gameState.init();
    auto &level = gameState.level;
    auto width = level.width;
    auto height = level.height;


    for (int i = 0; i < height * width; i++) {
        level.loc(i) = decodeTile(levdat[i]);
    }

    level.repairBorder();

    for (int i = 0; i < height * width; i++) {
        level.loc(i)->init(gameState, i);
    }

    if (levdat[1470]) {
        gameState.infotronsRequirement = levdat[1470];
    } else {
        gameState.infotronsRequirement = gameState.infotronsInLevel;
    }

    gameState.gravity = levdat[1444] & 1;

    gameState.level.console();

    return 1;
}




