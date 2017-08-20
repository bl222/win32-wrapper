//-----------------------------------------------------------------
//  This file contains classes that allow using tooltip controls.
//-----------------------------------------------------------------

#if !defined (WINTOOLTIP_H)

	#define WINTOOLTIP_H
	#include "useunicode.h"
	#include "wincommoncontrol.h"
	#include "wincontrol.h"

	namespace Win
	{
		//-----------------------------------------------------------------
		//  Used to load the tooltip from the DLL.
		//-----------------------------------------------------------------
		class UsingToolTip : UsingCommonControl
		{
		public:
			UsingToolTip ()
				:  UsingCommonControl (ICC_BAR_CLASSES) 
			{}
		}  ;

		//-------------------------------------------------------------------------
		// Win::ToolTipHandle encapsulates a tooltip control handle.  Represent a tooltip
		// control.  Inherit from Win::SimpleControl for basic functionality.
		//-------------------------------------------------------------------------

		class ToolTipHandle : public SimpleControlHandle
		{
			
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle to represent the tooltip
			// control through it's parent.
			// 
			// Parameters:
			//
			// const HWND parent -> Parent of the static control.
			// const int id      -> Id of the static control.
			//-------------------------------------------------------------------------

			ToolTipHandle (const Win::Base parent, const int id)
				: SimpleControlHandle (parent, id) 
			{}

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle directly
			// 
			// Parameters:
			//
			// const HWND win -> Handle of the static control.
			//-------------------------------------------------------------------------

			ToolTipHandle (const Win::Base win = NULL)
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
			// Activates or desactivates the tooltip control.
			//
			// Parameters:
			//
			// const bool activate -> true to activate, false to desactivate
			//-------------------------------------------------------------------------

			void Activate (const bool activate = true) 
			{
				SendMessage (TTM_ACTIVATE, static_cast <WPARAM> (activate)) ;
			}

			void AddTool (Win::Base win, const UINT id, Win::Rect & rect, std::tstring str, const UINT flag = TTF_CENTERTIP, const LPARAM lParam = 0) ;
			void AddTool (Win::Base win, const UINT id, Win::Rect & rect, const UINT flag = TTF_CENTERTIP, const LPARAM lParam = 0) ;
			void AddTool (HINSTANCE hInstance, Win::Base win, const UINT id, Win::Rect & rect, int stringId, const UINT flag = TTF_CENTERTIP, const LPARAM lParam = 0) ;
			void AddTool (Win::Base win, std::tstring &str, const UINT flag = TTF_CENTERTIP, const LPARAM lParam = 0) ;
			void AddTool (Win::Base win,const UINT flag = TTF_CENTERTIP, const LPARAM lParam = 0) ;
			void AddTool (HINSTANCE hInstance, Win::Base win, int stringId, const UINT flag = TTF_CENTERTIP, const LPARAM lParam = 0) ;
			void DeleteTool (Win::Base win, const UINT id) ;

			//-------------------------------------------------------------------------
			// Obtains info about a tooltip
			//
			// Parameters:
			//
			// TOOLINFO * ti   -> Will contain the info.
			// const int index -> Index of the tooltip.
			//-------------------------------------------------------------------------

			void GetToolInfo (TOOLINFO * ti, const int index)
			{
				if (SendMessage (TTM_ENUMTOOLS, index, reinterpret_cast <LPARAM> (ti)) == FALSE)
					throw Win::Exception (TEXT("Error, could not obtain the information from the desired tool")) ;
			}

			//-------------------------------------------------------------------------
			// Determines if there is a current tool.
			//
			// Return value:  True if the current tool exist, else false.
			//-------------------------------------------------------------------------

			bool CurrentToolExist () 
			{
				return SendMessage (TTM_GETCURRENTTOOL) != 0 ;
			}

			//-------------------------------------------------------------------------
			// Obtains the info about the current tool
			//
			// Parameters:
			//
			// TOOLINFO * ti   -> Will contain the info.
			//-------------------------------------------------------------------------

			void GetCurrentToolInfo (TOOLINFO * ti)
			{
				if (SendMessage (TTM_GETCURRENTTOOL, 0, reinterpret_cast <LPARAM> (ti)) != 0)
					throw Win::Exception (TEXT("Error, could not obtain the information from the current tool")) ;
			}

			//-------------------------------------------------------------------------
			// Get the auto pop delay.
			//-------------------------------------------------------------------------			

			void GetAutoPopDelay () const
			{
				SendMessage (TTM_GETDELAYTIME, TTDT_AUTOPOP) ;
			}

			//-------------------------------------------------------------------------
			// Get the initial delay.
			//-------------------------------------------------------------------------

			void GetInitialDelay () const
			{
				SendMessage (TTM_GETDELAYTIME, TTDT_INITIAL) ;
			}

			//-------------------------------------------------------------------------
			// Get the reshow delay.
			//-------------------------------------------------------------------------

			void GetReshowDelay () const
			{
				SendMessage (TTM_GETDELAYTIME, TTDT_RESHOW) ;
			}

			//-------------------------------------------------------------------------
			// Obtains the margins.
			//
			// Parameters:
			//
			// Win::Rect & rect -> Will contains the margins.
			//-------------------------------------------------------------------------

			void GetMargin (Win::Rect & rect) const
			{
				SendMessage (TTM_GETMARGIN, 0, reinterpret_cast <LPARAM> (&rect)) ;
			}

			//-------------------------------------------------------------------------
			// Obtains the maximum width
			//
			// Return value:  The maximum width.
			//-------------------------------------------------------------------------

			int GetMaxWidth () const
			{
				return SendMessage (TTM_GETMAXTIPWIDTH) ;
			}

			std::tstring GetText (Win::Base win, const int id = 0) const ;

			//-------------------------------------------------------------------------
			// Obtains the background color
			//
			// Return value:  The background color.
			//-------------------------------------------------------------------------

			Win::Color GetBackgroundColor () const 
			{
				return SendMessage (TTM_GETTIPBKCOLOR) ;
			}

			//-------------------------------------------------------------------------
			// Obtains the text color
			//
			// Return value:  The text color
			//-------------------------------------------------------------------------

			Win::Color GetTextColor () const 
			{
				return SendMessage (TTM_GETTIPTEXTCOLOR) ;
			}

			//-------------------------------------------------------------------------
			// Obtains the number of tooltips
			//
			// Return value:  The number of tooltips
			//-------------------------------------------------------------------------

			int GetNbTooltips () const
			{
				return SendMessage (TTM_GETTOOLCOUNT) ;
			}

			//-------------------------------------------------------------------------
			// Gets the tool info
			//
			// Parameters:
			//
			// TOOLINFO & tl -> Will contain the tool info
			//-------------------------------------------------------------------------

			void GetToolInfo (TOOLINFO & tl) const
			{
				tl.cbSize = sizeof (TOOLINFO) ;

				if (SendMessage (TTM_GETTOOLINFO, 0, reinterpret_cast <LPARAM> (&tl)) == FALSE)
					throw Win::Exception (TEXT("Error, could not get the tool info.")) ;
			}

			void HitTest (TTHITTESTINFO & hti)
			{
				if (SendMessage (TTM_HITTEST, 0, reinterpret_cast <LPARAM> (&hti)) == FALSE)
					throw Win::Exception (TEXT("Error, could not perform a hit test")) ;
			}

			void SetBoundingRect (Win::Base win, Win::Rect & rect, const UINT id = 0) ;

			//-------------------------------------------------------------------------
			// Removes a displayed tooltip from view
			//-------------------------------------------------------------------------

			void Pop ()
			{
				SendMessage (TTM_POP) ;
			}

			//-------------------------------------------------------------------------
			// Sets the auto pop delay
			//-------------------------------------------------------------------------

			void SetAutoPopDelay (const int delay) 
			{
				SendMessage (TTM_SETDELAYTIME, TTDT_AUTOPOP, delay) ;
			}

			//-------------------------------------------------------------------------
			// Sets the initial delay
			//-------------------------------------------------------------------------

			void SetInitialDelay (const int delay) 
			{
				SendMessage (TTM_SETDELAYTIME, TTDT_INITIAL, delay) ;
			}

			//-------------------------------------------------------------------------
			// Sets the reshow delay
			//-------------------------------------------------------------------------

			void SetReshowDelay (const int delay) 
			{
				SendMessage (TTM_SETDELAYTIME, TTDT_RESHOW, delay) ;
			}

			//-------------------------------------------------------------------------
			// Sets the margin
			//
			// Parameters:
			//
			// const Win::Rect & rect -> Contains the new margins
			//-------------------------------------------------------------------------

			void SetMargin (const Win::Rect & rect)
			{
				SendMessage (TTM_SETMARGIN, 0, reinterpret_cast <LPARAM> (&rect)) ;
			}

			//-------------------------------------------------------------------------
			// Sets the maximum width
			//
			// Parameters:
			//
			// const int width -> The new width.
			//-------------------------------------------------------------------------

			void SetMaxWidth (const int width)
			{
				SendMessage (TTM_SETMAXTIPWIDTH, 0, width) ;
			}

			//-------------------------------------------------------------------------
			// Sets the background color
			//
			// Parameters:
			//
			// const Win::Color & color -> The new background color.
			//-------------------------------------------------------------------------

			void SetBackgroundColor (const Win::Color & color)
			{
				SendMessage (TTM_SETTIPBKCOLOR, color.GetColorRef ()) ;
			}

			//-------------------------------------------------------------------------
			// Sets the text color
			//
			// Parameters:
			//
			// const Win::Color & color -> The new text color.
			//-------------------------------------------------------------------------

			void SetTextColor (const Win::Color & color)
			{
				SendMessage (TTM_SETTIPTEXTCOLOR, color.GetColorRef ()) ;
			}

			//-------------------------------------------------------------------------
			// Sets the tool info
			//
			// Parameters:
			//
			// TOOLINFO tl -> The new tool info.
			//-------------------------------------------------------------------------

			void SetToolInfo (TOOLINFO tl)
			{
				tl.cbSize = sizeof (TOOLINFO) ;

				SendMessage (TTM_SETTOOLINFO, 0, reinterpret_cast <LPARAM> (&tl)) ;
			}

			void TrackActivate (Win::Base & win, const int id = 0, bool activate = true) ;

			//-------------------------------------------------------------------------
			// changes the position of the tracked window.
			//
			// Parameters:
			//
			// const int x -> The new x coordinate
			// const int y -> The new y coordinate
			//-------------------------------------------------------------------------

			void TrackPosition (const int x, const int y)
			{
				SendMessage (TTM_TRACKPOSITION, 0, MAKELONG (x, y)) ;
			}

			//-------------------------------------------------------------------------
			// Updates the tooltip.
			//-------------------------------------------------------------------------

			void Update () 
			{
				SendMessage (TTM_UPDATE) ;
			}

			//-------------------------------------------------------------------------
			// Updates a particular tooltip
			//
			// Parameters:
			//
			// TOOLINFO tl -> Indicates witch tooltip will be updated
			//-------------------------------------------------------------------------

			void Update (TOOLINFO tl)
			{
				tl.cbSize = sizeof (TOOLINFO) ;

				SendMessage (TTM_UPDATETIPTEXT, 0, reinterpret_cast <LPARAM> (&tl)) ;
			}



			Win::dow::Handle WindowFromPoint (Win::Point & pt)
			{
				if (SendMessage (TTM_WINDOWFROMPOINT, 0, reinterpret_cast <LPARAM> (&pt)) == 0)
					throw Win::Exception (TEXT("Error, no window at that point")) ;
			}
		} ;

		//-------------------------------------------------------------------------
		// Win::TooltipCreator allows to create a static control.
		// Inherit from Win::ControlCreator for basic functionality.
		//-------------------------------------------------------------------------

		class ToolTipCreator : public ControlCreator
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Creates a tooltip control with the functionality of 
			// Win::ControlCreator.
			//-------------------------------------------------------------------------

			ToolTipCreator ()
				: ControlCreator (std::tstring (TOOLTIPS_CLASS), 0, 0)
			{
				_style = WS_POPUP ;
			}


			//-------------------------------------------------------------------------
			// Creates a new tooltip control.
			// 
			// Return value:  The static control handle.
			//
			// Parameters:
			//
			// const std::tstring title -> The title of the tooltip control.
			//-------------------------------------------------------------------------

			Win::ToolTipHandle Create (HINSTANCE hInstance) const
			{
				return CreateWindowEx(0, TOOLTIPS_CLASS, TEXT(""),
                          _style,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          NULL, (HMENU)NULL, hInstance,
                          NULL);

			}

			//-------------------------------------------------------------------------
			// The following methods all serve the same purpose.  They set one of the 
			// style of the future static control.
			//-------------------------------------------------------------------------

			void SetAlwaysTipStyle () {_style |= TTS_ALWAYSTIP ;}
			void SetNoPrefixStyle  () {_style |= TTS_NOPREFIX ;}
		} ;
	}

#endif