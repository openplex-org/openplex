#ifndef __HDR_globals_h
#define __HDR_globals_h


#include "includes.h"


struct tConfigurable
{
	int idx;
	string name;
};

struct tVideoMode:public tConfigurable
{
	int height,width,bpp;
};


#endif
