#include "wintimer.h"

//-----------------------------------------------------------
// Constructor. Creates a Win::Timer object and optionnaly
// set it's data members.
// 
// Parameters:
//
// const Win::Base hwnd -> Owner of the timer.
// const int id        -> Id of the timer.
// TIMERPROC timeProc  -> Procedure to be called by the timer
//					     If none specified, sends WM_TIMER.
//-----------------------------------------------------------

Win::Timer::Timer (const Win::Base hwnd, const int id, TIMERPROC timeProc) 
	: _hwnd (hwnd), 
	  _id (id),
	  _timeProc (timeProc)
{}

//-----------------------------------------------------------
// This method set the data members of the Win::Timer object.
// 
// Parameters:
//
// const Win::Base hwnd -> Owner of the timer.
// const int id        -> Id of the timer.
// TIMERPROC timeProc  -> Procedure to be called by the timer
//					     If none specified, sends WM_TIMER.
//-----------------------------------------------------------

void Win::Timer::Create (const Win::Base hwnd, const int id, TIMERPROC timeProc)
{
	_hwnd     = hwnd ;
	_id       = id ;
	_timeProc = timeProc ;
}