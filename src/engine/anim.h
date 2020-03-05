#ifndef __HDR_play_h
#define __HDR_play_h

/**
 * returns the progress of an object through animation
 * @param counter    - the object counter
 * @param maxcounter - the maximum value of the counter
 * @param animstart - value at the start of the animation
 * @param animstop  - the value at the end of animation, for example if animstart is 0 and animstop is 100 then the result in in percent
 */
int animprogress(int counter, int maxcounter, int animstart, int animstop=0);


#endif
