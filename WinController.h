//----------------------------------------------------------------------
// This file contains two class.  Win::Controller allow access to
// the window procedure.  Win::SubController allow window subclassing.
//----------------------------------------------------------------------

#if !defined (WINCONTROLLER_H)

	#define WINCONTROLLER_H
	#include "useunicode.h"
	#include "wndproc.h"
	#include "winkeyboard.h"
	#include "winmouse.h"
	#include "winmenu.h"
	#include "winmessagepump.h"
	#include <map>
	//#include "winctrleventhandlers.h"




	namespace Win
	{

		struct ControlEventHandler;
		//----------------------------------------------------------------------
		// In traditional Window programming, every type of window has a 
		// Window procedure that offers treatment for the messages received by
		// the window.  The procedure is based on a switch/case.  
		// Win::BaseController be seen as the replacement of the window procedure, 
		// even though it is not exactly the case.  There is still a Window 
		// procedure, but every window use the same one (which is predefined).   
		// The Win::Controller class defines a lot of methods.  Most of these 
		// correspond to a window message.  When a Window is created, it's 
		// received as a parameter a controller.  For each message, the 
		// predefined window procedure call the corresponding method of the 
		// controller of the window.  To implement different treatment for
		// different messages, all that need to be done is to create a new
		// class that inherit from the proper controller and then implement the 
		// methods corresponding to the desired message and ignore the others.
		//----------------------------------------------------------------------

		class BaseController
		{
		public:
			virtual ~BaseController () 
			{}

			void RegisterControl (Win::dow::Handle ctrl, ControlEventHandler * handler)
			{
				_ctrlMap[ctrl] = handler;
			};

			//-------------------------------------------------------------
			// A Win::MessagePump object encapsulate a message loop.  One
			// of the data members of Win::Controller is a pointer on a 
			// Win::MessagePump so a Win::Controller object can have access
			// on the message loop used by the window.  This is necessary
			// for the use of modeless dialog.  The SetPump method 
			// initialize the Win::MessagePump pointer.
			//
			// Parameters:
			//
			// const Win::MessagePump & pump -> The Win::MessagePump object
			//                                  on which the pointer must
			//									points.
			//-------------------------------------------------------------

			void SetPump (Win::MessagePump & pump)
			{
				_pump = &pump ;
			}

			//-------------------------------------------------------------------
			// The following methods represents various window messages.  The
			// return value for each of them has the same meaning unless
			// else wise specified.
			// 
			// Return value:  True is the message is processed, else false.
			//-------------------------------------------------------------------

			//-------------------------------------------------------------------
			// Represents the WM_CREATE message.
			//
			// Parameters:
			//
			// Win::CreationData const * create -> An object encapsulating a
			//									   CREATESTRUCT.
			//-------------------------------------------------------------------

			virtual bool OnCreate (Win::CreationData const * create) throw ()
			{return false ;}

			//-------------------------------------------------------------------
			// Represents the WM_ACTIVATE message.
			//
			// Parameters:
			//
			// const Win::ActivateAction activate -> Data about how the window was
			//										 activated.
			// const bool isMinimised             -> True if window is minimized,
			//										 else false.
			// Win::dow::Handle prevWnd					  -> Handle of the window been
			//										 activated or desactivated.
			//-------------------------------------------------------------------

			virtual bool OnActivate (const Win::ActivateAction & activate, const bool isMinimised, Win::dow::Handle & prevWnd) throw ()
			{return false ;}

			//-------------------------------------------------------------------
			// Represents the WM_SETREDRAW message.
			//
			// Parameters:
			//
			// const bool mustBeRedrawn -> State of the redraw flag.
			//-------------------------------------------------------------------

			virtual bool OnSetRedraw (const bool mustBeRedrawn) throw ()
			{return false ;}

			//-------------------------------------------------------------------
			// Represents the WM_SHOWWINDOW message.
			//
			// Parameters:
			//
			// const bool isBeingShown				-> True if the window is being 
			//										   shown, else false.
			// const Win::ShowWindowStatus & status -> Status of the window being
			//                                         shown.
			//-------------------------------------------------------------------

			virtual bool OnShowWindow (const bool isBeingShown, const Win::ShowWindowStatus & status) throw ()
			{return false ;}

			//-------------------------------------------------------------------
			// Represents the WM_CLOSE message.
			//-------------------------------------------------------------------

			virtual bool OnClose () throw ()
			{return false ;}

			virtual bool OnQueryEndSession (unsigned int logOffFlag) throw ()
			{return true ;}

			//-------------------------------------------------------------------
			// Represents the WM_NCDESTROY message.
			//-------------------------------------------------------------------

			virtual bool OnNonClientDestroy () throw ()
			{return false ;}

			//-------------------------------------------------------------------
			// Represents the WM_DESTROY message.
			//-------------------------------------------------------------------

			virtual bool OnDestroy ()  throw ()
			{return false ;}

			//-------------------------------------------------------------------
			// Represents the WM_CANCEL message.
			//-------------------------------------------------------------------

			virtual bool OnCancelMode () throw ()
			{return false ;}

			//-------------------------------------------------------------------
			// Represents the WM_CAPTURECHANGE message.
			//
			// Parameters:
			//
			// Win::dow::Handle hasCaptureWnd -> Handle of the window capturing the 
			//							 mouse.
			//-------------------------------------------------------------------

			virtual bool OnCaptureChange (Win::dow::Handle & hasCaptureWnd) throw ()
			{return false ;}

			//-------------------------------------------------------------------
			// Represents the WM_ENABLE message.
			//
			// Parameters:
			//
			// const bool IsEnabled -> True if the window has been enabled, else
			//						   false.
			//-------------------------------------------------------------------

			virtual bool OnEnable (const bool IsEnabled) throw ()
			{return false ;}

			//-------------------------------------------------------------------
			// Represents the WM_ENTERIDLE message.
			//
			// Parameters:
			//
			// const bool byDialog -> True if idle because of dialog, false if 
			//						  idle because of menu.
			// Win::dow::Handle ownderWnd  -> Handle of the dialog box or window 
			//                        containing the displayed menu.
			//-------------------------------------------------------------------

			virtual bool OnEnterIdle (const bool byDialog, Win::dow::Handle & ownderWnd) throw ()
			{return false ;}

			//-------------------------------------------------------------------
			// Represents the WM_ENTERSIZEMOVE message.
			//-------------------------------------------------------------------

			virtual bool OnEnterSizeMove () throw ()
			{return false ;}

			//-------------------------------------------------------------------
			// Represents the WM_EXITSIZEMOVE message.
			//-------------------------------------------------------------------

			virtual bool OnExitSizeMove () throw () 
			{return false ;}

			//-------------------------------------------------------------------
			// Represents the WM_GETMINMAXIBFO message.
			//
			// Parameters:
			//
			// Win::MinMaxInfo * const minMax -> Use this to change maximized 
			//                                   position and dimensions, and the
			//									 minimum and maximum tracking sizes
			//-------------------------------------------------------------------

			virtual bool OnGetMinMaxInfo (Win::MinMaxInfo * const minMax) throw ()
			{return false ;}

			//-------------------------------------------------------------------
			// Represents the WM_SIZE message.
			//
			// Parameters:
			//
			// const int width            -> New width of the window.
			// const int height           -> New height of the window.
			// const Win::SizeType & type -> Indicate the type of resizing that is
			//								 occurring.
			//-------------------------------------------------------------------

			virtual bool OnSize (const int width, const int height, const Win::SizeType & type) throw ()
			{return false ;}

			//-------------------------------------------------------------------
			// Represents the WM_MOVE message.
			//
			// Parameters:
			//
			// const int x -> New x coordinate of the window.
			// const int y -> New y coordinate of the window.
			//-------------------------------------------------------------------

			virtual bool OnMove (int x, int y) throw ()
			{return false ;}
			
			//-------------------------------------------------------------------
			// Represents the WM_PAINT message.
			//-------------------------------------------------------------------

			virtual bool OnPaint () throw ()
			{return false ;}

			//---------------------------------------------------------------
			// The four following messages have to do with scroll bars.
			//---------------------------------------------------------------

			//-------------------------------------------------------------------------
			// Represents the WM_VSCROLL message when it's NOT send by a 
			// scrollbar control.  
			//
			// Parameters:
			//
			// const int thumbPos         -> Position of the thumb of the scrollbar.
			// const int notificationCode -> Represent the type of scrolling being
			//								 requested.
			//-------------------------------------------------------------------------

			virtual bool OnVerticalScroll (const int thumbPos, const int notificationCode) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_HSCROLL message when it's NOT send by a 
			// scrollbar control.  
			//
			// Parameters:
			//
			// const int thumbPos         -> Position of the thumb of the scrollbar.
			// const int notificationCode -> Represent the type of scrolling being
			//								 requested.
			//-------------------------------------------------------------------------

			virtual bool OnHorizontalScroll (const int thumbPos, const int notificationCode) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_VSCROLL message when it's sent by a 
			// scrollbar control.  
			//
			// Parameters:
			//
			// Win::dow::Handle scrollHandle      -> Handle of the scrollbar control.
			// const int scrollId         -> Id of the scrollbar.
			// const int thumbPos         -> Position of the thumb of the scrollbar.
			// const int notificationCode -> Represent the type of scrolling being
			//								 requested.
			//-------------------------------------------------------------------------

			virtual bool OnControlVerticalScroll (Win::dow::Handle & scrollHandle, const int scrollId, const int thumbPos, const int notificationCode) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_HSCROLL message when it's sent by a 
			// scrollbar control.  
			//
			// Parameters:
			//
			// Win::dow::Handle scrollHandle      -> Handle of the scrollbar control.
			// const int scrollId         -> Id of the scrollbar.
			// const int thumbPos         -> Position of the thumb of the scrollbar.
			// const int notificationCode -> Represent the type of scrolling being
			//								 requested.
			//-------------------------------------------------------------------------

			virtual bool OnControlHorizontalScroll (Win::dow::Handle & scrollHandle, int scrollId, int thumbPos, int notificationCode) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_ACTIVATEAPP message.
			//
			// Parameters:
			//
			// const bool isActive         -> True if the window is being activated, 
			//								  else false.
			// const unsigned int threadID -> Id of the thread.
			//-------------------------------------------------------------------------

			virtual bool OnOtherAppActivate (const bool isActive, const unsigned int threadID) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_TIMER message.
			//
			// Parameters:
			//
			// const WPARAM timerID        -> Id of the timer.
			// TIMERPROC * const timerProc -> Pointer to a TIMERPROC function.  May be
			//								  NULL.
			//-------------------------------------------------------------------------

			virtual bool OnTimer (const WPARAM timerID, TIMERPROC * const timerProc) throw ()
			{return false ;}

			
			//-------------------------------------------------------------------------
			// The 6 following messages indiquate a system change.
			//-------------------------------------------------------------------------

			//-------------------------------------------------------------------------
			//  Represents the WM_TIMECHANGE message
			//-------------------------------------------------------------------------

			virtual bool OnTimeChange () throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			//  Represents the WM_USERCHANGED message
			//-------------------------------------------------------------------------

			virtual bool OnUserChanged () throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			//  Represents the WM_DISPLAYCHANGE message
			//
			// Parameters:
			//
			// const unsigned int bitPerPixel -> The new number of bit per pixel of the 
			//									display.
			// const int horResolution        -> The new horizontal resolution of the 
			//									 display.
			// const int verResolution        -> The new vertical resolution of the 
			//									 display.
			//-------------------------------------------------------------------------

			virtual bool OnDisplayChange (const unsigned int bitPerPixel, const int horResolution, const int verResolution) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_COMPACTING message
			//
			// Parameters:
			//
			// const unsigned int compactRatio -> Ratio of CPU time spent by the system 
			//									  compacting memory to CPU time spent on 
			//									  other operations.
			//-------------------------------------------------------------------------

			virtual bool OnCompacting (const unsigned int compactRatio) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_ENDSESSION message
			//
			// Parameters:
			//
			// const bool IsEndSession -> True if it is the end of the session, else 
			//							  false.
			// const long logOffFlag   -> Always ENDSESSION_LOGOFF
			//-------------------------------------------------------------------------

			virtual bool OnEndSession (const bool IsEndSession, const long logOffFlag) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			//  Represents the WM_FONTCHANGE message
			//-------------------------------------------------------------------------

			virtual bool OnFontChange () throw ()
			{return false ;}

			//-----------------------------------------------------------------
			// The 5 following messages concerns menu.
			//-----------------------------------------------------------------

			//-------------------------------------------------------------------------
			// Represents the WM_ENTERMENLOOP message
			//
			// Parameters:
			//
			// const bool isTrackPopUpMenu -> True if the menu was entered through a 
			//								  call of the TrackPopUpMenu function.
			//-------------------------------------------------------------------------

			virtual bool OnEnterMenuLoop (const bool isTrackPopUpMenu) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_EXITMENLOOP message
			//
			// Parameters:
			//
			// const bool isTrackPopUpMenu -> True if the menu was entered through a 
			//								  call of the TrackPopUpMenu function.
			//-------------------------------------------------------------------------

			virtual bool OnExitMenuLoop (bool isTrackPopUpMenu) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_INITMENU message
			//
			// Parameters: 
			//
			// Win::Menu::Weak menuInit -> The handle of the menu about to be activated.
			//-------------------------------------------------------------------------

			virtual bool OnInitMenu (Win::Menu::Handle & menuInit) throw () 
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_INITMENUPOPUP message
			//
			// Parameters: 
			//
			// const unsigned int pos    -> Position of the menu item that openned the 
			//								dropdown menu. 
			// const bool isSystemMenu   -> True if the dropdown menu is the system menu.
			// Win::Menu::Weak menuPopup -> The handle of the drop down menu about to be 
			//							    activated.
			//-------------------------------------------------------------------------

			virtual bool OnInitMenuPopup (const unsigned int pos, const bool isSystemMenu, Win::Menu::Handle menuPopup) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_INITMENUPOPUP message
			//
			// Parameters: 
			//
			// const unsigned int x     -> x coordinate of the cursor at the time the
			//						       right button of the mouse.
			// const unsigned int y     -> y coordinate of the cursor at the time the
			//						       right button of the mouse.
			// Win::dow::Handle rightClickedWnd -> The window that was right-clicked.
			//-------------------------------------------------------------------------

			virtual bool OnContextMenu (const unsigned int x, const unsigned int y, Win::dow::Handle & rightClickedWnd) throw ()
			{return false ;}

			//-----------------------------------------------------------------
			// The 3 following messages concerns palettes.
			//-----------------------------------------------------------------

			//-------------------------------------------------------------------------
			// Represents the WM_PALETTECHANGED message.
			//
			// Parameters: 
			//
			// Win::dow::Handle changedPaletteWnd -> Handle of the window that changed the
			//								 system message.
			//-------------------------------------------------------------------------

			virtual bool OnPaletteChanged (Win::dow::Handle & changedPaletteWnd) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_PALETTEISCHANGING message.
			//
			// Parameters: 
			//
			// Win::dow::Handle paletteChangingWnd -> Handle of the window that will realize  
			//								  the palette.
			//-------------------------------------------------------------------------

			virtual bool OnPaletteIsChanging (Win::dow::Handle & paletteChangingWnd) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_QUERYNEWPALETTE message.
			//-------------------------------------------------------------------------

			virtual bool OnQueryNewPalette () throw ()
			{return false;}
			
			//-----------------------------------------------------------------
			// The 10 following messages concerns the keyboard.
			//-----------------------------------------------------------------		

			//-------------------------------------------------------------------------
			// Represents the WM_SETFOCUS message.
			//
			// Parameters: 
			//
			// Win::dow::Handle lostFocusWnd -> Handle of the window that has lost the 
			//							input focus.
			//-------------------------------------------------------------------------
		
			virtual bool OnSetFocus (Win::dow::Handle & lostFocusWnd) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_KILLFOCUS message.
			//
			// Parameters: 
			//
			// Win::dow::Handle getFocusWnd -> Handle of the window that has obtain the input
			//						   focus.
			//-------------------------------------------------------------------------

			virtual bool OnKillFocus (Win::dow::Handle & getFocusWnd) throw ()
			{return false ;}

			//-----------------------------------------------------------------
			// The 4 following keyboard messages have the same parameters.
			//
			// Parameters:
			//
			// const TCHAR charCode         -> The caracter code of the key that 
			//								   was pressed.
			// const Win::Key::Data & keyData -> Various data about the key.
			//-----------------------------------------------------------------

			//-------------------------------------------------------------------------
			// Represents the WM_CHAR message.
			//-------------------------------------------------------------------------

			virtual bool OnChar (const TCHAR charCode, const Win::Key::Data & keyData) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_SYSCHAR message.
			//-------------------------------------------------------------------------

			virtual bool OnSysChar (const TCHAR charCode, const Win::Key::Data & keyData) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_DEADCHAR message.
			//-------------------------------------------------------------------------

			virtual bool OnDeadChar (const TCHAR charCode, const Win::Key::Data & keyData) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_SYSDEADCHAR message.
			//-------------------------------------------------------------------------

			virtual bool OnSysDeadChar (const TCHAR charCode, const Win::Key::Data & keyData) throw ()
			{return false ;}

			//-----------------------------------------------------------------
			// The 4 following keyboard messages have the same parameters.
			//
			// Parameters:
			//
			// const unsigned int virtualKey -> Virtual code of the key that 
			//									was pressed
			// const Win::KeyData & keyData  -> Various data about the key.
			//-----------------------------------------------------------------

			//-------------------------------------------------------------------------
			// Represents the WM_KEYDOWN message.
			//-------------------------------------------------------------------------

			virtual bool OnKeyDown (const unsigned int virtualKey, const Win::Key::Data & keyData) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_SYSKEYDOWN message.
			//-------------------------------------------------------------------------

			virtual bool OnSysKeyDown (const unsigned int virtualKey, const Win::Key::Data & keyData) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_KEYUP message.
			//-------------------------------------------------------------------------

			virtual bool OnKeyUp (const unsigned int virtualKey, const Win::Key::Data & keyData) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_SYSKEYUP message.
			//-------------------------------------------------------------------------

			virtual bool OnSysKeyUp (const unsigned int virtualKey, const Win::Key::Data & keyData) throw ()
			{return false ;}

			//-----------------------------------------------------------------
			// The 20 following messages concerns the mouse.
			//-----------------------------------------------------------------

			//---------------------------------------------------------------------
			// The 10 following mouse messages have the same parameters.
			//
			// Parameters:
			//
			// const int x                    -> The x coordinate of the screen in 
			//									 client coordinates
			// const int y                    -> The y coordinate of the screen in 
			//									 client coordinates
			// const Win::Mouse::KeyState & keyState -> Various data about the mouse.
			//---------------------------------------------------------------------

			//-------------------------------------------------------------------------
			// Represents the WM_LBUTTONDBLCLK message.
			//-------------------------------------------------------------------------

			virtual bool OnLeftButtonDoubleClick (const int x, const int y, const Win::Mouse::KeyState & keyState) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_LBUTTONDOWN message.
			//-------------------------------------------------------------------------

			virtual bool OnLeftButtonDown (const int x, const int y, const Win::Mouse::KeyState & keyState) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_LBUTTONUP message.
			//-------------------------------------------------------------------------

			virtual bool OnLeftButtonUp (const int x, const int y, const Win::Mouse::KeyState & keyState) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_MBUTTONDBLCLK message.
			//-------------------------------------------------------------------------

			virtual bool OnMiddleButtonDoubleClick (const int x, const int y, const Win::Mouse::KeyState & keyState) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_MBUTTONDOWN message.
			//-------------------------------------------------------------------------

			virtual bool OnMiddleButtonDown (const int x, const int y, const Win::Mouse::KeyState & keyState) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_MBUTTONUP message.
			//-------------------------------------------------------------------------

			virtual bool OnMiddleButtonUp (const int x, const int y, const Win::Mouse::KeyState & keyState) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_RBUTTONDBLCLK message.
			//-------------------------------------------------------------------------

			virtual bool OnRightButtonDoubleClick (const int x, const int y, const Win::Mouse::KeyState & keyState) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_RBUTTONDOWN message.
			//-------------------------------------------------------------------------

			virtual bool OnRightButtonDown (const int x, const int y, const Win::Mouse::KeyState & keyState) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_RBUTTONUP message.
			//-------------------------------------------------------------------------

			virtual bool OnRightButtonUp (const int x, const int y, const Win::Mouse::KeyState & keyState) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_RBUTTONUP message.
			//-------------------------------------------------------------------------

			virtual bool OnMouseMove (const int x, const int y, const Win::Mouse::KeyState & keyState) throw ()
			{return false ;}

			//---------------------------------------------------------------------
			// The 10 following mouse messages have the same parameters.
			//
			// Parameters:
			//
			// const int xScreen          -> The x coordinate of the screen in 
			//								 screen coordinates
			// const int yScreen          -> The y coordinate of the screen in 
			//								 screen coordinates
			// const Win::HitText hitText -> Various data about hit testing.
			//---------------------------------------------------------------------

			//-------------------------------------------------------------------------
			// Represents the WM_NCLBUTTONDBLCLK message.
			//-------------------------------------------------------------------------

			virtual bool OnNCLeftButtonDoubleClick  (const int xScreen, const int yScreen, const Win::Mouse::HitText hitText)
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_NCLBUTTONDOWN message.
			//-------------------------------------------------------------------------

			virtual bool OnNCLeftButtonDown (const int xScreen, const int yScreen, const Win::Mouse::HitText hitText)
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_NCLBUTTONUP message.
			//-------------------------------------------------------------------------

			virtual bool OnNCLeftButtonUp  (const int xScreen, const int yScreen, const Win::Mouse::HitText hitText)
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_NCMBUTTONDBLCLK message.
			//-------------------------------------------------------------------------

			virtual bool OnNCMiddleButtonDoubleClick  (const int xScreen, const int yScreen, const Win::Mouse::HitText hitText)
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_NCMBUTTONDOWN message.
			//-------------------------------------------------------------------------

			virtual bool OnNCMiddleButtonDown (const int xScreen, const int yScreen, const Win::Mouse::HitText hitText)
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_NCMBUTTONUP message.
			//-------------------------------------------------------------------------

			virtual bool OnNCMiddleButtonUp  (const int xScreen, const int yScreen, const Win::Mouse::HitText hitText)
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_NCRBUTTONDBLCLK message.
			//-------------------------------------------------------------------------

			virtual bool OnNCRightButtonDoubleClick  (const int xScreen, const int yScreen, const Win::Mouse::HitText hitText)
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_NCRBUTTONDOWN message.
			//-------------------------------------------------------------------------

			virtual bool OnNCRightButtonDown (const int xScreen, const int yScreen, const Win::Mouse::HitText hitText)
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_NCRBUTTONUP message.
			//-------------------------------------------------------------------------

			virtual bool OnNCRightButtonUp  (const int xScreen, const int yScreen, const Win::Mouse::HitText hitText)
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_NCMOUSEMOVE message.
			//-------------------------------------------------------------------------

			virtual bool OnNCMouseMove  (const int xScreen, const int yScreen, const Win::Mouse::HitText hitText)
			{return false ;}

			//---------------------------------------------------------------
			// The 5 following messages concerns the clipboard.
			//---------------------------------------------------------------

			//-------------------------------------------------------------------------
			// Represents the WM_CHANGECBCHAIN message
			//
			// Parameters: 
			//
			// Win::dow::Handle removedWnd -> The handle of the window that is removed of the
			//						  clipboard chain.
			// Win::dow::Handle nextWnd    -> The handle of the next window of the clipboard 
			//						  chain.
			//-------------------------------------------------------------------------

			virtual bool OnChangeCBChain (Win::dow::Handle & removedWnd, Win::dow::Handle & nextWnd) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_DESTROYCLIPBOARD message.
			//-------------------------------------------------------------------------

			virtual bool OnDestroyClipboard () throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_DRAWCLIPBOARD message.
			//-------------------------------------------------------------------------

			virtual bool OnDrawClipboard () throw () 
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_RENDERALLFORMATS message.
			//-------------------------------------------------------------------------

			virtual bool OnRenderAllFormats () throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_RENDERFORMAT message.
			//-------------------------------------------------------------------------

			virtual bool OnRenderFormat (unsigned int clipboardFormat) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_CHILDACTIVATE message.
			//-------------------------------------------------------------------------

			virtual bool OnChildActivate () throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_COMMAND message for menus and keyboard accelerators.
			//
			// Parameters:
			//
			// const int id             -> Id of the menu or accelerator that caused 
			//							   the message.
			// const bool isAccelerator -> True if the message was caused by an 
			//                             accelerator, else false.
			//-------------------------------------------------------------------------

			virtual bool OnCommand (const int id, const bool isAccelerator) throw ()
			{return false;}

			//-------------------------------------------------------------------------
			// Represents the WM_SYSCOMMAND message.
			//
			// Parameters:
			//
			// const int id      -> Type of command.
			// const int xScreen -> X coordinate of the cursor in screen coordinate.
			// const int yScreen -> Y coordinate of the cursor in screen coordinate.
			//-------------------------------------------------------------------------

			virtual bool OnSysCommand (const unsigned int id, const int xScreen, const int yScreen) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_COMMAND message for controls.
			//
			// Parameters:
			//
			// Win::dow::Handle control           -> Handle of the control.

			// const int id               -> Id of the menu or accelerator that caused 
			//							     the message.
			// const int notificationCode -> Notification code of the control.
			//-------------------------------------------------------------------------

			virtual bool OnControl (Win::dow::Handle & control, const int id, const int notificationCode) throw ();

			virtual bool OnNotify (const int idCtrl, LPARAM lParam)
			{return false ;}

			virtual bool OnScrollBarColor(Win::dow::Handle _scrollHandle, Win::ControlColor & ctrColor) throw ()
			{return false ;}

			virtual bool OnStaticColor(Win::dow::Handle _staticHandle, Win::ControlColor & ctrColor) throw ()
			{return false ;}

			virtual bool OnButtonColor(Win::dow::Handle _buttonHandle, Win::ControlColor & ctrColor) throw ()
			{return false ;}

			virtual bool OnDlgColor(Win::dow::Handle _DlgHandle, Win::ControlColor & ctrColor) throw ()
			{return false ;}

			virtual bool OnEditColor(Win::dow::Handle _editHandle, Win::ControlColor & ctrColor) throw ()
			{return false ;}

			virtual bool OnListBoxColor(Win::dow::Handle _listBoxHandle, Win::ControlColor & ctrColor) throw ()
			{return false ;}

			//-------------------------------------------------------------------------
			// Represents the WM_USER message.
			//
			// Parameters:
			//
			// UINT msg -> Numerical value of the user define message.
			// WPARAM wParam -> wParam of the user message.
			// LPARAM lParam -> lParam of the user message.
			// LRESULT & result -> Value to be returned by the predifine window 
			//                     procedure (only if OnUserMessage return true).
			//-------------------------------------------------------------------------

			virtual bool OnUserMessage (UINT msg, WPARAM wParam, LPARAM lParam, LRESULT & result) throw ()
			{ return false; }

			//--------------------------------------------------------------
			// Constructor.  Set the pointer on the message pump to 0 (NULL)
			//--------------------------------------------------------------

			BaseController ()
				: _pump (NULL)
			{}

		protected:
			Win::MessagePump * _pump ;      //Pointer on the "message loop".
			std::map <HWND, ControlEventHandler *> _ctrlMap; // A map containing all the child controls so user feedback (example button click) can be handled
		} ;

		//----------------------------------------------------------------------
		// Win::Controller is a controller for normal windows.
		//----------------------------------------------------------------------

		namespace dow
		{
			class Controller : public Win::BaseController
			{
				
			//Friend with the predefined window procedure.
			friend LRESULT CALLBACK Win::Proc ( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) ;

			public: 

				Controller ()
					: BaseController (),
					  _myWindow (NULL)
				{}

				virtual ~Controller () 
				{}

			protected:

				//-------------------------------------------------------------
				// A Win::Controller object has an handle of the window that's
				// own him.  The predefined window procedure uses this method
				//  to initialize the handle.
				///
				// Parameters:
				//
				// const HWND hwnd -> Handle of the window.
				//-------------------------------------------------------------

				void SetWindowHandle (const HWND hwnd) 
				{
					_myWindow.Init (hwnd) ;
				}

			protected:
				Win::dow::Handle _myWindow ;  // Handle of the window that own the Win::Controller object.
				
			} ;
		}

		namespace Frame
		{

			//----------------------------------------------------------------------
			// Win::FrameController is a controller for frame windows in MDI 
			// application.
			//----------------------------------------------------------------------
			class Controller : public Win::BaseController
			{
			//Friend with the predefined window procedure.
			friend LRESULT CALLBACK Win::FrameProc ( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) ;

			public: 

				Controller ()
					: BaseController (),
					  _myFrame (NULL),
					  _myClient (NULL)
				{}

				virtual ~Controller () 
				{}

			protected:

				//-------------------------------------------------------------
				// A Win::FrameController object has an handle of the window that's
				// own him.  The predefined window procedure uses this method
				//  to initialize the handle.
				//
				// Parameters:
				//
				// const HWND hwnd -> Handle of the window.
				//-------------------------------------------------------------

				void SetFrameHandle (const HWND hwnd) 
				{
					_myFrame.Init (hwnd) ;
				}

				//-------------------------------------------------------------
				// A Win::FrameController object has an handle of the client
				// window used by the frame.  This method is use to innitialize
				// that handle.
				//
				// Parameters:
				//
				// const HWND hwnd -> Handle of the window.
				//-------------------------------------------------------------

				void SetClientHandle (const HWND hwnd)
				{
					_myClient.Init (hwnd) ;
				}

			protected:
				Win::Frame::Handle  _myFrame ;  // Handle of the window that own the Win::Controller object.
				Win::Client::Handle _myClient ;

			} ;
		}


		namespace MDIChild
		{
		//----------------------------------------------------------------------
		// Win::MDIChildController is a controller for MDI child windows in MDI 
		// application.
		//----------------------------------------------------------------------

			class Controller : public Win::BaseController
			{
			//Friend with the predefined window procedure.
			friend LRESULT CALLBACK Win::MDIChildProc ( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) ;

			public: 

				Controller ()
					: BaseController (),
					  _myMDIChild (NULL)
				{}

				virtual ~Controller () 
				{}

				virtual bool OnMDIActivated (Win::MDIChild::Handle & desactivated, Win::MDIChild::Handle & activated) throw ()
				{return false ;}

			protected:

				//-------------------------------------------------------------
				// A Win::FrameController object has an handle of the window that's
				// own him.  The predefined window procedure uses this method
				//  to initialize the handle.
				//
				// Parameters:
				//
				// const HWND hwnd -> Handle of the window.
				//-------------------------------------------------------------

				void SetMDIChildHandle (const HWND hwnd) 
				{
					_myMDIChild.Init (hwnd) ;
				}

			protected:
				Win::MDIChild::Handle  _myMDIChild ;  // Handle of the window that own the Win::Controller object.

			} ;
		}

		//----------------------------------------------------------------------
		// Window subclassing is supported by Win::SubController.  There is a
		// special window procedure predefined for window subclassing.  It is
		// accessed through a Win::SubController object.  Win::SubController
		// is used in a way similar to Win::Controller.
		//----------------------------------------------------------------------

		class SubController: public Win::dow::Controller
		{
		public:

			//--------------------------------------------------------------------
			// Constructor.  Simply set the data members to 0.
			//--------------------------------------------------------------------

			SubController () 
				: _prevProc (NULL), 
				  _prevController (NULL) 
			{}

			//--------------------------------------------------------------------
			// Use this to initialize the data members of a Win::SubController
			// object.
			//
			// Parameters:
			//
			// const HWND hwnd            -> Handle of the window that will own the
			//					             Win::SubController.
			// ProcPtr prevProc           -> Previous window procedure of the 
			//								 window.
			// Win::Controller * prevCtrl -> Pointer on the previous controller
			//								 of the window.
			//--------------------------------------------------------------------

			void Init (const HWND hwnd, ProcPtr prevProc, Win::BaseController * prevCtrl)
			{
				SetWindowHandle (hwnd) ;
				_prevProc = prevProc ;
				_prevController.Init (prevCtrl) ;
			}

			//--------------------------------------------------------------------
			// Call the previous window procedure.
			//
			// Return value : The value returned by the window procedure.
			//
			// Parameters:
			//
			// UINT message  -> Id of the message that was received.
			// WPARAM wParam -> wParam of the message.
			// LPARAM lParam -> lParam of the message.
			//--------------------------------------------------------------------

			LRESULT CallPrevProc (UINT message, WPARAM wParam, LPARAM lParam)
			{
				return ::CallWindowProc (_prevProc, _myWindow, message, wParam, lParam) ;
			}

			//--------------------------------------------------------------------
			// Obtains the pointer on the previous window procedure.
			//
			// Return value : Pointer on the previous window procedure
			//--------------------------------------------------------------------

			ProcPtr GetPrevProc () const
			{
				return _prevProc ;
			}

			//--------------------------------------------------------------------
			// Obtains the pointer on the previous controller.
			//
			// Return value : Pointer on the previous controller
			//--------------------------------------------------------------------

			Win::BaseController * GetPrevController () const
			{
				return _prevController.Get ();
			}

			virtual bool OnNonClientDestroy () throw ()
			{
				/*Win::SetLong<ProcPtr> (_myWindow,GetPrevProc (), GWL_WNDPROC);
				Win::SetLong<Win::BaseController *> (_myWindow, GetPrevController ());
				_prevController = 0;*/
				return false ;
			}

		protected:
			ProcPtr      _prevProc ; // Pointer on the previous window procedure.
			StrongPointer <Win::BaseController> _prevController ;  // Pointer on the previous controller.
		} ;
	}

#endif