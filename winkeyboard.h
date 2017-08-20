//--------------------------------------------------------------------
// This file contains a class and functions linked to the keyboard.
//--------------------------------------------------------------------

#if !defined (WINKEYBOARD_H)

	#define WINKEYBOARD_H
	#include "useunicode.h"
	#include <windows.h>

	namespace Win
	{
		namespace Key
		{
			//--------------------------------------------------------------------
			// Win::KeyData encapsulates the key information that comes with the 
			// with keyboard messages in the lParam parameter.
			//--------------------------------------------------------------------

			class Data
			{
			public:

				//--------------------------------------------------------------------
				// Constructor.  Creates the Win::KeyData object with the lParam from
				// keyboard messages.
				//
				// Parameters:
				//
				// const LPARAM flag -> The information on the key that was pressed.
				//--------------------------------------------------------------------

				Data (const LPARAM flag) 
					: _flag (flag) 
				{}

				//--------------------------------------------------------------------
				// Returns the number of key stokes represented by the message.
				//
				// Return value:  The reapeat count.
				//--------------------------------------------------------------------

				unsigned int GetRepeatCount () const 
				{
					return _flag & REPEATCOUNT ;
				}

				//--------------------------------------------------------------------
				// Returns the OEM scan code of the pressed key.
				//
				// Return value:  The OEM scan code.
				//--------------------------------------------------------------------

				unsigned int GetOEMScanCode () const 
				{
					return _flag & OEMSCANCODE ;
				}

				//--------------------------------------------------------------------
				// Determines if the key is an extended key.
				//
				// Return value:  True if the key is an extended key, else false.
				//--------------------------------------------------------------------

				bool IsExtendedKey () const 
				{
					return (_flag & EXTENDEDKEYFLAG) == 1 ;
				}

				//--------------------------------------------------------------------
				// Determines if the alt key is not pressed.
				//
				// Return value:  True if the alt key is not pressed, else false.
				//--------------------------------------------------------------------

				bool IsAltKeyDepressed () const 
				{
					return (_flag & CONTEXTCODE) == 1 ;
				}

				//--------------------------------------------------------------------
				// Determines if the key was previously down.
				//
				// Return value:  True if the key was previously down, else false.
				//--------------------------------------------------------------------

				bool IsKeyPreviouslyDown () const 
				{
					return (_flag & PREVIOUSKEYSTATE) == 1 ;
				}

				//--------------------------------------------------------------------
				// Determines if the key is being press or depressed.
				//
				// Return value:  True if the key is being press, else false.
				//--------------------------------------------------------------------

				bool IsKeyPress  () const 
				{
					return (_flag & TRANSITIONKEY) == 0 ;
				}

				//--------------------------------------------------------------------
				// Returns the key data unmodified.
				//
				// Return value:  The key data.
				//--------------------------------------------------------------------

				LPARAM GetKeyData () const 
				{
					return _flag ;
				}

				//--------------------------------------------------------------------
				// Converts the Key::Data object a LPARAM
				// Used for compatibility with the WinAPI.
				//--------------------------------------------------------------------

				operator LPARAM () const
				{
					return _flag ;
				}

			private:
				LPARAM _flag ; //The key data.

			private:

				//--------------------------------------------------------------------
				// Constants used by Win::KeyData to easily access the key information.
				//--------------------------------------------------------------------

				static const unsigned int REPEATCOUNT ;
				static const unsigned int OEMSCANCODE ;
				static const unsigned int EXTENDEDKEYFLAG ;
				static const unsigned int CONTEXTCODE ;
				static const unsigned int PREVIOUSKEYSTATE ;
				static const unsigned int TRANSITIONKEY ;
			} ;

			//---------------------------------------------------------------
			// Determine if a key is pressed.  Use only in keyboard messages.
			//
			// Return value:  True is the key is being pressed, else false.
			//
			// Parameters:
			//
			// const int key -> The virtual key code of the key
			//---------------------------------------------------------------

			inline bool IsPressed (const int key)
			{
				return ::GetKeyState (key) < 0 ;
			}

			//---------------------------------------------------------------
			// Determine asynchronically if a key is pressed.
			//
			// Return value:  True is the key is being pressed, else false.
			//
			// Parameters:
			//
			// const int key -> The virtual key code of the key
			//---------------------------------------------------------------

			inline bool IsPressedAsync (int key)
			{
				return ::GetAsyncKeyState (key) < 0 ;
			}
		}
}

#endif