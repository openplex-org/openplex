#ifndef __HDR_keyboard_h
#define __HDR_keyboard_h

#include <context/GameContext.hh>
#include <SDL_events.h>

std::string keyname(int id);

void translateandhandleevent(SDL_Event &event, GameContext &gameContext);

/**
 * Allow navigating the menus using the selected controller
 * translate the event into Arrow keys and RETURN
 */
void menukey(SDL_Event &event, int flags = 0);


#endif
