#ifndef __HDR_display_h
#define __HDR_display_h

#include <assets/Sprites.hh>

struct GameState;

void renderscene(GameState& gameState);

/**
 * Compute exact object location on screen, including modifier
 * @param loc - tile index
 * @param locy - position on the y (vertical) axis, axis points down
 * @param locx - position on the x (horizontal) axis, axis points right
 */
void computeloc(GameState& gameState, int loc, GLfloat &locy, GLfloat &locx, int flags=0);

void painttex(GameState &gameState, GLfloat x, GLfloat y, StaticTile staticTile, int rot, int flags = 0);
void painttex(GameState &gameState, GLfloat x, GLfloat y, StaticTile staticTile);

/**
 * paint a texture at the given coordinates
 * @param x horizontal location
 * @param y vertical location
 * @param id texture id inside a group of textures
 * @param group the group of textures
 * @param rot rotation in degrees
 */
void painttex(GameState& gameState, GLfloat x, GLfloat y, int tileindex, Tileset tileset, int rot=0, int flags=0);


#endif
