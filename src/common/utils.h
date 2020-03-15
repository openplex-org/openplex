#ifndef __HDR_utils_h
#define __HDR_utils_h


#include <cstdlib>

// defined in configuration
int tsimatch(char *&s, const char *v);

template <typename T>
T* dorealloc(T* &adr,int len)
{
	T* res=(T*) realloc(adr,len*sizeof(T));
	if (!res) std::exit(1);
	adr=res;
	return res;
}

#endif
