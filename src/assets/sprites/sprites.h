#ifndef __HDR_sprites_h
#define __HDR_sprites_h

struct GameContext;
enum class TileSet;

int gettex(GameContext& gameContext, TileSet tileset, int tileindex);
int spritecount(GameContext& gameContext, TileSet tileset);
int getelectronid(GameContext& gameContext, int time);




#endif
