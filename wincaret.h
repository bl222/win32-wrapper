//------------------------------------------------------
// This file contains classes dealing with the caret.
//------------------------------------------------------

#if !defined (WINCARET_H)

	#define WINCARET_H
	#include "useunicode.h"
	#include "win.h"
	#include "windrawingtool.h"
	#include "winexception.h"

	namespace Win
	{
		//----------------------------------------------------------------
		// Win::Caret represents the caret.  Allows to create, destroy
		// and use the caret.
		//----------------------------------------------------------------

		class Caret
		{
		public:

			class Hider ;
			friend class Hider ;

			//----------------------------------------------------------------
			// Constructor.  Does not actually creates a caret.  Must call
			// the create method afterward.
			//
			// Parameters:
			//
			// const Win::Base hwnd -> The window using the caret.
			//----------------------------------------------------------------

			Caret  (const Win::Base hwnd = NULL)
					: _hwnd (hwnd)
			{}

			void SetOwningWindow (const Win::Base hwnd)
			{
				_hwnd = hwnd ;
			}

			void Create  (const int width, const int height, const Win::Bitmap::DDB::Handle bmp = NULL, const int x = 0, const int y = 0) ;
			void Destroy () ;
			//----------------------------------------------------------------
			// Obtains the position of the caret
			//
			// Parameters:
			//
			// Win::Point & point -> Will contain the coordinate of the 
			//						 position of the caret.
			//----------------------------------------------------------------

			void GetPosition (Win::Point & point) const 
			{
				if (::GetCaretPos (reinterpret_cast <LPPOINT> (&point)) == 0)
					throw Win::Exception (TEXT("Error, could not get the caret position!"));
			}

			Win::Point GetPosition () const ;
			void GetPosition (int x, int y) const ;

			//----------------------------------------------------------------
			// Obtains the time interval at which the cursor blink.
			//
			// Return value: The time interval of the blinking.
			//----------------------------------------------------------------

			UINT GetBlinkTime () const
			{
				return ::GetCaretBlinkTime () ;
			}

			//----------------------------------------------------------------
			// Sets the position of the caret.
			//
			// Parameters:
			//
			// const int x -> New x coordinate.
			// const int y -> New x coordinate.
			//----------------------------------------------------------------

			void SetPosition (const int x, const int y) const
			{
				if (::SetCaretPos (x, y) == 0)
					throw Win::Exception (TEXT("Error, could not set the position of the carret.")) ;
			}

			//----------------------------------------------------------------
			// Sets the time interval at which the cursor blink.
			//
			// Parameters:
			//
			// const UINT milliSec -> The time interval in milliseconds.
			//----------------------------------------------------------------

			void SetBlinkTime (const UINT milliSec) const
			{
				if (::SetCaretBlinkTime (milliSec) == 0)
					throw Win::Exception (TEXT("Error, could not set the blinking time of the carret")) ;
			}

			//--------------------------------------------------------------------
			// Win::Caret::Holder is used hide the caret.  When a 
			// Win::Caret::Hider is created, the caret is hidden.  When the object 
			// is destroyed, the caret us shown.
			//--------------------------------------------------------------------

			class Hider
			{
			public:

				//--------------------------------------------------------------------
				// Constructor.  Hide the caret.
				//--------------------------------------------------------------------

				Hider (const Win::Caret & caret)
					: _caret (caret)
				{
					if (!::HideCaret (_caret._hwnd)) // Makes sure the caret was hidden.
						throw (TEXT("The caret could not be hidden")) ;
				}

				//--------------------------------------------------------------------
				// Destructor. Show the caret.
				//--------------------------------------------------------------------

				~Hider ()
				{
					::ShowCaret (_caret._hwnd);
				}
			private:

				const Win::Caret & _caret ;  // The carret being hidden.
			} ;

		private:
			Caret (Win::Caret & caret) ;
			Win::Caret operator = (Win::Caret & caret) ;
		private:

			Win::Base _hwnd ; // Owner of the caret.
		} ;
	} 

#endif