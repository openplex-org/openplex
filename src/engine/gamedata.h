#ifndef __HDR_gamedata_h
#define __HDR_gamedata_h

#include "../common/includes.h"

/**
 * Object heading constants, define the direction objects move in
 */
enum TTHEADING {
	TH_UP=0,
	TH_RIGHT=1,
	TH_DOWN=2,
	TH_LEFT=3,
	TH_MOVEIN=4,
	TH_ANTICLOCK=0x08,
	TH_CLOCKWISE=0x0c
};

/**
 * Additional heading constants due to value overlap
 */
enum TTHEADINGM {
	TH_NORMAL=0x00,      // object is in a normal state, not going anywhere
	TH_VANISHING=0x01,   // adjacent objects eaten by murphy without moving
	TH_PREPAREFALL=0x02, // zonks and infotrons have a special state, prepare to fall
	TH_MOVEDOUBLE=0x08   // murphy can move two squares through a port
};

/**
 * vanishing object types
 */
enum TTVANISHING {
	TV_REDDISK=0x05,
	TV_EXPLODE=0x06,
	TV_EXPLODEINFO=0x07
};

/**
 * Tile type constants, defined as enum for simplicity
 */
enum TTFLAGS {
	// TB = tile base - this is the same id the tile has in the level file
	TB_ZONK        =    0x01,
	TB_BASE        =    0x02,
	TB_MURPHY      =    0x03,
	TB_INFOTRON    =    0x04,
	TB_CONCRETE    =    0x06,
	TB_EXIT        =    0x07,
	TB_ORANGE      =    0x08,
	TB_PORTRIGHT   =    0x09,
	TB_PORTDOWN    =    0x0a,
	TB_PORTLEFT    =    0x0b,
	TB_PORTUP      =    0x0c,
	TB_KNIK        =    0x11,
	TB_YELLOW      =    0x12,
	TB_CONSOLE     =    0x13,
	TB_RED         =    0x14,
	TB_PORTUPDN    =    0x15,
	TB_PORTLR      =    0x16,
	TB_PORTALL     =    0x17,
	TB_ELECTRON    =    0x18,
	TB_BUG         =    0x19,
	TB_LEVTITLE    =    0x3f,
	TB_MYTILE      =    0x29, // 41
	// TX = extended IDs we assign here to tiles that move
	TX_VANISHING   =    0x70,
	TX_KNIK        =    0x80,
	TX_ELECTRON    =    0x90,
	TX_ORANGE      =    0xa0,
	TX_YELLOW      =    0xb0,
	TX_ZONK        =    0xc0,
	TX_INFOTRON    =    0xd0,
	TX_MURPH       =    0xe0,
	TX_MOVEOUT     =    0xf0,
	// TF = tile flags, put tiles in categories to facilitate decisions
	// TD = flag combinations, to avoid checking for flags with plain &
	TF_BUG         =  0x0100,
	TF_IC          =  0x0200,
	TF_SOLID       =  0x0400,
	TF_PORT        =  0x0800,
	TF_SPECIAL     =  0x1000,
	TD_PORTSPECIAL =  0x1800
};


#endif
