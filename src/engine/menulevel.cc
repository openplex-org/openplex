#include <model/level/Level.hh>
#include "menulevel.h"

#include <assets/levels/levelset.h>
#include "../common/utils.h"
#include "gamedata.h"
#include <assets/levels/loadlevel.h>

/*
void genmenulevel()
{
	int i,j;
	int n=getnumlevels();
	gameState.init();
	level = Level(20, 3+2*n);
	int portType=(TF_PORT | TB_PORTUPDN);
	int cntnf=0;
	for (i=0; i<n; i++)
	{
		//if (levelstate(i)!=2)
		//{
		//	cntnf++;
			//if (cntnf>3) portType=TF_PORT | TB_PORTUP;
	//	}
		level.ldt[lvlwidth*(i*2+2)+1].set(portType);
		for (j=2; j<lvlwidth; j++) level.ldt[lvlwidth*(i*2+2)+j].set(TF_SOLID | TB_CONCRETE);
		level.ldt[lvlwidth*(i*2+3)+3].set(TX_INFOTRON);
		level.ldt[lvlwidth*(i*2+3)+4].set(TB_LEVTITLE);
	}
    gameState.murphloc= lvlwidth + 1;
	if (gameState.lastlevel > 0 && gameState.lastlevel <= n)
        gameState.murphloc= lvlwidth + 1 + gameState.lastlevel * 2 * lvlwidth;

	level.ldt[gameState.murphloc].set(TX_MURPH);
    gameState.mode=1;
    gameState.loadlevel=0;
}
*/


