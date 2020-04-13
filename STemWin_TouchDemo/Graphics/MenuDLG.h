/*
 * MenuDLG.h
 *
 *  Created on: Apr 8, 2020
 *      Author: Jovan
 */

#ifndef MENUDLG_H_
#define MENUDLG_H_

#include "DIALOG.h"

#define MAIN_MENU	0
#define STOUCH_DEMO	1
#define MTOUCH_DEMO	2

U8 menu_state;
WM_HWIN hMenu;

WM_HWIN CreateMenu(void);

#endif /* MENUDLG_H_ */
