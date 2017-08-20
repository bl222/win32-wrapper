//-------------------------------------------------------------------------
// This file contain a class that encapsulate a windows handle (HWND)
//-------------------------------------------------------------------------

#if !defined (WIN_H)

	#define WIN_H
	#include "useunicode.h"
	#include "winunicodehelper.h"
	#include "windrawingtool.h"
	#include "winencapsulation.h"
	#include "winmenu.h"
	#include "winhandle.h"
	
	namespace Win
	{
		
		class SubController ;
		
		//-------------------------------------------------------------------------
		// Replacement for the GetWindowLong function.  Same purpose, easier to use
		// 
		// Return value:  The requested long value.
		//
		// Parameters:
		//
		// const HWND hwnd -> Handle of the window from which you want to get 
		//					  a long value.
		// const int which -> Indicate which long value the function must return.
		//
		//-------------------------------------------------------------------------

		template <class T>
		inline T GetLong (const HWND hwnd, const int which = GWL_USERDATA)
		{
			return reinterpret_cast <T> ( ::GetWindowLong (hwnd, which) ) ;
		}

		//-------------------------------------------------------------------------
		// Replacement for the SetWindowLong function.  Same purpose, easier to use
		//
		// Parameters:
		//
		// const HWND hwnd -> Handle of the window to which you want to assign 
		//					  a long value.
		// const T value   -> The value that will be set.
		// const int which -> Indicate which long value the function must set.
		//
		//-------------------------------------------------------------------------

		template <class T>
		inline void SetLong (const HWND hwnd, const T value, const int which = GWL_USERDATA)
		{
			::SetWindowLong (hwnd, which, reinterpret_cast <long> (value)) ;
		}

		namespace dow
		{
			enum Scrolling  {Erase = SW_ERASE, Invalidate = SW_INVALIDATE, ScrollChildren = SW_SCROLLCHILDREN};
		}
		class Base : public Sys::Handle <HWND>
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Set the window handle.
			//
			// Parameters:
			//
			// const HWND hwnd -> Used to initialize the window handle encapsulated by 
			//					  the Win::dow::Handle::Handle object.
			//-------------------------------------------------------------------------

			Base (const HWND hwnd = NULL)
				:  Sys::Handle <HWND> (hwnd)
			{} 

			virtual ~Base ()
			{}



			//-------------------------------------------------------------------------
			// Return the instance of the program.
			//
			// Return value:  The instance of the program.
			//-------------------------------------------------------------------------

			HINSTANCE GetInstance () const
			{
				
				return reinterpret_cast <HINSTANCE> (::GetWindowLong (_h, GWL_HINSTANCE)) ;
			}

			//-------------------------------------------------------------------------
			// Replacement for the GetWindowLong function.  Same purpose, easier to use
			// 
			// Return value:  The requested long value.
			//
			// Parameters:
			//
			// const int which -> Indicate which long value the function must return.
			//-------------------------------------------------------------------------

			template <class T>
			inline T GetLong  (const int which = GWL_USERDATA) const
			{
				return reinterpret_cast <T> (::GetWindowLong (_h, which)) ;
			}

			//-------------------------------------------------------------------------
			// Replacement for the SetWindowLong function.  Same purpose, easier to use
			//
			// Parameters:
			//
			// const T value   -> The value that will be set.
			// const int which -> Indicate which long value the function must set.
			//-------------------------------------------------------------------------

			template <class T>
			inline void SetLong (const T value, const int which = GWL_USERDATA)
			{
				::SetWindowLong (_h, which, reinterpret_cast <long> T) ;
			}

			//-------------------------------------------------------------------------
			// Send a message to the window represented by the Win::dow::Handle::Handle object.  Do not
			// return until the message has been processed.
			// 
			// Return value:  Depends on which message was sent.
			//
			// Parameters:
			//
			// const UINT msg      -> The id of the message.
			// const WPARAM wParam -> The first parameter of the message.
			// const LPARAM lParam -> The second parameter of the message.
			//-------------------------------------------------------------------------

			LRESULT SendMessage (const UINT msg, const WPARAM wParam = 0, const LPARAM lParam = 0) const
			{
				return ::SendMessage (_h, msg, wParam, lParam) ;
			}

			//-------------------------------------------------------------------------
			// Send a message to the window represented by the Win::dow::Handle::Handle object. 
			// Return immediately.
			// 
			// Parameters:
			//
			// const UINT msg      -> The id of the message.
			// const WPARAM wParam -> The first parameter of the message.
			// const LPARAM lParam -> The second parameter of the message.
			//-------------------------------------------------------------------------

			void PostMessage (const UINT msg, const WPARAM wparam = 0, const LPARAM lparam = 0) const
			{
				if (::PostMessage (_h, msg, wparam, lparam) == FALSE)
					throw Win::Exception (TEXT ("Error, could not post a message")) ;
			}

			//---------------------------------------------------------
			// Destroy the window represented by the Win::dow::Handle::Handle object.
			//---------------------------------------------------------

			void Destroy ()
			{
				if (::DestroyWindow (_h) == 0)
					throw Win::Exception (TEXT("Error, could not destroy a window.")) ;
			}

			//---------------------------------------------------------
			// Give the input focus to the window represented by the 
			// Win::dow::Handle::Handle object.
			//---------------------------------------------------------
			void SetFocus () const
			{ 
				if (::SetFocus (_h) == 0)
					throw Win::Exception (TEXT("Error, could not set the focus")) ;
			}

			//---------------------------------------------------------
			// Determine if the window represented by the 
			// Win::dow::Handle::Handle object has the input focus.
			//
			// Return value:  true if the window has focus, else false.
			//---------------------------------------------------------

			bool HasFocus () const
			{
				return ::GetFocus () == _h ;
			}

			//-----------------------------------
			// Capture the mouse.
			//-----------------------------------

			void CaptureMouse () const
			{
				::SetCapture (_h) ;
			}



			//-----------------------------------
			// Release the mouse.
			//-----------------------------------

			void ReleaseMouse () const
			{
				if (HasCapture ())
					if (::ReleaseCapture () == 0)
						throw Win::Exception (TEXT ("Error, could not release the mouse")) ;
			}

			//----------------------------------------------------------
			// Determine if the window represented by the 
			// Win::dow::Handle::Handle object has captured the mouse.
			//
			// Return value:  true if the window has captured the mouse,
			// else false.
			//----------------------------------------------------------

			bool HasCapture () const
			{
				return ::GetCapture () == _h ;
			}

			//-------------------------------------------------------------------------
			// Set the caption of the window represented by the Win::dow::Handle::Handle object.
			// 
			// Parameters:
			//
			// const std::tstring str -> The text of the caption.
			//-------------------------------------------------------------------------

			void SetText (const std::tstring str) const
			{ 
				SendMessage (WM_SETTEXT, 0, reinterpret_cast <LPARAM> (str.c_str())) ;
			}

			//-------------------------------------------------------------------------
			// Get the caption of the window represented by the Win::dow::Handle::Handle object.
			// 
			// Return value:  The number of character successfully copied.
			//
			// Parameters:
			//
			// TCHAR * buf   -> The text of the caption will be copied in this buffer.
			// const int len -> Number of characters buf can contain, includes null.
			//-------------------------------------------------------------------------

			LRESULT GetText (const TCHAR * buf, const int len) const
			{ 
				return SendMessage (WM_GETTEXT, static_cast <WPARAM> (len), reinterpret_cast <LPARAM> (buf)) ;

			}

			std::tstring GetText () const ; // Get the caption of the window.
			
			//-------------------------------------------------------------------------
			// Get the length of the caption of the window represented by the 
			// Win::dow::Handle::Handle object.
			// 
			// Return value:  The number of character of the caption.
			//-------------------------------------------------------------------------

			LRESULT GetTextLenght () const
			{
				 return SendMessage (WM_GETTEXTLENGTH) ;
			}

			void SetBrush (Win::Brush::Solid::StrongHandle brush) 
			{
				
				::DeleteObject (reinterpret_cast<HBRUSH> (::SetClassLong (_h, GCL_HBRBACKGROUND, reinterpret_cast <DWORD> (static_cast <HBRUSH> ((brush)))))) ;
			}

			//-------------------------------------------------------------------------
			// Set the font the window represented by the Win::dow::Handle::Handle object must use to
			// display its caption.
			// 
			// Parameters:
			//
			// const HFONT hFont -> Handle of the font.
			//-------------------------------------------------------------------------

			void SetFont (const Win::Font::Handle hFont)
			{
				BOOL fRedraw = TRUE ;
				SendMessage (WM_SETFONT, reinterpret_cast <WPARAM> (static_cast <HFONT> (hFont)), MAKELPARAM (fRedraw, 0)) ;
			}

			//-------------------------------------------------------------------------
			// Can Show, hide, maximize, minimize, etc. the window represented by the 
			// Win::dow::Handle::Handle object.
			// 
			// Parameters:
			//
			// const HFONT cmdShwo -> The action to be accomplish (show, hide, etc).
			//-------------------------------------------------------------------------

			void Show (int cmdShow = SW_SHOW) const
			{
				::ShowWindow (_h, cmdShow) ;
			}

			//---------------------------------------------------------
			// Hide the window represented by the Win::dow::Handle::Handle object.
			//---------------------------------------------------------

			void Hide () const
			{
				::ShowWindow (_h, SW_HIDE) ;
			}

			//---------------------------------------------------------
			// Update the window represented by the Win::dow::Handle::Handle object by 
			// indirectly sending a WM_PAINT message.
			//---------------------------------------------------------

			void Update () const
			{
				if (::UpdateWindow (_h) == 0)
					throw Win::Exception (TEXT("Error, could not update a window")) ;
			}

			//---------------------------------------------------------
			// Enable the window represented by the Win::dow::Handle::Handle object.
			//---------------------------------------------------------

			void Enable () const
			{
				::EnableWindow (_h, TRUE) ;
			}

			//---------------------------------------------------------
			// Disable the window represented by the Win::dow::Handle::Handle object.
			//---------------------------------------------------------

			void Disable () const 
			{
				::EnableWindow (_h, FALSE) ;
			}

			//-------------------------------------------------------------------------
			// Move and resize the window represented by the Win::dow::Handle::Handle object.
			//
			// Parameters:
			//
			// const int x      -> New x coordinate of the window.
			// const int y      -> New y coordinate of the window.
			// const int width  -> New width coordinate of the window.
			// const int height -> New height coordinate of the window.
			//-------------------------------------------------------------------------

			void Move (const int x, const int y, const int width, const int height) const 
			{
				if (::MoveWindow (_h, x, y, width, height, TRUE) == 0)
					throw Win::Exception (TEXT("Error, could not move a window")) ;
			}

			//-------------------------------------------------------------------------
			// Scroll the content of the client area of the window represented by the 
			// Win::dow::Handle::Handle object.
			//
			// Return value:  A code indicating if the method succeeded or not.
			//
			// Parameters:
			//
			// const int x                   -> Amount in device unit of horizontal 
			//									scrolling. (Negative value to scroll left.)
			// const int y                   -> Amount in device unit of vertical 
			//                                  scrolling. (Negative value to scroll up.)
			// const Rect * const scrollRect -> Specify the area of the client area that
			//									will be scrolled (Null for entire client area)
			// const Rect * const clipRect   -> Coordinate of the clipping rectangle.
			// const HRGN rgnUpdate          -> This handle will hold the modified 
			//                                  region. (can be NULL)
			// Rect * updateRect             -> Will contain the coordinates of the
			//									invalidated rectangle.
			// const UINT flags              -> Used to specify various options.
			//-------------------------------------------------------------------------

			void Scroll (const int x, const int y, const Rect * const scrollRect = NULL, const Rect * const clipRect = NULL, const Win::Region::Handle rgnUpdate = NULL, Rect * updateRect = NULL, const UINT flags = SW_INVALIDATE | SW_ERASE) const
			{
				if ( ::ScrollWindowEx (_h, x, y, reinterpret_cast <CONST RECT *> (scrollRect),
					reinterpret_cast <CONST RECT *> (clipRect), rgnUpdate, 
					reinterpret_cast <LPRECT> (updateRect), flags) == ERROR)
						throw Win::Exception (TEXT("Error, could not scroll a window")) ;
			}

			//-------------------------------------------------------------------------
			// Get the coordinates the of client area of the window represented by the 
			// Win::dow::Handle::Handle object.
			//
			// Parameters:
			//
			// Rect & rect -> Will contain the coordinates of the client area.
			//-------------------------------------------------------------------------

			void GetClientRect (Win::Rect & rect)  const
			{
				if (::GetClientRect (_h, reinterpret_cast <LPRECT> (&rect) ) == 0)
					throw Win::Exception (TEXT("Error, could not get the client rectangle")) ;
			}

			//-------------------------------------------------------------------------
			// Get the coordinates the window represented by the Win::dow::Handle::Handle object.
			//
			// Parameters:
			//
			// Rect & rect -> Will contain the coordinates of the window.
			//-------------------------------------------------------------------------

			void GetWindowRect (Win::Rect & rect) const
			{
				if (::GetWindowRect (_h, reinterpret_cast <LPRECT> (&rect) ) == 0)
					throw Win::Exception (TEXT("Error, could not get the window rectangle")) ;
			}

			//-------------------------------------------------------------------------
			// Convert a client coordinate point to a screen coordinate point.
			//
			// Parameters:
			//
			// Point & p -> The point to be converted.
			//-------------------------------------------------------------------------

			void ClientToScreen (Win::Point & p) const
			{
				if (::ClientToScreen (_h, reinterpret_cast <LPPOINT> (&p) ) == 0)
					throw Win::Exception (TEXT("Error, could not convert from client to screen")) ;
			}

			//-------------------------------------------------------------------------
			// Convert a screen coordinate point to a client coordinate point.
			//
			// Parameters:
			//
			// Point & p -> The point to be converted.
			//-------------------------------------------------------------------------

			void ScreenToClient (Win::Point & p) const
			{
				if (::ScreenToClient (_h, reinterpret_cast <LPPOINT> (&p) ) == 0)
					throw Win::Exception (TEXT("Error, could not convert from screen to client")) ;
			}

			//-------------------------------------------------------------------------
			// Invalidate a rectangular area of the client area of the window 
			// represented by the Win::dow::Handle::Handle object.  This indicate that the area must be
			// redrawn.
			//
			// Parameters:
			//
			// Rect * rect -> Coordinate of the area that must be redrawn.
			//                (NULL = whole client area)
			// bool erase  -> true if the background must be erased, else false.
			//-------------------------------------------------------------------------

			void InvalidateRect (const Win::Rect * const rect, bool erase = true) const
			{
				if (::InvalidateRect (_h, reinterpret_cast <CONST RECT *> (rect), erase) == 0)
					throw Win::Exception (TEXT("Error, could invalidate a rectangular area of the client area")) ;
			}

			//-------------------------------------------------------------------------
			// Invalidate an area of the client area of the window represented by the 
			// Win::dow::Handle::Handle object.  This indicate that the area must be redrawn.
			//
			// Parameters:
			//
			// const HRGN rgn    -> Represent the are that must be redrawn 
			//                      (NULL = whole client area)
			// const bool erase  -> true if the background must be erased, else false.
			//-------------------------------------------------------------------------

			void InvalidateRegion (const Win::Region::Handle rgn, const bool erase = true) const
			{
				if (::InvalidateRgn (_h, rgn, erase) == 0)
					throw Win::Exception (TEXT("Error, could invalidate a region area of the client area")) ;
			}

			//-------------------------------------------------------------------------
			// Validate a rectangular area of the client area of the window 
			// represented by the Win::dow::Handle::Handle object.  This removes the rectangle area from
			// the window's update region.
			//
			// Parameters:
			//
			// Rect * rect -> Coordinate of the area that must be validated.
			//                (NULL = whole client area)
			//-------------------------------------------------------------------------

			void ValidateRect (const Win::Rect * const rect) const
			{
				if (::ValidateRect(_h, reinterpret_cast <CONST RECT *> (rect)) == 0)
					throw Win::Exception (TEXT("Error, could validate a rectangular area of the client area")) ;
			}

			//-------------------------------------------------------------------------
			// Validate an area of the client area of the window 
			// represented by the Win::dow::Handle::Handle object.  This removes the area from
			// the window's update region.
			//
			// Parameters:
			//
			// const HRGN rgn -> Represent of the area that must be validated.
			//                   (NULL = whole client area)
			//-------------------------------------------------------------------------

			void ValidateRegion (const Win::Region::Handle rgn) const
			{
				if (::ValidateRgn (_h, rgn) == 0)
					throw Win::Exception (TEXT("Error, could validate a rerion of the client area")) ;
			}

			//-------------------------------------------------------------------------
			// Get the coordinates of the smallest rectangle containing the update 
			// region of window represented by the Win::dow::Handle::Handle object.  This removes 
			// the area from the window's update region.
			//
			// Parameters:
			//
			// Rect & rect       -> This object will contain the coordinate of the 
			//                      rectangle.
			// const bool erase  -> true if the background must be erased, else false.
			//-------------------------------------------------------------------------

			void GetUpdateRect (Win::Rect & rect, const bool erase = false) const
			{
				if (::GetUpdateRect (_h, reinterpret_cast <PRECT> (&rect), erase) == 0)
					throw Win::Exception (TEXT("Error, could not get the update rectangle")) ;
			}

			//----------------------------------------------------------------
			// Determine whether the window represented by the Win::dow::Handle::Handle object
			// is native Unicode.
			//
			// Return value:  True if the window is native Unicode, else false.
			//----------------------------------------------------------------

			bool IsUnicode () const
			{
				return ::IsWindowUnicode (_h) == TRUE ;
			}

			//These methods allow window subclassing.
			void SubClass   (StrongPointer <SubController> & subCtrl) ;
			void UnSubClass () ;

			//-------------------------------------------------------------------------
			// Get a "Weak handle" of the menu bar of the window represented by the 
			// Win::dow::Handle::Handle object.  This allow to modify the menu bar without removing
			// it from the window.
			//
			// Return value:  The "weak handle" of the menu bar.
			//-------------------------------------------------------------------------	

			Menu::Bar::Handle GetWeakMenuBar () const
			{
				return ::GetMenu (_h) ;
			}

			Menu::Bar::StrongHandle RemoveMenuBar () const;

			//-------------------------------------------------------------------------
			// Give a menu bar to the window represented by the Win::dow::Handle::Handle object.
			//
			// Parameters:
			//
			// Menu::Bar & menu -> The menu bar that will be attach to the window.
			//                     Afterward this object contain an invalid handle.
			//-------------------------------------------------------------------------

			void AttachMenuBar (Win::Menu::Bar::StrongHandle  menu) const
			{
				::SetMenu (_h, menu.Release ()) ;
			}

			//-------------------------------------------------------------------------
			// Update the menu bar of the window represented by the Win::dow::Handle::Handle object.
			//-------------------------------------------------------------------------

    		void RefreshMenuBar () const
    		{
				if (::DrawMenuBar(_h) == 0)
					throw Win::Exception (TEXT("Error, could not draw the menu bar")) ;
    		}

			void CheckRadioButton (const int idFirst, const int idLast, const int idCheck) const
			{
				if (::CheckRadioButton (_h, idFirst, idLast, idCheck) == 0)
					throw Win::Exception (TEXT("Error, could not check the radio button")) ;
			}

		} ;
			
		//-------------------------------------------------------------------------
		// Win::dow::Handle::Handle encapsulates a window handle.  Represent a window.
		//-------------------------------------------------------------------------

		namespace dow
		{
			class Handle : public Win::Base
			{
			public:

				Handle (const HWND hwnd = NULL)
					: Win::Base (hwnd)
				{} 

				//-------------------------------------------------------------------------
				// Return the parent of the window represented by the Win::dow::Handle::Handle object.
				//
				// Return value:  A Win::dow::Handle::Handle object encapsulating the handle of the parent
				//-------------------------------------------------------------------------

				Win::dow::Handle GetParent () 
				{ 
					return ::GetParent (_h) ; 
				}

				Win::dow::Handle GetChild (const int id) 
				{
					return ::GetDlgItem (_h, id) ;
				}
			} ;
		}

		namespace Frame
		{
			class Handle : public Base
			{
			public:

				Handle (const HWND hwnd = NULL)
					: Base (hwnd)
				{} 

				//-------------------------------------------------------------------------
				// Return the parent of the window represented by the Win::dow::Handle::Handle object.
				//
				// Return value:  A Win::dow::Handle::Handle object encapsulating the handle of the parent
				//-------------------------------------------------------------------------

				Win::dow::Handle GetParent () 
				{ 
					return ::GetParent (_h) ; 
				}
			} ;
		}


		namespace Client
		{
			class Handle ;
		}

		namespace MDIChild
		{
			class Handle : public Win::Base
			{
			public:

				Handle (const HWND hwnd = NULL)
					: Base (hwnd)
				{} 

				Win::Client::Handle GetParent () ;

			} ;
		}

		namespace Client
		{
			class Handle : public Base
			{
			public:

				//-------------------------------------------------------------------------
				// Return the parent of the window represented by the Win::dow::Handle::Handle object.
				//
				// Return value:  A Win::Frame object encapsulating the handle of the parent
				//-------------------------------------------------------------------------

				Win::Frame::Handle GetParent () 
				{ 
					return ::GetParent (_h) ; 
				}

				Handle (const HWND hwnd = NULL)
					: Base (hwnd)
				{} 

				//-------------------------------------------------------------------------
				// Activate one of the MDI child window.
				//
				// Parameters:
				//
				// const HWND hwnd -> Child to be activated.
				//-------------------------------------------------------------------------

				void ActivateMDIChild (const Win::MDIChild::Handle hwnd) const
				{
					::SendMessage (_h, WM_MDIACTIVATE, reinterpret_cast <WPARAM> (static_cast <HWND> (hwnd)), 0) ;
				}

				//-------------------------------------------------------------------------
				// Cascades the MDI child windows.
				//
				// Parameters:
				//
				// const bool cascadeDisabledChild -> True to cascade the disabled child 
				//									  too, else false.
				//-------------------------------------------------------------------------

				void Cascade (const bool cascadeDisabledChild = false) const
				{
					if (::SendMessage (_h, WM_MDICASCADE, 
						cascadeDisabledChild ? MDITILE_SKIPDISABLED : 0, 0) == 0)
							throw Win::Exception (TEXT("Error, could not cascade the MDI windows")) ;
				}

				//-------------------------------------------------------------------------
				// Tiles the MDI child windows.
				//
				// Parameters:
				//
				// const int flag -> Indicates how the windows will be tiled.
				//-------------------------------------------------------------------------

				void Tile (const int flag) const
				{
					if (::SendMessage (_h, WM_MDITILE, flag, 0) == 0)
						throw Win::Exception (TEXT("Error, could not tile the MDI windows")) ;
				}

				// CreateMDIChild () ;

				//-------------------------------------------------------------------------
				// Destroys one of the MDI child window.
				//
				// Parameters:
				//
				// const HWND hwnd -> Child to be destroyed.
				//-------------------------------------------------------------------------

				void DestroyMDIChild (const Win::MDIChild::Handle  hwnd) const
				{
					::SendMessage (_h, WM_MDIDESTROY, reinterpret_cast <WPARAM> (static_cast <HWND> (hwnd)), 0) ;
				}

				//-------------------------------------------------------------------------
				// Obtains the active MDI child window.
				//
				// Parameters:
				//
				// bool * isMaximized -> Will be true if the child is maximized, else false.
				//-------------------------------------------------------------------------

				Win::MDIChild::Handle GetActiveMDIChild (bool * isMaximized = 0) const
				{
					return reinterpret_cast <HWND>(::SendMessage (_h, WM_MDIGETACTIVE, reinterpret_cast <WPARAM> (isMaximized), 0)) ;
				}

				//-------------------------------------------------------------------------
				// Aranges the icons of the minimized MDI child window.
				//-------------------------------------------------------------------------

				void ArrangeIcon () const
				{
					::SendMessage (_h, WM_MDIDESTROY, 0, 0) ;
				}

				//-------------------------------------------------------------------------
				// Maximized one of the MDI child window.
				//
				// Parameters:
				//
				// const HWND hwnd -> Child to be maximized.
				//-------------------------------------------------------------------------

				void MaximizeMDIChild (const Win::MDIChild::Handle  hwnd) const
				{
					::SendMessage (_h, WM_MDIMAXIMIZE, reinterpret_cast <WPARAM> (static_cast <HWND> (hwnd)), 0) ;
				}

				//-------------------------------------------------------------------------
				// Activate the MDI child window next to the specified child.
				//
				// Parameters:
				//
				// const HWND hwnd -> The child next to this one is activated.
				//-------------------------------------------------------------------------

				void ActivateNext (const Win::MDIChild::Handle  hwnd = NULL) const
				{
					::SendMessage (_h, WM_MDINEXT, reinterpret_cast <WPARAM> (static_cast <HWND> (hwnd)), 0) ;

				}

				//-------------------------------------------------------------------------
				// Activate the MDI child window before to the specified child.
				//
				// Parameters:
				//
				// const HWND hwnd -> The child before this one is activated.
				//-------------------------------------------------------------------------

				void ActivatePrevious (const Win::MDIChild::Handle  hwnd = NULL) const
				{
					::SendMessage (_h, WM_MDINEXT, reinterpret_cast <WPARAM> (static_cast <HWND> (hwnd)), 1) ;
				}

				//-------------------------------------------------------------------------
				// Refresh the menu of the frame window.
				//
				// Return value:  True if the method succeed, else false.
				//-------------------------------------------------------------------------

				void RefreshMenu () const
				{
					if (::SendMessage (_h, WM_MDIREFRESHMENU, 0, 0) == 0)
						throw Win::Exception (TEXT("Error, could not refresh the menu")) ;
				}

				//-------------------------------------------------------------------------
				// Restores one of the MDI child window.
				//
				// Parameters:
				//
				// const HWND hwnd -> Child to be restored.
				//-------------------------------------------------------------------------

				void RestoreMDIChild (const Win::MDIChild::Handle  hwnd) const
				{
					::SendMessage (_h, WM_MDIRESTORE, reinterpret_cast <WPARAM> (static_cast <HWND> (hwnd)), 0) ;
				}

				//-------------------------------------------------------------------------
				// Sets a new menu to the frame window.
				//
				// Return value:  The old menu.
				//
				// Parameters:
				//
				// const Win::Menu::Bar & menu -> The new menu.
				// const HMENU winMenu         -> The window popup menu of the new menu
				//-------------------------------------------------------------------------

				Win::Menu::Bar::StrongHandle SetFrameMenu (Win::Menu::Bar::StrongHandle  menu, const Win::Menu::PopUp::Handle winMenu) const
				{

					return Win::Menu::Bar::StrongHandle (reinterpret_cast <HMENU> (::SendMessage (_h, WM_MDISETMENU, 
																reinterpret_cast <WPARAM> (static_cast <HMENU> (menu.Release ())),
																reinterpret_cast <LPARAM> (static_cast <HMENU> (winMenu))))) ;

					
				}

			} ;
		}

		BOOL CALLBACK ChildEnumProc (HWND hwnd, LPARAM lParam) ;

		//-------------------------------------------------------------------
		// Win::ChildEnumController replaces the child
		// enumeration procedure from traditionnal Windows programming.
		// Simply create a new class inheriting from 
		// Win::ChildEnumController and implement the Enumeration
		// method.
		//-------------------------------------------------------------------

		class ChildEnumController 
		{
				friend int CALLBACK Win::ChildEnumProc (HWND hwnd, LPARAM lParam) ;

			public:
				//-------------------------------------------------------------------
				// Constructor.
				//-------------------------------------------------------------------

				ChildEnumController ()
				{}

				//-------------------------------------------------------------------
				// Destructor.
				//-------------------------------------------------------------------

				virtual ~ChildEnumController ()
				{}

				//-------------------------------------------------------------------
				// This method define the what happens during enumaration of the 
				// childs .
				// 
				// Return value:  False to stop enumaration, else true.
				//
				// Parameters:
				//
				// Win::dow::Handle::Handle & child -> Handle of the current child.
				//-------------------------------------------------------------------

				virtual bool Enumeration (Win::Base  child) throw ()
				{return false ;}
		} ;

		//-------------------------------------------------------------------
		// Win::ChildEnumerator allows to enumerate the childs of a window.
		//-------------------------------------------------------------------

		class ChildEnumerator 
		{
		public:

			//-------------------------------------------------------------------
			// Constructor.
			//
			// const HWND parent = 0 -> Parent window whose children will be 
			//							enumerated
			//-------------------------------------------------------------------

			ChildEnumerator (const Win::Base parent = NULL)
				: _parent (parent)
			{}

			//-------------------------------------------------------------------
			// Indiquates the parent whose children will be enumerated.
			//
			// const HWND parent = 0 -> Parent window whose children will be 
			//							enumerated
			//-------------------------------------------------------------------

			void SetParent (const Win::Base parent = NULL)
			{
				_parent = parent ;
			}

			//-------------------------------------------------------------------
			// Enumerate the childs of the parent.
			//
			// const Win::ChildEnumController & ctrl -> Defines the behavior during
			//											enumeration.
			//-------------------------------------------------------------------

			bool Enumerate (const Win::ChildEnumController & ctrl) const
			{
				return ::EnumChildWindows (_parent, ChildEnumProc, reinterpret_cast <LPARAM> (&ctrl)) != 0 ;
			}

		private:
			HWND   _parent ;
		} ;
	}

#endif