
/*
J. Bajic - 2020.
Based on SEGGER Touch panel configuration example
*/


#include "TouchExec.h"
#include "GUI.h"
#include "FT5XX6.h"

// POINT_DATA - Used by this module to calculate the different MT flags and events.
typedef struct {
  U16 xPos;
  U16 yPos;
  U8  Id;
  U8  Flags;
} POINT_DATA;

static int _LayerIndex;

static U8  _aActiveIds[TOUCH_MAX_TOUCH_POINTS];

/*********************************************************************
*
*       _ActiveIdFound
*
* Purpose:
*   Checks if the given Id is part of the currently active Ids
*/
static int _ActiveIdFound(U8 Id) {
  int i;
  U8 * pId;

  pId = _aActiveIds;
  i   = GUI_COUNTOF(_aActiveIds);
  do {
    if (*pId++ == Id) {
      return 1;
    }
  } while (--i);
  return 0;
}

/*********************************************************************
*
*       _StoreId
*
* Purpose:
*   Finds a free 'slot' for the given Id and puts it to the active Ids
*/
static int _StoreId(U8 Id) {
  int i;
  U8 * pId;

  pId = _aActiveIds;
  i   = GUI_COUNTOF(_aActiveIds);
  do {
    if (*pId == 0) {
      *pId = Id;
      return 0;
    }
    pId++;
  } while (--i);
  return 1;
}

/*********************************************************************
*
*       _CurrentIdFound
*
* Purpose:
*   Checks if the given Id is part of the given POINT_DATA array
*/
static int _CurrentIdFound(U8 Id, POINT_DATA * pPointData, int NumPoints) {
  POINT_DATA * pi;
  int i;

  for (pi = pPointData, i = 0; i < NumPoints; i++, pi++) {
    if (pi->Id == Id) {
      return 1;
    }
  }
  return 0;
}

/*********************************************************************
*
*       _CreateInput
*
* Purpose:
*   Fills the given GUI_MTOUCH_INPUT structure with the given coordinates
*   of the POINT_DATA data structure. In case of UP events there is no
*   data and only the given Id is used.
*/
static void _CreateInput(U16 Flags, U8 Id, POINT_DATA * pPointData, GUI_MTOUCH_INPUT * pInput) {
  if (pPointData) {
    pInput->x  = pPointData->xPos;
    pInput->y  = pPointData->yPos;
    pInput->Id = pPointData->Id;
  } else {
    pInput->Id = Id;
  }
  pInput->Flags = Flags;
}

/*********************************************************************
*
*       _CreateUpInputs
*
* Purpose:
*   Checks if the already existing active touch points exist in current
*   data. For each non existing active Id in the current data an UP event
*   is created.
*/
static void _CreateUpInputs(POINT_DATA * pPointData, int NumPoints, GUI_MTOUCH_INPUT ** ppInput, int * pNumInputs) {
  GUI_MTOUCH_INPUT * pInput;
  int i;
  U8 * pId;
  U8 Id;

  pInput = *ppInput;
  pId = _aActiveIds;
  i   = GUI_COUNTOF(_aActiveIds);
  do {
    Id = *pId;
    if (Id) {
      if (_CurrentIdFound(Id, pPointData, NumPoints) == 0) {
        _CreateInput(GUI_MTOUCH_FLAG_UP, Id, NULL, pInput);
        (*pNumInputs)++;
        pInput++;
        *pId = 0;
      }
    }
    pId++;
  } while (--i);
  *ppInput = pInput;
}

/*********************************************************************
*
*       _CreateMoveAndDownInputs
*
* Purpose:
*   Fills the given array of GUI_MTOUCH_INPUT structures with data of current
*   POINT_DATA array. If an item already exist a MOVE event is created,
*   otherwise a DOWM event.
*/
static void _CreateMoveAndDownInputs(POINT_DATA * pPointData, int NumPoints, GUI_MTOUCH_INPUT * pInput) {
  int i, Found;

  for (i = 0; i < NumPoints; i++, pPointData++, pInput++) {
    Found = _ActiveIdFound(pPointData->Id);
    pInput->x     = pPointData->xPos;
    pInput->y     = pPointData->yPos;
    pInput->Id    = pPointData->Id;
    if (Found) {
      pInput->Flags = GUI_MTOUCH_FLAG_MOVE;
    } else {
      pInput->Flags = GUI_MTOUCH_FLAG_DOWN;
      _StoreId(pPointData->Id);
    }
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************/

//=============================================================================
// MULTI Touch Execute - Gets n touch points and pass to GUI
//=============================================================================
void MTOUCH_Exec(void)
{
	GUI_MTOUCH_INPUT * pInput;
	GUI_MTOUCH_EVENT   Event;
	GUI_MTOUCH_INPUT   aInput[TOUCH_MAX_TOUCH_POINTS];
	POINT_DATA         aPointData[TOUCH_MAX_TOUCH_POINTS];
	int                NumInputs;
	int                i;
	U8                 NumPoints;
	U8 				   n_points;
	CTP_point_data	   point={0,0,0,0,0,0};

	NumPoints=0;

  	n_points=FT5XX6_GetNumOfTouches();
  	if(n_points>TOUCH_MAX_TOUCH_POINTS) n_points=TOUCH_MAX_TOUCH_POINTS;

	for (i = 0; i < n_points; i++)
	{
		point=FT5XX6_ReadPoint(i);
		if(point.pressure>TOUCH_SENSITIVITY)
		{
		  aPointData[i].Id   =i + 1; // Add 1 to ID because TC counts from 0 and emWin can't handle an ID with 0.
		  aPointData[i].xPos = point.x;
		  aPointData[i].yPos = point.y;
		  NumPoints++; 				// increase num of valid points
		}
	}
	//SEGGER example
	// Independent of NumPoints check if UP-inputs need to be generated
	pInput    = aInput;
	NumInputs = 0;
	_CreateUpInputs(aPointData, NumPoints, &pInput, &NumInputs);

	// Create MOVE- and DOWN-inputs only for current points
	if (NumPoints)
	{
		NumInputs += NumPoints;
		_CreateMoveAndDownInputs(aPointData, NumPoints, pInput);
	}

	// If any input exists, store an event into emWin buffer
	if (NumInputs)
	{
		Event.LayerIndex = _LayerIndex;
		Event.NumPoints  = NumInputs;
		GUI_MTOUCH_StoreEvent(&Event, aInput);
	}
}
//=============================================================================
// SINGLE Touch Execute - Get only first touch point and pass to GUI
//=============================================================================
void STOUCH_Exec(void) {
  static GUI_PID_STATE 	StatePID;
  static int           	IsTouched;
  CTP_point_data	   	point={0,0,0,0,0,0};

  StatePID.Layer    = _LayerIndex;          // Set layer who should handle touch
  //Report.DeviceMode = FT5XX6_GetMode();
  //Report. GestureID = FT5XX6_GetGeastureID();
  //Report.NumPoints  = FT5XX6_GetNumOfTouches();

  point=FT5XX6_ReadPoint(0);
  if (point.pressure>TOUCH_SENSITIVITY)
  {
    IsTouched        = 1;  // Remember that we have a touch, needed for generating up events
    StatePID.Pressed = 1;  // State is pressed
    StatePID.x       = point.x;
    StatePID.y       = point.y;
    GUI_TOUCH_StoreStateEx(&StatePID);
  }
  else
  {
    if (IsTouched)
    {
      IsTouched        = 0;  // now we don't.
      StatePID.Pressed = 0;  // So, state is not pressed.
      //StatePID.x       = 0;
      //StatePID.y       = 0;
      GUI_TOUCH_StoreStateEx(&StatePID);   
    }
  }
}
//=============================================================================
// Set Layer Index
//=============================================================================
void TOUCH_SetLayerIndex(int LayerIndex) {
  _LayerIndex = LayerIndex;
}
