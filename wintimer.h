//-----------------------------------------------------------
// This file contains only one class:  Win::Timer.
//-----------------------------------------------------------

#if !defined (WINTIMER_H)

	#define WINTIMER_H
	#include "useunicode.h"
	#include "win.h"

	namespace Win
	{
		//-----------------------------------------------------------
		// A Win::Timer object represents a Windows timer.  When a
		// timer is set, its either sends a WM_TIMER message or calls
		// a timer procedure at fixed time interval.  
		//-----------------------------------------------------------

		class Timer
		{
		public:

			Timer (const Win::Base hwnd = NULL, const int id = -1, TIMERPROC timeProc = NULL) ;
			void Create (const Win::Base hwnd, const int id, TIMERPROC timeProc = NULL) ;

			//-----------------------------------------------------------
			// Activate the timer by specifying him the time interval at
			// which its must send a WM_TIMER message or call the timer
			// procedure.
			// 
			// Parameters:
			//
			// const int milliSec -> Time interval in milliseconds.
			//-----------------------------------------------------------

			void Set (const int milliSec) const
			{
				if (::SetTimer (_hwnd, _id, milliSec, _timeProc) == 0)
					throw Win::Exception (TEXT("Error, could not create a timer")) ;

			}
		
			//------------------------------------------------------------
			// Terminate the timer, thus stopping it from sending WM_TIMER
			// messages or calling the timer procedure.
			//------------------------------------------------------------

			void Kill () const
			{
				if (::KillTimer (_hwnd, _id) == 0)
					throw Win::Exception (TEXT("Error, the timer could not be killed!")) ;
			}

			//------------------------------------------------------------
			// Return the id of the timer.
			// 
			// Return value:  The id of the timer.
			//------------------------------------------------------------

			int  GetId () const 
			{
				return _id ; 
			}

			private:
				Win::Base   _hwnd ;  //Owner.
				int        _id ; 
				TIMERPROC  _timeProc ;  // Called by the timer.
		} ;
	}

#endif