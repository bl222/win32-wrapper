#include "wincommoncontrol.h"
#include <windows.h>
#include <commctrl.h>


//-----------------------------------------------------------------
//  Loads one of the common controls in memory.
//-----------------------------------------------------------------

Win::UsingCommonControl::UsingCommonControl (DWORD icc)
{
	INITCOMMONCONTROLSEX init ;

	init.dwSize = sizeof (INITCOMMONCONTROLSEX) ;
	init.dwICC  = icc ;

	if (::InitCommonControlsEx (&init) == FALSE)
		throw Win::Exception (TEXT("Could not innitialize one of the common control")) ;
}

