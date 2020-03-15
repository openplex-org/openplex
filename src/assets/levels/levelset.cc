#include <cstring>
#include "levelset.h"

//#include "../common/verbosity.h"
#include "common/sha1.h"
#include "common/fileio.h"
#include "common/utils.h"
//#include "message.h"

uint8_t *lsetdat = NULL;
int lsetallocd;
std::vector<int> lsetindex;
std::vector<std::string> lsetnames;
std::vector<std::string> lsethashes;

int getnumlevels() {
    return lsetindex.size();
}

void load_levelset_idx(std::string filename) {
    const char *idxdat;
    int idxsize;
    int idxfile;
    int cnt;
    uint8_t *datdat;
    int datsize;

    idxfile = mapFile(filename, idxdat, idxsize);
    {

    }
    unmapFile(idxfile);
}

void load_levelset_dat(std::string filename) {
    const char *dat;
    int datasize;
    int datafile;
    int i;
    datafile = mapFile(filename, dat, datasize);
    if (lsetallocd < datasize) {
        dorealloc(lsetdat, datasize);
        lsetallocd = datasize;
    }
    std::memcpy(lsetdat, dat, datasize);
    lsetindex.resize(0);
    lsethashes.resize(0);
    lsetnames.resize(0);
    for (i = 0; i < datasize; i += 1536) {
        char a[32];
        lsetindex.push_back(i);
        std::memcpy(a, lsetdat + i + 0x5a6, 23);
        a[23] = 0;
        lsetnames.push_back(std::string(a));
        std::string hash = compute_sha(lsetdat + i, 1536);
        lsethashes.push_back(hash);
        printf("Level loaded from DAT: %s\n", a);
    }
    unmapFile(datafile);
}

void load_levelset(std::string filename) {
    load_levelset_dat(filename);
    //levfile=mapFile(s,levdat,levdsize);
    //if (!levfile) return  0;
    //unmapFile(levfile);

}

const uint8_t *getleveldata(int levelnum) {
    if (!lsetdat) return NULL;
    if (levelnum >= lsetindex.size()) return lsetdat;
    return lsetdat + lsetindex[levelnum];
}

std::string getlevelname(int levelnum) {
    if (levelnum >= lsetnames.size()) return "";
    return lsetnames[levelnum];
}

std::string getlevelhash(int levelnum) {
    if (levelnum >= lsetnames.size()) return "";
    return lsethashes[levelnum];
}



