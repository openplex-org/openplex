#ifndef __HDR_readpng_h
#define __HDR_readpng_h


#include <common/openplex-gl.h>
#include <string>
#include <vector>

void loadImageSet(const std::string &filename, std::vector<GLuint> &texture, int flags);


#endif
