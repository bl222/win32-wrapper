//------------------------------------------------------------
// This file contains classes working with the mouse.
//------------------------------------------------------------

#if !defined (WINMOUSE_H)

#define WINMOUSE_H
	#include "useunicode.h"
	#include "winencapsulation.h"

	namespace Win
	{
		namespace Mouse
		{
			//----------------------------------------------------------------
			// Win::KeyState encapsulates the informations that comes with
			// mouse messages in the wParam.
			//----------------------------------------------------------------

			class KeyState
			{
			public:

				//--------------------------------------------------------------------
				// Constructor.  Creates the Win::KeyState object with the wParam from
				// mouse messages.
				//
				// Parameters:
				//
				// const LPARAM flag -> The information from the wParam of the message.
				//--------------------------------------------------------------------

				KeyState (WPARAM wParam)
					: _state(wParam) 
				{}

				//--------------------------------------------------------------------
				// Determines if the control key is pressed.
				//
				// Return value:  True if the control key is pressed, else false.
				//--------------------------------------------------------------------

				bool IsCtrlPressed    () const 
				{
					return (_state & MK_CONTROL) != 0 ;
				}

				//--------------------------------------------------------------------
				// Determines if the shift key is pressed.
				//
				// Return value:  True if the shift key is pressed, else false.
				//--------------------------------------------------------------------

				bool IsShiftPressed   () const 
				{
					return (_state & MK_SHIFT) != 0 ;
				}

				//--------------------------------------------------------------------
				// Determines if the left button of the mouse is pressed.
				//
				// Return value:  True if the left button of the mouse is pressed, 
				//                else false.
				//--------------------------------------------------------------------

				bool IsLeftButtonPressed () const 
				{
					return (_state & MK_LBUTTON) != 0 ;
				}

				//--------------------------------------------------------------------
				// Determines if the middle button of the mouse is pressed.
				//
				// Return value:  True if the middle button of the mouse is pressed, 
				//                else false.
				//--------------------------------------------------------------------

				bool IsMiddleButtonPressed () const 
				{
					return (_state & MK_MBUTTON) != 0 ;
				}

				//--------------------------------------------------------------------
				// Determines if the right button of the mouse is pressed.
				//
				// Return value:  True if the righ button of the mouse is pressed, 
				//                else false.
				//--------------------------------------------------------------------

				bool IsRightButtonPressed () const 
				{
					return (_state & MK_RBUTTON) != 0 ;
				}

				//--------------------------------------------------------------------
				// Returns the key state unmodified.
				//
				// Return value:  The key state data.
				//--------------------------------------------------------------------

				WPARAM GetKeyState () const 
				{
					return _state ;
				}

				//--------------------------------------------------------------------
				// Converts the KeyState object intoa WPARAM
				// Used for compatibility with the WinAPI.
				//--------------------------------------------------------------------

				operator WPARAM () const
				{
					return _state ;
				}

			private:
				WPARAM _state ; // the key state.

			} ;

			//----------------------------------------------------------------
			// Win::KeyState encapsulates the informations that comes with
			// non-client mouse messages in the wParam.
			//----------------------------------------------------------------

			class HitText
			{
			public:

				//--------------------------------------------------------------------
				// Constructor.  Creates the Win::HitTest object with the wParam from
				// non-client mouse messages.
				//
				// Parameters:
				//
				// const LPARAM flag -> The information from the wParam of the message.
				//--------------------------------------------------------------------

				HitText (int hit)
					: _hit (hit)
				{}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the client area.
				//
				// Return value:  True if the mouse was click on the client area, 
				// else false.
				//--------------------------------------------------------------------

				bool HitClient () const 
				{
					return _hit == HTCLIENT ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the screen background.
				//
				// Return value:  True if the mouse was click the screen background, 
				// else false.
				//--------------------------------------------------------------------

				bool HitNoWhere () const 
				{
					return _hit == HTNOWHERE ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on a window currently covered 
				// by another window .
				//
				// Return value:  True if the mouse was click on a window currently 
				// covered by another window else false.
				//--------------------------------------------------------------------

				bool HitTransparent () const 
				{
					return _hit == HTTRANSPARENT ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse generated an error.
				//
				// Return value:  True if the mouse click generated an error, 
				// else false.
				//--------------------------------------------------------------------

				bool HitError () const 
				{
					return _hit == HTERROR ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the border of a window.
				//
				// Return value:  True if the mouse was click on the border of a window, 
				// else false.
				//--------------------------------------------------------------------

				bool HitBorder () const 
				{
					return _hit == HTBORDER ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the lower horizontal
				// border of a window.
				//
				// Return value:  True if the mouse was click on the lower horizontal 
				// border of a window, else false.
				//--------------------------------------------------------------------

				bool HitBottom () const 
				{
					return _hit == HTBOTTOM ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the  lower left corner of a
				// border of a window.
				//
				// Return value:  True if the mouse was click on lower left corner of 
				// the the border of a window, else false.
				//--------------------------------------------------------------------

				bool HitBottomLeft () const 
				{
					return _hit == HTBOTTOMLEFT ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the  lower right corner of a
				// border of a window.
				//
				// Return value:  True if the mouse was click on lower right corner of 
				// the the border of a window, else false.
				//--------------------------------------------------------------------

				bool HitBottomRight () const 
				{
					return _hit == HTBOTTOMRIGHT ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the title bar of a window.
				//
				// Return value:  True if the mouse was click on the title bar  of a 
				// window, else false.
				//--------------------------------------------------------------------

				bool HitTitleBar () const 
				{
					return _hit == HTCAPTION ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the close button.
				//
				// Return value:  True if the mouse was click on the close button,
				// else false.
				//--------------------------------------------------------------------

				bool HitClose () const 
				{
					return _hit == HTCLOSE ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the size box.
				//
				// Return value:  True if the mouse was click on the size box, else 
				// false.
				//--------------------------------------------------------------------

				bool HitGrowBox () const 
				{
					return _hit == HTGROWBOX ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on a help button.
				//
				// Return value:  True if the mouse was click a help button, else false.
				//--------------------------------------------------------------------

				bool HitHelp () const 
				{
					return _hit == HTHELP ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on an horizontal scroll bar.
				//
				// Return value:  True if the mouse was click on a horizontal scroll
				// bar, else return false.
				//--------------------------------------------------------------------

				bool HitHorizontalScroll () const 
				{
					return _hit == HTHSCROLL ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the left of the
				// border of a window.
				//
				// Return value:  True if the mouse was click on the left of
				// the border of a window, else false.
				//--------------------------------------------------------------------

				bool HitLeft () const 
				{
					return _hit == HTLEFT ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on a menu.
				//
				// Return value:  True if the mouse was click on a menu, else false.
				//--------------------------------------------------------------------

				bool HitMenu () const 
				{
					return _hit == HTMENU ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the max button..
				//
				// Return value:  True if the mouse was click on the max button,
				// else false.
				//--------------------------------------------------------------------

				bool HitMaxButton () const 
				{
					return _hit == HTMAXBUTTON ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the min button.
				//
				// Return value:  True if the mouse was click on the min button,
				// else false.
				//--------------------------------------------------------------------

				bool HitMinButton () const 
				{
					return _hit == HTMINBUTTON ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the min button.
				//
				// Return value:  True if the mouse was click on the min button, else 
				// false.
				//--------------------------------------------------------------------

				bool HitReduce () const 
				{
					return _hit == HTREDUCE ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the right of the
				// border of a window.
				//
				// Return value:  True if the mouse was click on the right of
				// the border of a window, else false.
				//--------------------------------------------------------------------

				bool HitRight () const 
				{
					return _hit == HTRIGHT ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the size box.
				//
				// Return value:  True if the mouse was click on the sizebox, else 
				// false.
				//--------------------------------------------------------------------

				bool HitSize () const 
				{
					return _hit == HTSIZE ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on a system menu.
				//
				// Return value:  True if the mouse was click on a system menu, else 
				// false.
				//--------------------------------------------------------------------

				bool HitSystemMenu () const 
				{
					return _hit == HTSYSMENU ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the higher horizontal
				// border of a window.
				//
				// Return value:  True if the mouse was click on the higher horizontal 
				// border of a window, else false.
				//--------------------------------------------------------------------

				bool HitTop () const 
				{
					return _hit == HTTOP ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the higher left corner of a
				// border of a window.
				//
				// Return value:  True if the mouse was click on higher left corner of 
				// the the border of a window, else false.
				//--------------------------------------------------------------------

				bool HitTopLeft () const 
				{
					return _hit == HTTOPLEFT ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the higher right corner of a
				// border of a window.
				//
				// Return value:  True if the mouse was click on higher right corner of 
				// the the border of a window, else false.
				//--------------------------------------------------------------------

				bool HitTopRight () const 
				{
					return _hit == HTTOPRIGHT ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on an vertical scroll bar.
				//
				// Return value:  True if the mouse was click on a vertical scroll
				// bar, else return false.
				//--------------------------------------------------------------------

				bool HitVerticalScroll () const 
				{
					return _hit == HTVSCROLL ;
				}

				//--------------------------------------------------------------------
				// Determines if the mouse was click on the max button..
				//
				// Return value:  True if the mouse was click on the max button,
				// else false.
				//--------------------------------------------------------------------

				bool HitZoom () const 
				{
					return _hit == HTZOOM ;
				}

				//--------------------------------------------------------------------
				// Returns the hit testing data unmodified.
				//
				// Return value:  The hit testing data.
				//--------------------------------------------------------------------

				int GetHitTestData () const 
				{
					return _hit ;
				}

				//--------------------------------------------------------------------
				// Converts the Win::Mouse::KeyState object a int
				// Used for compatibility with the WinAPI.
				//--------------------------------------------------------------------

				operator int () const
				{
					return _hit ;
				}

			private:
				int _hit ; //The hit test data.

			} ;

			//--------------------------------------------------------------------
			// Obtains the cursor position.  
			//
			// Parameters:
			//
			// Win::Point & point -> This will contain the coordinates of the 
			//						 cursor position.
			//--------------------------------------------------------------------

			inline void GetCursorPosition (Win::Point & point)
			{
				::GetCursorPos (reinterpret_cast<LPPOINT> (&point)) ;
			}

			//--------------------------------------------------------------------
			// Set the cursor position.  
			//
			// Parameters:
			//
			// const int x -> x position of the cursor.
			// const int y -> y position of the cursor.
			//--------------------------------------------------------------------

			inline void SetCursorPosition (const int x, const int y)
			{
				::SetCursorPos (x, y) ;
			}
		}
	} 

#endif