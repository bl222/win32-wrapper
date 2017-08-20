//---------------------------------------------------------------------------
// This file contains the predefined window procedure as well as
// some classes encapsulating parameters for some messages.
//---------------------------------------------------------------------------

#if !defined (WNDPROC_H)

	#define WNDPROC_H

	#include "useunicode.h"
	#include "winunicodehelper.h"
	#include "win.h"
	#include "winencapsulation.h"
	#include "wincanvas.h"
	#include "winmenu.h"

	namespace Win
	{
		//---------------------------------------------------------------------------
		// Win::CreationData encapsulates a CREATESTRUCT through private inheritance
		// The parameter of the WM_CREATE message is a CREATESTRUCT.
		//
		// Dara members of CREATESTRUCT:
		//
		// lpCreateParams -> Additional data, contains the lpParam of the 
		//                   CreateWindowEx call.
		// x              -> X coordinate of the window.
		// y              -> Y coordinate of the window.
		// cx             -> Width of the window.
		// cy             -> Height of the window.
		// lpszClass      -> Name of the Win::Class object used to create the window.
		// lpszName       -> Title of the window.
		// hInstance      -> Instance of the program.
		// hMenu          -> Handle of the menu.
		// hwndParent     -> Handle of the parent of the window.
		// style          -> Style of the window.
		// dwExStyle      -> Extended style of the window. 
		//---------------------------------------------------------------------------

		class CreationData : private CREATESTRUCT
		{
		public :

			//----------------------------------------------------------------
			// Obtains a pointer on the additional creation data.
			//
			// Return value: Void pointer on the creation data.
			//----------------------------------------------------------------

			void * GetCreationData () const 
			{
				return lpCreateParams ;
			}

			//----------------------------------------------------------------
			// Obtains the initial x coordinate of the window.
			//
			// Return value: Initial x coordinate of the window.
			//----------------------------------------------------------------

			int GetX () const 
			{
				return x ;
			}

			//----------------------------------------------------------------
			// Obtains the initial y coordinate of the window.
			//
			// Return value: Initial y coordinate of the window.
			//----------------------------------------------------------------

			int GetY () const 
			{
				return y ;
			}

			//----------------------------------------------------------------
			// Obtains the initial width of the window.
			//
			// Return value: Initial width of the window.
			//----------------------------------------------------------------

			int GetWidth () const 
			{
				return cx ;
			}

			//----------------------------------------------------------------
			// Obtains the initial height of the window.
			//
			// Return value: Initial height of the window.
			//----------------------------------------------------------------

			int GetHeight () const 
			{
				return cy ;
			}

			//----------------------------------------------------------------
			// Obtains the name of the Win::Class object used to create the 
			// window.
			//
			// Return value: The name of the Win::Class object.
			//----------------------------------------------------------------

			const std::tstring GetClassName () const 
			{
				return lpszClass ;
			}

			//----------------------------------------------------------------
			// Obtains the title of the window.
			//
			// Return value: The title of the window.
			//----------------------------------------------------------------

			const std::tstring GetWindowName () const 
			{
				return lpszName ;
			}

			//----------------------------------------------------------------
			// Obtains the instance of the program.
			//
			// Return value: The instance of the program.
			//----------------------------------------------------------------

			HINSTANCE GetInstance () const 
			{
				return hInstance ;
			}

			//----------------------------------------------------------------
			// Obtains a weak handle on the menu of the window.
			//
			// Return value: A weak handle on the menu of the window.
			//----------------------------------------------------------------

			Win::Menu::Handle GetMenu () const 
			{
				return hMenu ;
			}//----------------------------------------------------------------

			
			// Obtains the parent of the window.
			//
			// Return value: The parent of the window.
			//----------------------------------------------------------------

			Win::dow::Handle GetParent () const 
			{
				return hwndParent ;
			}
			
			//----------------------------------------------------------------
			// Obtains the style of the window.
			//
			// Return value: The style of the window.
			//----------------------------------------------------------------

			LONG GetStyle () const 
			{
				return style ;
			}

			//----------------------------------------------------------------
			// Obtains the extended style of the window.
			//
			// Return value: The extended style of the window.
			//----------------------------------------------------------------

			DWORD GetStyleEX () const 
			{
				return dwExStyle ;
			} 

		private:
			
			CreationData (CreationData & data) ;
			CreationData operator = (CreationData & data) ;
			
		} ;

		//----------------------------------------------------------------
		// Win::ActivateAction encapsulates the flag that come with the 
		// WM_ACTIVATE message in the wParam parameter.
		//----------------------------------------------------------------

		class ActivateAction
		{
		public:

			//--------------------------------------------------------------------
			// Constructor.  Creates the Win::ActivateAction object with the 
			// lParam from WM_ACTIVATE messages.
			//
			// Parameters:
			//
			// const LPARAM flag -> The information on the window that is shown.
			//--------------------------------------------------------------------

			ActivateAction (int action) 
				: _action (action)
			{}

			//----------------------------------------------------------------------
			// Determines if the window is being activated but not by a mouse click.
			//
			// Return value: True if the window is being activated but not by a 
			//               mouse click, else false.  
			//----------------------------------------------------------------------

			bool isActive () const 
			{
				return _action == WA_ACTIVE ;
			}

			//----------------------------------------------------------------------
			// Determines if the window is being deactivated.
			//
			// Return value: True if the window is being deactivated, else false.  
			//----------------------------------------------------------------------

			bool isInactive () const 
			{
				return _action == WA_INACTIVE ;
			}

			//----------------------------------------------------------------------
			// Determines if the window is being activated by a mouse click.
			//
			// Return value: True if the window is being activated by a 
			//               mouse click, else false.  
			//----------------------------------------------------------------------

			bool isClickActive () const 
			{
				return _action == WA_CLICKACTIVE ;
			}

			//--------------------------------------------------------------------
			// Converts the ActivateAction object into a int
			// Used for compatibility with the WinAPI.
			//--------------------------------------------------------------------

			operator int () const
			{
				return _action ;
			}

		private:

			int _action ; // The action accomplished on the window.
		} ;

		//---------------------------------------------------------------
		// Win::ShowWindowStatus encapsulate the flag that comes with the 
		// WM_SHOWWINDOW message in the lParam parameters
		//---------------------------------------------------------------

		class ShowWindowStatus
		{
		public:

			//--------------------------------------------------------------------
			// Constructor.  Creates the Win::ShowWindowStatus object with the 
			// lParam from WM_SHOWWINDOW messages.
			//
			// Parameters:
			//
			// const LPARAM flag -> The information on the window that is shown.
			//--------------------------------------------------------------------

			ShowWindowStatus (int status) 
				: _status(status) 
			{}

			//--------------------------------------------------------------------
			// Determines if the message was received due to a call to ShowWindow.
			//
			// Return value: True if ShowWindow was called, else false.  
			//--------------------------------------------------------------------

			bool ShowWindowWasCalled () const 
			{
				return _status == 0 ;
			}

			//--------------------------------------------------------------------
			// Determines if the message was received due to the fact that the
			// window was uncovered.
			//
			// Return value: True if the window was uncovered, else false.  
			//--------------------------------------------------------------------

			bool WindowIsUncovered () const 
			{
				return _status == SW_OTHERUNZOOM ;
			}

			//--------------------------------------------------------------------
			// Determines if the message was received due to the fact that the
			// window was covered.
			//
			// Return value: True if the window was covered, else false.  
			//--------------------------------------------------------------------

			bool WindowIsCovered () const 
			{
				return _status == SW_OTHERZOOM ;
			}

			//--------------------------------------------------------------------
			// Determines if the message was received due to the fact that the
			// parent was minimized.
			//
			// Return value: True if the parent was minimized, else false.  
			//--------------------------------------------------------------------

			bool ParentBeingMinimised () const 
			{
				return _status == SW_PARENTCLOSING ;
			}

			//--------------------------------------------------------------------
			// Determines if the message was received due to the fact that the
			// parent was maximised.
			//
			// Return value: True if the parent was maximised, else false.  
			//--------------------------------------------------------------------

			bool ParentBeingRestored  () const 
			{
				return _status == SW_PARENTOPENING ;
			}

			//--------------------------------------------------------------------
			// Converts the ShowWindowStatus object into a int
			// Used for compatibility with the WinAPI.
			//--------------------------------------------------------------------

			operator int () const
			{
				return _status ;
			}

		private:

			int _status ; // Status of the window that was shown/hidden.
		} ;

		//-----------------------------------------------------------------
		// Win::SizeType encapsulating the flag that comes with the WM_SIZE 
		// message in the wParam parameters
		//-----------------------------------------------------------------

		class SizeType
		{
		public:

			//--------------------------------------------------------------------
			// Constructor.  Creates the Win::SizeType object with the 
			// wParam from WM_SIZE messages.
			//
			// Parameters:
			//
			// const LPARAM flag -> The information on the window that is resized.
			//--------------------------------------------------------------------

			SizeType (WPARAM style)
				: _style(style) 
			{}

			//--------------------------------------------------------------------
			// Determines if the message was received due to the fact that 
			// another window was maximized.
			//
			// Return value: True if another window was maximized, else false.  
			//--------------------------------------------------------------------

			bool OtherWindowMaximised () const 
			{
				return _style == SIZE_MAXHIDE ;
			}

			//--------------------------------------------------------------------
			// Determines if the message was received due to the fact that 
			// another window was restored to its previous size.
			//
			// Return value: True if another window was restored to its previous 
			// size, else false.  
			//--------------------------------------------------------------------

			bool OtherWindowRestoreSize () const 
			{
				return _style == SIZE_MAXSHOW ;
			}

			//--------------------------------------------------------------------
			// Determines if the message was received due to the fact that the
			// window was minimized
			//
			// Return value: True if the window was minimized, else false.  
			//--------------------------------------------------------------------

			bool IsBeingMinimised () const 
			{
				return _style == SIZE_MINIMIZED ;
			}

			//--------------------------------------------------------------------
			// Determines if the message was received due to the fact that the
			// window was maximized
			//
			// Return value: True if the window was maximized, else false.  
			//--------------------------------------------------------------------

			bool IsBeingMaximised () const 
			{
				return _style == SIZE_MAXIMIZED ;
			}

			//--------------------------------------------------------------------
			// Determines if the message was received due to the fact that the
			// window was resized
			//
			// Return value: True if the window was resized, else false.  
			//--------------------------------------------------------------------

			bool isBeingResized () const 
			{
				return _style == SIZE_RESTORED ;
			}

			//--------------------------------------------------------------------
			// Converts the SizeType object into a WPARAM
			// Used for compatibility with the WinAPI.
			//--------------------------------------------------------------------

			operator WPARAM () const
			{
				return _style ;
			}

		private:
			WPARAM _style ; // Style of the window that was resized.
		} ;

	typedef LRESULT (CALLBACK * ProcPtr)
		(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		// The predefined window procedure.

		LRESULT CALLBACK Proc ( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) ;

		// The predefined window procedure for frame window.
		LRESULT CALLBACK FrameProc ( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) ;

		// The predefined window procedure for MDI child.
		LRESULT CALLBACK MDIChildProc ( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) ;

		// The predefined window procedure used for window subclasing.
		LRESULT CALLBACK SubProcedure
			(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		class ControlColor
		{
		public:
			friend LRESULT CALLBACK Win::Proc ( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) ;
			friend LRESULT CALLBACK FrameProc ( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) ;
			friend LRESULT CALLBACK MDIChildProc ( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) ;
			friend LRESULT CALLBACK SubProcedure (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
			ControlColor ()
			{
				_brush = NULL ;
				_flag = 0 ;
			}

			void SetBrush (HBRUSH brush) 
			{
				_brush = brush ;
			}

			void SetTextColor (Win::Color & textColor)
			{
				_flag |= 0x01 ;
				_textColor = textColor ;
			}

			void SetBackgroundColor (Win::Color & backColor)
			{
				_flag |= 0x02 ;
				_backColor = backColor ;
			}

		private:

			bool ChangedTextColor ()
			{
				return (_flag & 0x01) != 0 ;
			}

			bool ChangedBackgroundColor ()
			{
				return (_flag & 0x02) != 0 ;
			}

			HBRUSH     _brush ;
			Win::Color _textColor ;
			Win::Color _backColor ;
			BYTE       _flag ;
		} ;
	}
	

#endif