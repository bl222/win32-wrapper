//------------------------------------------------
// This file contains only one class:  Win::Class
//------------------------------------------------

#if !defined (WINCLASS_H)

	#define WINCLASS_H
	#include "useunicode.h"
	#include "winicon.h"
	#include "winexception.h"
	#include "wincursor.h"
	#include "windrawingtool.h"
	#include "winunicodehelper.h"

	LRESULT CALLBACK Proc ( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) ;

	namespace Win
	{
		//---------------------------------------------------------------------
		// Win::Class encapsulates a WNDSTRUCTEX structure.  A Win::Class
		// object is used to indicate the various characteristics of a window.
		// It is then possible to create many windows using those 
		// characteristics. In a way, a Win::Class object allow you to define a 
		// type of window, and then windows of that type are created. In order
		// to define such a type, all that must be done is set the appropriate 
		// field of the Win::Class object with the desired value and call the
		// Register method.
		//---------------------------------------------------------------------

		class Class
		{
		public:
			Class (const std::tstring & className, const HINSTANCE hInst) ;
			virtual ~Class ()
			{}

			//--------------------------------------------------------------------
			// In order to be able to create a window of the type defined by the
			// Win::Class object, the Register method must be called.  Once this
			// is done, use a Win::Creator object to create a Window.
			//--------------------------------------------------------------------

			void Register () const
			{
				if(!::RegisterClassEx( &_wndClass ))
					throw Win::Exception (TEXT("Error, could not register class.")) ;
			}

			//--------------------------------------------------------------------------
			// It is possible to reserve some memory space to the class for various
			// purposes.  This method allow to set how many byte of memory must be 
			// reserved.
			//
			// Parameters:
			//
			// const int extra -> Number of bytes that must be reserved. (0 by default)
			//--------------------------------------------------------------------------

			void SetClassExtra (const int extra) 
			{
				_wndClass.cbClsExtra = extra ;
			}

			//-------------------------------------------------------------------------
			// It is possible to reserve some memory space to a window for various
			// purposes.  This method allow to set how many byte of memory must be 
			// reserved for this type of window.
			//
			// Parameters:
			//
			// const int extra -> Number of bytes that must be reserved. (0 by default)
			//-------------------------------------------------------------------------

			void SetWindowsExtra (const int extra)
			{
				_wndClass.cbWndExtra = extra ;
			}

			//----------------------------------------------------------------------
			// Gives the class the CS_BYTEALIGNCLIENT style.
			//----------------------------------------------------------------------

			void SetByteAlignClient ()
			{
				_wndClass.style |= CS_BYTEALIGNCLIENT ;
			}

			//----------------------------------------------------------------------
			// Gives the class the CS_BYTEALIGNWINDOWT style.
			//----------------------------------------------------------------------

			void SetByteAlignWindow ()
			{
				_wndClass.style |= CS_BYTEALIGNWINDOW ;
			}

			//----------------------------------------------------------------------
			// Gives the class the CS_CLASSDC style.
			//----------------------------------------------------------------------

			void SetClassDeviceContext ()
			{
				_wndClass.style |= CS_CLASSDC ;
			}

			//----------------------------------------------------------------------
			// Gives the class the CS_DBLCLKS style.
			//----------------------------------------------------------------------

			void SetDoubleClick ()
			{
				_wndClass.style |= CS_DBLCLKS ;
			}

			//----------------------------------------------------------------------
			// Gives the class the CS_GLOBALCLASS style.
			//----------------------------------------------------------------------

			void SetGlobalClass ()
			{
				_wndClass.style |= CS_GLOBALCLASS ;
			}

			//----------------------------------------------------------------------
			// Gives the class the CS_HREDRAW style.
			//----------------------------------------------------------------------

			void SetHorizontalRedraw ()
			{
				_wndClass.style |= CS_HREDRAW ;
			}

			//----------------------------------------------------------------------
			// Gives the class the CS_VREDRAW style.
			//----------------------------------------------------------------------

			void SetVerticalRedraw ()
			{
				_wndClass.style |= CS_VREDRAW ;
			}

			//----------------------------------------------------------------------
			// Gives the class the CS_NOCLOSE style.
			//----------------------------------------------------------------------

			void SetNoClose ()
			{
				_wndClass.style |= CS_NOCLOSE ;
			}

			//----------------------------------------------------------------------
			// Gives the class the CS_OWNDC style.
			//----------------------------------------------------------------------

			void SetOwnDeviceContext ()
			{
				_wndClass.style |= CS_OWNDC ;
			}

			//----------------------------------------------------------------------
			// Gives the class the CS_PARENTDC style.
			//----------------------------------------------------------------------

			void SetParentDeviceContext ()
			{
				_wndClass.style |= CS_PARENTDC ;
			}

			//----------------------------------------------------------------------
			// Gives the class the CS_SAVEBITS style.
			//----------------------------------------------------------------------

			void SetSaveBitmap ()
			{
				_wndClass.style |= CS_SAVEBITS ;
			}

			//-----------------------------------------------------------
			// Sets the style using the WINAPI flags
			//
			// Parameters:
			//
			// UINT style -> The WINAPI flags.
			//-----------------------------------------------------------

			void SetStyle (UINT style)
			{
				_wndClass.style = style ;
			}

			//----------------------------------------------------------------------
			// Reset the style of the class.
			//----------------------------------------------------------------------

			void ResetStyle ()
			{
				_wndClass.style = 0;
			}

			//----------------------------------------------------------------------
			// Specify a menu resource to the Win::Class object.  The menu resource
			// is identified by a string (name).
			// 
			// Parameters:
			//
			// const std::tstring & menuName -> Name of the menu resource.
			//                                 (No menu by default)
			//---------------------------------------------------------------------

			void SetMenuName (const std::tstring menuName)
			{
				_wndClass.lpszMenuName = menuName.c_str () ;
			}

			//----------------------------------------------------------------------
			// Specify a menu resource to the Win::Class object.  The menu resource
			// is identified by a numerical id.
			// 
			// Parameters:
			//
			// const std::tstring & menuName -> Numerical id of the menu resource.
			//                                 (No menu by default)
			//---------------------------------------------------------------------

			void SetMenuName (const int id)
			{
				_wndClass.lpszMenuName = MAKEINTRESOURCE (id) ;
			}

			//----------------------------------------------------------------------
			// Specify an icon to the Win::Class object.  
			// 
			// Parameters:
			//
			// const Win::Icon::Handle -> Handle of the desired icon.
			//							 (Winlogo icon by default)
			//---------------------------------------------------------------------

			void SetIcons (const Win::Icon::Handle icon)
			{
				_wndClass.hIconSm = icon ;
				_wndClass.hIcon   = icon ;
			}

			//----------------------------------------------------------------------
			// Specify a cursor to the Win::Class object.  
			// 
			// Parameters:
			//
			// const Win::Cursor::Handle cursor -> Handle of the desired cursor.
			//									   (Arrow cursor by default)
			//---------------------------------------------------------------------

			void SetCursor (const Win::Cursor::Handle cursor)
			{
				_wndClass.hCursor = cursor ;
			}

			//----------------------------------------------------------------------
			// Specify a brush to the Win::Class object.  This brush is used to
			// repaint the background of the windows created from the Win::Class 
			// object
			// 
			// Parameters:
			//
			// const Win::Brush::Handle brush -> Handle of the desired brush.
			//										   (White brush by default)
			//---------------------------------------------------------------------

			void SetBrush (HBRUSH brush)//const Win::Brush::Solid::Handle brush)
			{
				_wndClass.hbrBackground = brush ;
			}

			//----------------------------------------------------------------------
			// Specify a brush to the Win::Class object.  This brush is used to
			// repaint the background of the windows created from the Win::Class 
			// object
			// 
			// Parameters:
			//
			// const Win::Brush::Handle brush -> Handle of the desired brush.
			//										   (White brush by default)
			//---------------------------------------------------------------------

			void SetBrush (const Win::Brush::Hatch::Handle brush)
			{
				_wndClass.hbrBackground = brush ;
			}

			//----------------------------------------------------------------------
			// Specify a brush to the Win::Class object.  This brush is used to
			// repaint the background of the windows created from the Win::Class 
			// object
			// 
			// Parameters:
			//
			// const Win::Brush::Handle brush -> Handle of the desired brush.
			//										   (White brush by default)
			//---------------------------------------------------------------------

			void SetBrush (const Win::Brush::Pattern::Handle brush)
			{
				_wndClass.hbrBackground = brush ;
			}
	
		private:

			Class (Win::Class & winClass) ;
			void operator = (Win::Class & winClass) ;

		protected:

			WNDCLASSEX   _wndClass ;
			std::tstring _name;
		} ;

		//---------------------------------------------------------------------
		// Win::FrameClass is the same as a Win::Class object except it is used
		// for frame windows in MDI application.
		//---------------------------------------------------------------------

		class FrameClass : public Win::Class
		{
		public:

			FrameClass (const std::tstring & className, const HINSTANCE hInst) ;

		private:

			FrameClass (Win::FrameClass & winClass) ;
			void operator = (Win::FrameClass & winClass) ;

		} ;

		//---------------------------------------------------------------------
		// Win::MDIChildClass is the same as a Win::Class object except it is used
		// for MDI child windows in MDI application.
		//---------------------------------------------------------------------

		class MDIChildClass : public Win::Class
		{
		public:

			MDIChildClass (const std::tstring & className, const HINSTANCE hInst) ;

		private:

			MDIChildClass (Win::MDIChildClass & winClass) ;
			void operator = (Win::MDIChildClass & winClass) ;

		} ;
	}

#endif