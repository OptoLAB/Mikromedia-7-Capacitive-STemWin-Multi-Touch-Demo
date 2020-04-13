/*
J. Bajic - 2020.
*/

#ifndef TOUCHEXEC_H
#define TOUCHEXEC_H


//Defines
#define TOUCH_MAX_TOUCH_POINTS	5 // <= driver touch points
#define TOUCH_SENSITIVITY		50 // Min. press weight


//Prototypes
void STOUCH_Exec(void);
void MTOUCH_Exec(void);
void TOUCH_SetLayerIndex(int LayerIndex);

#endif
