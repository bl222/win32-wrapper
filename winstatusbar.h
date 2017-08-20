//-----------------------------------------------------------------
//  This file contains classes that allow using status bar controls.
//-----------------------------------------------------------------

#if !defined (WINSTATUSBAR_H)

	#define WINSTATUSBAR_H
		#include "useunicode.h"
	#include "wincommoncontrol.h"
	#include "wincontrol.h"
	#include "winicon.h"

	namespace Win
	{
		//-----------------------------------------------------------------
		//  Used to load the Status Bar from the DLL.
		//-----------------------------------------------------------------
		class UsingStatusBar : UsingCommonControl
		{
		public:
			UsingStatusBar ()
				:  UsingCommonControl (ICC_BAR_CLASSES) 
			{}
		}  ;

		//-------------------------------------------------------------------------
		// Win::StatusBar encapsulates a status bar control handle.  Represent a status
		// bar control.  Inherit from Win::SimpleControl for basic functionality.
		//-------------------------------------------------------------------------

		class StatusBarHandle : public SimpleControlHandle
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

			StatusBarHandle (const Win::Base parent, const int id)
				: SimpleControlHandle (parent, id) 
			{}

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle directly
			// 
			// Parameters:
			//
			// const HWND win -> Handle of the static control.
			//-------------------------------------------------------------------------

			StatusBarHandle (const Win::Base win = NULL)
				: SimpleControlHandle (win)
			{}

			//-------------------------------------------------------------------------
			// Initialize the handle and the id through the parent handle.
			//-------------------------------------------------------------------------

			void Init (const Win::Base parent, const int id)
			{
				SimpleControlHandle::Init (parent, id) ;
			}

			void GetBordersWitdh (int  & vertWidth, int & horzWidth, int & betweenWidth) const ;
			void SetBordersWitdh (const int vertWidth, const int  horzWidth, const int betweenWidth) const ;

			//-------------------------------------------------------------------------
			// Gets the number of part of the status bar.
			//
			// Return value:  The number of parts.
			//-------------------------------------------------------------------------

			int GetNbParts () const
			{
				return SendMessage (SB_GETPARTS, 0, 0) ;
			}

			//-------------------------------------------------------------------------
			// Obtains the right coordiantes of the various parts of the status bar
			//
			// Parameters:
			//
			// int * array -> Will contains the coordinates
			// int   count -> The size of the array
			//-------------------------------------------------------------------------

			void GetPartsRightCoordinates (int  * array, const long count) const
			{
				if (SendMessage (SB_GETPARTS, count, reinterpret_cast <LPARAM> (array)) == 0)
					throw Win::Exception (TEXT("Error, could not get the right coordiantes of the parts")) ;
			}

			//-------------------------------------------------------------------------
			// Obtains the drawing rectangle of the status bar
			//
			// Parameters:
			//
			// Win::Rect & rect -> Will contain the coordinates of the drawing rectangle
			// const long index -> The index of the desired part
			//-------------------------------------------------------------------------

			void GetRect (Win::Rect & rect, const long index) const
			{
				if (SendMessage (SB_GETRECT, index, reinterpret_cast <WPARAM> (reinterpret_cast <LPRECT> (&rect))) == FALSE)
					throw Win::Exception (TEXT("Error, could not get the rectangle of the status bar")) ;
			}


			Win::Rect GetRect (const long index) const ;

			//-------------------------------------------------------------------------
			// Return the length text of a part on the status bar
			//
			// Return value:  The text length.
			//
			// Parameters:
			//
			// const long index -> Index of the desired part.
			//-------------------------------------------------------------------------

			short GetTextLength (const long index) const
			{
				int l = SendMessage (SB_GETTEXTLENGTH, index) ;

				return LOWORD (l) ;
			}

			std::tstring GetText (const long index) const ;
			std::tstring GetToolTipText (const short index, const short nbChar = 255) const ;

			//-------------------------------------------------------------------------
			// Determines wheter the status bar is using Unicode or ASCII.
			//
			// Return value:  True if the status bar is using Unicode, else false.
			//-------------------------------------------------------------------------

			bool IsUsingUnicode () const
			{
				return SendMessage (SB_GETUNICODEFORMAT) != 0 ;
			}

			//-------------------------------------------------------------------------
			// Determines wheter the status bar is using simple style or not.
			//
			// Return value:  True if the status bar is using simple style, else false.
			//-------------------------------------------------------------------------

			bool IsSimple () const 
			{
				return SendMessage (SB_ISSIMPLE) != 0 ;
			}

			//-------------------------------------------------------------------------
			// Changes the color of the background.
			//
			// Parameters:
			//
			// const Win::Color & color -> The new background color.
			//-------------------------------------------------------------------------

			void SetBkColor (const Win::Color & color) const
			{
				SendMessage (SB_SETBKCOLOR, 0, static_cast <COLORREF> (color.GetColorRef ())) ;
			}

			//-------------------------------------------------------------------------
			// Sets a icon that will be displayed on the push button control.
			//
			// Parameters:
			// 
			// const HICON icon -> Handle of the icon.
			// const long index -> Index of the desired part.
			//-------------------------------------------------------------------------

			void SetIcon (const Win::Icon::Handle icon, const long index) const
			{
				if (SendMessage (SB_SETICON, index, 
					reinterpret_cast <LPARAM> (static_cast <HICON> (icon))) == 0)
					throw Win::Exception (TEXT("Error, could not set a icon in the status bar")) ;
			}

			//-------------------------------------------------------------------------
			// Removes a icon that will be displayed on the push button control.
			//
			// Parameters:
			// 
			// const long index -> Index of the desired part.
			//-------------------------------------------------------------------------

			void SetIcon (const long index) const
			{
				if (SendMessage (SB_SETICON, index, 
					reinterpret_cast <LPARAM> (static_cast <HICON> (0))) == 0)
					throw Win::Exception (TEXT("Error, could not set a icon in the status bar")) ;
			}

			//-------------------------------------------------------------------------
			// Sets the minimum height of the status bar.
			//
			// Parameters:
			// 
			// const long index -> Index of the desired part.
			//-------------------------------------------------------------------------

			void SetMinHeight (const long height) const
			{
				SendMessage (SB_SETMINHEIGHT, height) ;
				SendMessage (WM_SIZE) ; // Redraw the window
			}

			//-------------------------------------------------------------------------
			// Sets the of a part of the status bar.
			//
			// Parameters:
			// 
			// int * array  -> Constain the coordinates of the parts
			// BYTE nbParts -> The number of parts (length of the array);
			//-------------------------------------------------------------------------

			void SetParts (int * array, const BYTE nbParts) const
			{
				if (SendMessage (SB_SETPARTS, nbParts, reinterpret_cast <LPARAM> (array)) == FALSE)
					throw (TEXT("Error, could not sets the parts of the status bar")) ;
			}

			//-------------------------------------------------------------------------
			// Sets the text of a part of the status bar.
			//
			// Parameters:
			// 
			// std::tstring & str         -> Text
			// const BYTE index          -> Index of the desired part
			// const unsigned long style -> Style of the text
			//-------------------------------------------------------------------------

			void SetText (std::tstring str, const BYTE index, const unsigned long style = 0 ) const
			{
				if (SendMessage (SB_SETTEXT, static_cast <WPARAM> (index | style), reinterpret_cast <LPARAM> (&str[0])) == FALSE)
					throw Win::Exception (TEXT("Error, could not set the text of one of the part of the status bar")) ;
			}

			//-------------------------------------------------------------------------
			// Sets the tooltip text of a part of the status bar.
			//
			// Parameters:
			// 
			// std::tstring & str         -> Text
			// const BYTE index          -> Index of the desired part
			//-------------------------------------------------------------------------

			void SetToolTipText (std::tstring str, const long index) const
			{
				SendMessage (SB_SETTIPTEXT, index, reinterpret_cast <LPARAM> (&str[0])) ;
			}

			//-------------------------------------------------------------------------
			// Sets the unicode format of the status bar.
			//
			// Parameters:
			// 
			// const bool unicode -> True set the unicode flag, False is sets the ASCII style
			//-------------------------------------------------------------------------

			bool SetUnicodeFormat (const bool unicode = false) const
			{
				return SendMessage (SB_SETUNICODEFORMAT, static_cast <WPARAM> (unicode)) != 0 ;
			}

			//-------------------------------------------------------------------------
			// Sets the simple style of the status bar.
			//
			// Parameters:
			// 
			// const bool unicode -> True set the sympleflag, False is sets the "complex" style
			//-------------------------------------------------------------------------

			void SetSimpleStyle (const bool simple = true) const
			{
				SendMessage (SB_SIMPLE, static_cast <WPARAM> (static_cast <BOOL> (FALSE))) ;
			}

		} ;

		//-------------------------------------------------------------------------
		// Win::StatusBarHandleCreator allows to create an StatusBarHandle control.
		// Inherit from Win::ControlCreator for basic functionality.
		//-------------------------------------------------------------------------	

		class StatusBarCreator : public CommonControlCreator
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Creates an status bar control with the functionality of 
			// Win::ControlCreator.
			//-------------------------------------------------------------------------

			StatusBarCreator (Win::Base parent, int id)
				: CommonControlCreator (std::tstring (STATUSCLASSNAME), parent, id)
			{}

			//-------------------------------------------------------------------------
			// Creates a new status bar control.
			// 
			// Return value:  The status bar control handle.
			//
			// Parameters:
			//
			// const std::tstring title -> The title of the status bar control.
			//-------------------------------------------------------------------------

			Win::StatusBarHandle Create (const std::tstring title) const
			{
				return ChildCreator::Create (title) ;
			}

			//-------------------------------------------------------------------------
			// The following methods all serve the same purpose.  They set one of the 
			// style of the future StatusBarHandle control.
			//-------------------------------------------------------------------------

			void SetAutoHorzScrollStyle () {_style |= SBARS_SIZEGRIP ;}
			void SetTopStyle            () {_style |= CCS_TOP ;}
			void SetToolTipStyle        () {_style |= SBT_TOOLTIPS ;}
		} ;
	}

#endif