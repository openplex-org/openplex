#ifndef __HDR_sprites_h
#define __HDR_sprites_h

struct GameContext;
enum class Tileset;

int gettex(GameContext& gameContext, Tileset tileset, int tileindex);
int spritecount(GameContext& gameContext, Tileset tileset);
int getelectronid(GameContext& gameContext, int time);




#endif
