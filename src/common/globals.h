#ifndef __HDR_globals_h
#define __HDR_globals_h


#include <string>


struct tConfigurable {
    int idx;
    std::string name;
};

struct tVideoMode : public tConfigurable {
    int height, width, bpp;
};


#endif
