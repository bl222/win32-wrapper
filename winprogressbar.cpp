#include "winprogressbar.h"

//-------------------------------------------------------------------------
// Obtains the maximum and minimum range of the progress bar.
//
// Parameters:
//
// int & min -> Will contain the minimum range.
// int & max -> Will contain the maximum range
//-------------------------------------------------------------------------

void Win::ProgressBarHandle::GetRange (int & min, int & max)
{
	PBRANGE range ;

	SendMessage (PBM_GETRANGE, 0, reinterpret_cast <LPARAM>(&range)) ;

	min = range.iLow ;
	max = range.iHigh ;
}