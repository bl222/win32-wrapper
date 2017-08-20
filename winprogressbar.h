//-----------------------------------------------------------------
//  This file contains classes that allow using progress bar controls.
//-----------------------------------------------------------------

#if !defined (WINPROGRESSBAR_H)

	#define WINPROGRESSBAR_H
	#include "useunicode.h"
	#include "wincommoncontrol.h"
	#include "wincontrol.h"
	#include "winicon.h"

	namespace Win
	{
		//-----------------------------------------------------------------
		//  Used to load the Progess Bar from the DLL.
		//-----------------------------------------------------------------
		class UsingProgressBar : UsingCommonControl 
		{
		public:
			UsingProgressBar ()
				:  UsingCommonControl (ICC_PROGRESS_CLASS) 
			{}
		} ;

		//-------------------------------------------------------------------------
		// Win::ProgressBar encapsulates a progress bar bar control handle.  Represent a status
		// bar control.  Inherit from Win::SimpleControl for basic functionality.
		//-------------------------------------------------------------------------

		class ProgressBarHandle : public SimpleControlHandle
		{
			
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle to represent the status bar
			// control through it's parent.
			// 
			// Parameters:
			//
			// const HWND parent -> Parent of the static control.
			// const int id      -> Id of the static control.
			//-------------------------------------------------------------------------

			ProgressBarHandle (const Win::Base parent, const int id)
				: SimpleControlHandle (parent, id) 
			{}

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle directly
			// 
			// Parameters:
			//
			// const HWND win -> Handle of the static control.
			//-------------------------------------------------------------------------

			ProgressBarHandle (const Win::Base win = NULL)
				: SimpleControlHandle (win)
			{}

			//-------------------------------------------------------------------------
			// Initialize the handle and the id through the parent handle.
			//-------------------------------------------------------------------------

			void Init (const Win::Base parent, const int id)
			{
				SimpleControlHandle::Init (parent, id) ;
			}

			//-------------------------------------------------------------------------
			// Obtains the current position of the progress bar.
			//
			// Return value: The current position
			//-------------------------------------------------------------------------

			UINT GetPosition ()
			{
				return SendMessage (PBM_GETPOS) ;
			}

			void GetRange (int & min, int & max) ;

			//-------------------------------------------------------------------------
			// Changes the color of the bar
			//
			// Parameter:
			//
			// Win::Color & color -> The new color.
			//-------------------------------------------------------------------------

			void SetBarColor (Win::Color & color)
			{
				SendMessage (PBM_SETBARCOLOR, 0, color.GetColorRef ()) ;
			}

			//-------------------------------------------------------------------------
			// Changes the background color
			//
			// Parameter:
			//
			// Win::Color & color -> The new color.
			//-------------------------------------------------------------------------

			void SetBackgroundColor (Win::Color & color)
			{
				SendMessage (PBM_SETBKCOLOR, 0, color.GetColorRef ()) ;
			}

			//-------------------------------------------------------------------------
			// Changes the current position of the progress bar.
			//
			// Parameters:
			//
			// const int pos -> The new position
			//-------------------------------------------------------------------------

			void SetPosition (const int pos)
			{
				SendMessage (PBM_SETPOS, pos) ;
			}

			//-------------------------------------------------------------------------
			// Increment the current position of the progress bar.
			//
			// Parameters:
			//
			// const int incr -> The value by witch the pos will be incremented
			//-------------------------------------------------------------------------

			void IncrementPosition (const int incr)
			{
				SendMessage (PBM_DELTAPOS, incr) ;
			}

			//-------------------------------------------------------------------------
			// Changes the range of the progress bar.
			//
			// Parameters:
			//
			// const int min -> The new minimum range
			// const int max -> the new maximum range
			//-------------------------------------------------------------------------

			void SetRange (const int min, const int max)
			{
				SendMessage (PBM_SETRANGE, 0, MAKELPARAM (min, max)) ;
			}

			//-------------------------------------------------------------------------
			// Changes the range of the progress bar.
			//
			// Parameters:
			//
			// const int min -> The new minimum range
			// const int max -> the new maximum range
			//-------------------------------------------------------------------------

			void SetRange32 (const int min, const int max)
			{
				SendMessage (PBM_SETRANGE32, min, max) ;
			}

			//-------------------------------------------------------------------------
			// Changes the incremental step of the progress bar.
			//
			// Parameters:
			//
			// const int step -> The new incremental step
			//-------------------------------------------------------------------------

			void SetStep (const int step)
			{
				SendMessage (PBM_SETSTEP, step) ;
			}

			//-------------------------------------------------------------------------
			// Increment the position by the incremental step
			//-------------------------------------------------------------------------

			void Step ()
			{
				SendMessage (PBM_STEPIT) ;
			}

			
		} ;


		//-------------------------------------------------------------------------
		// Win::ProgressBarHandleCreator allows to create an ProgressBarHandle control.
		// Inherit from Win::ControlCreator for basic functionality.
		//-------------------------------------------------------------------------	

		class ProgressBarCreator : public CommonControlCreator
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Creates an progress bar control with the functionality of 
			// Win::ControlCreator.
			//-------------------------------------------------------------------------

			ProgressBarCreator (Win::Base parent, int id)
				: CommonControlCreator (std::tstring (PROGRESS_CLASS), parent, id)
			{}

			//-------------------------------------------------------------------------
			// Creates a newprogress bar control.
			// 
			// Return value:  The progress bar control handle.
			//
			// Parameters:
			//
			// const std::tstring title -> The title of the progress bar control.
			//-------------------------------------------------------------------------

			Win::ProgressBarHandle Create (const std::tstring title) const
			{
				return ChildCreator::Create (title) ;
			}

			//-------------------------------------------------------------------------
			// The following methods all serve the same purpose.  They set one of the 
			// style of the future ProgressBarHandle control.
			//-------------------------------------------------------------------------

			void SetSmoothStyle   () {_style |= PBS_SMOOTH ;}
			void SetVerticalStyle () {_style |= PBS_VERTICAL ;}

		} ;
	}

#endif