#ifndef __HDR_timing_h
#define __HDR_timing_h


struct GameTime
{
	int o1,o2,o3,o4,o5,o6,o7,o8;
	int m1,m2,m3,m4,m5,m6;
	int &enemyrotate;
	int &murphmove;
	int &zonkmove;
	int &zonkfall;
	void init(int scale);
	GameTime()
		:enemyrotate(o8)
		,murphmove(o8)
		,zonkmove(o8)
		,zonkfall(o8) { init(8); }
};

#endif
