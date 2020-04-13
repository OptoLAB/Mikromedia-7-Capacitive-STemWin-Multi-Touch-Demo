/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.32                          *
*        Compiled Oct  8 2015, 11:59:02                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
#include "MTouchDLG.h"
#include "MenuDLG.h"
#include <stdio.h>
// USER END



/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0       (GUI_ID_USER + 0x00)
#define ID_BUTTON_0       (GUI_ID_USER + 0x01)
#define ID_EDIT_0         (GUI_ID_USER + 0x02)
#define ID_EDIT_1         (GUI_ID_USER + 0x03)
#define ID_EDIT_2         (GUI_ID_USER + 0x04)
#define ID_EDIT_3         (GUI_ID_USER + 0x05)
#define ID_TEXT_0         (GUI_ID_USER + 0x06)
#define ID_TEXT_1         (GUI_ID_USER + 0x07)
#define ID_TEXT_2         (GUI_ID_USER + 0x08)
#define ID_TEXT_3	      (GUI_ID_USER + 0x09)
#define ID_BUTTON_1       (GUI_ID_USER + 0x0A)

// USER START (Optionally insert additional defines)
#define WIN_X_SIZE 			800
#define WIN_Y_SIZE 			480
#define MIN_ZOOM_FACTOR   	1000
#define MAX_ZOOM_FACTOR		8000
#define ZOOM_x1				2000
#define RECT_X_SIZE			100
#define RECT_Y_SIZE			100
#define START_ANGLE			0
#define BOUNDARY			30
#define AA_FACTOR			1
#define RECT_WIDTH			5
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "RST", ID_BUTTON_0, 5, 8, 40, 22, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_0, 105, 8, 45, 22, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_1, 227, 8, 45, 22, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_2, 347, 8, 45, 22, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_3, 483, 8, 60, 22, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Size:", ID_TEXT_0, 55, 8, 45, 22, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Angle:", ID_TEXT_1, 165,8, 55, 22, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Zoom:", ID_TEXT_2, 287, 8, 55, 22, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Gesture:", ID_TEXT_3, 405, 8, 75, 22, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "x", ID_BUTTON_1, 772, 8, 22, 22, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/

void redrawRect(int x, int y, int sx, int sy, float a)
{
	GUI_POINT rect[]={
		  {-sx/2,-sy/2},
		  { sx/2,-sy/2},
		  { sx/2, sy/2},
		  {-sx/2, sy/2},
	};
	GUI_POINT rot_rect[4];

	GUI_RotatePolygon(rot_rect,rect,4,a/180*3.14);

	GUI_AA_SetFactor(AA_FACTOR);
	GUI_SetColor(GUI_YELLOW);
	GUI_AA_DrawPolyOutline  (rot_rect, 4, RECT_WIDTH,  x,  y);
  	GUI_SetPenSize(RECT_WIDTH);
  	GUI_SetColor(GUI_CYAN);
	GUI_AA_DrawLine (rot_rect[1].x+x,rot_rect[1].y+y,rot_rect[3].x+x,rot_rect[3].y+y);
  	GUI_SetColor(GUI_RED);
	GUI_AA_DrawLine (rot_rect[0].x+x,rot_rect[0].y+y,rot_rect[2].x+x,rot_rect[2].y+y);

	GUI_SetPenSize(25);
	GUI_SetColor(GUI_GREEN);
	GUI_DrawPoint(rot_rect[0].x+x,rot_rect[0].y+y);
	GUI_SetColor(GUI_BLUE);
	GUI_DrawPoint(rot_rect[1].x+x,rot_rect[1].y+y);
	GUI_SetColor(GUI_MAGENTA);
	GUI_DrawPoint(rot_rect[2].x+x,rot_rect[2].y+y);
	GUI_SetColor(GUI_WHITE);
	GUI_DrawPoint(rot_rect[3].x+x,rot_rect[3].y+y);
}

static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  char data[10]="";
  static int x_pos=WIN_X_SIZE/2;
  static int y_pos=WIN_Y_SIZE/2;
  static int angle=START_ANGLE;
  static I32 zoom_factor=ZOOM_x1;
  static int size_x=RECT_X_SIZE;
  static int size_y=RECT_Y_SIZE;
  WM_GESTURE_INFO * pGestureInfo;
  static WM_ZOOM_INFO zoom_range = {MIN_ZOOM_FACTOR, MAX_ZOOM_FACTOR};
  int     i;
  int gesture=0;
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
	//
    // Initialization of 'Window'
    //
    hItem = pMsg->hWin;
    WINDOW_SetBkColor(hItem, GUI_GRAY_50);
    //
    // Initialization of 'Edit'
    //
    WIDGET_EFFECT_Simple_SetColor(0, GUI_DARKGRAY);
    for(i=0; i<4; i++)
    {
    	hItem = WM_GetDialogItem(pMsg->hWin, _aDialogCreate[i + 2].Id);
        EDIT_SetText(hItem, "none");
        EDIT_SetFont(hItem, GUI_FONT_20B_1);
        EDIT_SetTextColor(hItem,EDIT_CI_ENABELD,GUI_DARKGRAY);
        EDIT_SetBkColor(hItem, EDIT_CI_ENABELD, GUI_ORANGE);
        EDIT_SetFocussable(hItem, 0);

    }
    for(i=0; i<4; i++)
    {
    	hItem = WM_GetDialogItem(pMsg->hWin, _aDialogCreate[i + 6].Id);
        TEXT_SetFont(hItem, GUI_FONT_20B_1);
        TEXT_SetTextColor(hItem, GUI_ORANGE);
    }

    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetSkinClassic(hItem);
    BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_ORANGE);
    BUTTON_SetBkColor(hItem, BUTTON_CI_PRESSED, GUI_DARKGRAY);
    BUTTON_SetTextColor(hItem, BUTTON_CI_UNPRESSED, GUI_DARKGRAY);
    BUTTON_SetTextColor(hItem, BUTTON_CI_PRESSED, GUI_ORANGE);
    BUTTON_SetFrameColor(hItem, GUI_DARKGRAY);
    BUTTON_SetFont(hItem, GUI_FONT_20B_1);
    BUTTON_SetFocussable(hItem, 0);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetSkinClassic(hItem);
    BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_RED);
    BUTTON_SetBkColor(hItem, BUTTON_CI_PRESSED, GUI_WHITE);
    BUTTON_SetTextColor(hItem, BUTTON_CI_UNPRESSED, GUI_WHITE);
    BUTTON_SetTextColor(hItem, BUTTON_CI_PRESSED, GUI_RED);
    BUTTON_SetFrameColor(hItem, GUI_WHITE);
    BUTTON_SetFont(hItem, GUI_FONT_24B_1);
    BUTTON_SetFocussable(hItem, 0);

    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_PAINT:
	  	redrawRect(x_pos, y_pos, size_x, size_y, angle);

        sprintf((char*)data,"%03d",size_x);
        hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
        EDIT_SetText(hItem, data);

        sprintf((char*)data,"%03d",angle);
        hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_1);
        EDIT_SetText(hItem, data);

        sprintf((char*)data,"%01d.%02d",(int)(zoom_factor/ZOOM_x1),(int)((zoom_factor%ZOOM_x1)*100/ZOOM_x1));
        hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
        EDIT_SetText(hItem, data);

        GUI_SetColor(GUI_GRAY_7C);
        GUI_FillRect(0,0,800,32);
        GUI_DrawRoundedFrame(0,0,800,480,0,5);
	  	break;
  case WM_GESTURE:
	  pGestureInfo = (WM_GESTURE_INFO *)pMsg->Data.p;
	  pGestureInfo->pZoomInfo = &zoom_range;

	  	gesture=pGestureInfo->Flags;
	  	hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_3);

	  	if(gesture&WM_GF_PAN) EDIT_SetText(hItem, "pan");
	  	if(gesture&WM_GF_ZOOM) EDIT_SetText(hItem, "zoom");
	  	if(gesture&WM_GF_ROTATE) EDIT_SetText(hItem, "rotate");
	  	if(gesture&WM_GF_END) EDIT_SetText(hItem, "none");

	    switch (pGestureInfo->Flags& ~(WM_GF_BEGIN | WM_GF_END))
	    {
	    case WM_GF_ZOOM:
	    	if (pGestureInfo->Flags & WM_GF_BEGIN) //start of gesture
	    	{
	    		pGestureInfo->Factor = zoom_factor;
	    	}
	    	else if((pGestureInfo->Flags & WM_GF_END) == 0) //gesture in progress
	    	{
	    		zoom_factor=pGestureInfo->Factor;
	    		size_x=(RECT_X_SIZE*zoom_factor)/ZOOM_x1;
	    		size_y=(RECT_Y_SIZE*zoom_factor)/ZOOM_x1;
	    		WM_InvalidateWindow(pMsg->hWin);
	    	}
	    	break;
	   case WM_GF_ROTATE:
	        angle+=(pGestureInfo->Angle)>>16;
	        if(angle>360)angle-=360;
	        if(angle<0)angle+=360;
	        WM_InvalidateWindow(pMsg->hWin);
	    	break;
	    case WM_GF_PAN:
	        x_pos+=pGestureInfo->Point.x;
	        if(x_pos>(WIN_X_SIZE-BOUNDARY))
	        	x_pos=(WIN_X_SIZE-BOUNDARY);
	        else if (x_pos<BOUNDARY)
	        	x_pos=BOUNDARY;
	        y_pos+=pGestureInfo->Point.y;
	        if(y_pos>(WIN_Y_SIZE-BOUNDARY))
	        	y_pos=(WIN_Y_SIZE-BOUNDARY);
	        else if (y_pos<BOUNDARY)
	        	y_pos=BOUNDARY;
	        WM_InvalidateWindow(pMsg->hWin);
	    	break;
	    }

	  break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
    		size_x=RECT_X_SIZE;
    		size_y=RECT_Y_SIZE;
    		angle=START_ANGLE;
    		x_pos=WIN_X_SIZE/2;
    		y_pos=WIN_Y_SIZE/2;
    		zoom_factor=ZOOM_x1;
    		WM_InvalidateWindow(pMsg->hWin);
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Button'
	  switch(NCode) {
	  case WM_NOTIFICATION_CLICKED:
	  // USER START (Optionally insert code for reacting on notification message)
    	  hItem = pMsg->hWin;
		  WM_DeleteWindow(hItem);
		  menu_state=MAIN_MENU;
		  WM_ShowWindow(hMenu);
	  // USER END
	    break;
	  case WM_NOTIFICATION_RELEASED:
	  // USER START (Optionally insert code for reacting on notification message)
	  // USER END
	    break;
	// USER START (Optionally insert additional code for further notification handling)
	// USER END
	  }
	  break;
    case ID_EDIT_0: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_1: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateWindow
*/

WM_HWIN CreateMTouch(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  //hWin = WM_CreateWindow(0, 0, 800, 480, WM_CF_SHOW, _cbDialog, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
