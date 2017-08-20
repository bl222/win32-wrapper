//-----------------------------------------------------------------
//  This file contains classes that allow using EditHandle controls.
//-----------------------------------------------------------------

#if !defined (WINEDIT_H)

	#define WINEDIT_H
	#include "useunicode.h"
	#include "wincontrol.h"

	namespace Win
	{
		//-------------------------------------------------------------------------
		// Win::EditHandle encapsulates an EditHandle control handle.  Represents 
		// an EditHandle control.  Inherit from Win::SimpleControl for basic 
		// functionality.
		//-------------------------------------------------------------------------

		class EditHandle : public SimpleControlHandle
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle to represent the EditHandle
			// control through it's parent.
			// 
			// Parameters:
			//
			// const Win::Base parent -> Parent of the static control.
			// const int id      -> Id of the static control.
			//-------------------------------------------------------------------------

			EditHandle (const Win::Base parent, const int id)
				: SimpleControlHandle (parent, id)
			{}

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle directly
			// 
			// Parameters:
			//
			// const Win::Base win -> Handle of the group box control.
			//-------------------------------------------------------------------------

			EditHandle (const Win::Base win = NULL)
				: SimpleControlHandle (win)
			{}

			//-------------------------------------------------------------------------
			// Initialize the handle and the id through the parent handle.
			//-------------------------------------------------------------------------

			void Init (const Win::Base parent, const int id)
			{
				SimpleControlHandle::Init (parent, id);
			}

			void SetText (const std::tstring str) const
			{ 
				if (SendMessage (WM_SETTEXT, 0, reinterpret_cast <LPARAM> (str.c_str())) == FALSE)
					throw Win::Exception (TEXT("Error, could not set the text of the edit control")) ;
			}

			//-------------------------------------------------------------------------
			// Determines if the last action on the EditHandle control can be undone.
			//
			// Return value:  True if the action can be undone, else false.
			//-------------------------------------------------------------------------

			bool CanUndo () const
			{
				return SendMessage (EM_CANUNDO, 0, 0) == TRUE ;
			}

			//-------------------------------------------------------------------------
			// Allows to empty the undo buffer.
			//-------------------------------------------------------------------------

			void EmptyUndoBuffer () const
			{
				SendMessage (EM_EMPTYUNDOBUFFER, 0, 0) ;
			}

			//-------------------------------------------------------------------------
			// Obtains the first visible line.
			//
			// Return value:  The index of the first visible line.
			//-------------------------------------------------------------------------

			int GetFirstVisibleLine () const
			{
				return SendMessage (EM_GETFIRSTVISIBLELINE, 0, 0) ;
			}

			//-------------------------------------------------------------------------
			// Obtains the text limit.
			//
			// Return value:  The text limit.
			//-------------------------------------------------------------------------

			int GetTextLimit () const
			{
				return SendMessage (EM_GETLIMITTEXT, 0, 0) ;
			}

			//-------------------------------------------------------------------------
			// Obtains the number of line of the EditHandle control.
			//
			// Return value:  The number of line.
			//-------------------------------------------------------------------------

			unsigned int GetNbLines () const
			{
				return SendMessage (EM_GETLINECOUNT, 0, 0) ;
			}

			//-------------------------------------------------------------------------
			// Obtains the lenght in characters of one of the line of the EditHandle control.
			//
			// Return value:  The lenght of the line.
			//
			// Parameters:
			//
			// const int charIndex -> Index of one of the character of the line.
			//-------------------------------------------------------------------------

			unsigned int GetLineLength (const int charIndex) const
			{
				return SendMessage (EM_LINELENGTH, charIndex, 0) ;
			}

			//-------------------------------------------------------------------------
			// Obtains the number of unselected character on lines with selected
			// characters.
			//
			// Return value:  the number of unselected character on lines with selected
			// characters.
			//-------------------------------------------------------------------------

			unsigned int GetNbUnselectedCharOnLines () const
			{
				return SendMessage (EM_LINELENGTH, -1, 0) ;
			}

			void GetMargins (int & left, int & right)  const ; 

			//-------------------------------------------------------------------------
			// Obtains the starting and ending charcter position of the selection.
			//
			// Parameters:
			//
			// DWORD * start -> Will point on the stating position.
			// DWORD * end   -> Will point on the ending position.
			//-------------------------------------------------------------------------

			void GetSelection (DWORD * const start, DWORD * const end) const
			{
				SendMessage (EM_GETSEL, 
					reinterpret_cast <WPARAM> (reinterpret_cast <LPDWORD> (start)), 
					reinterpret_cast <LPARAM> (reinterpret_cast <LPDWORD> (end))) ;
			}

			//-------------------------------------------------------------------------
			// Obtains the formating rectangle of the EditHandle control..
			//
			// Parameters:
			//
			// Win::Rect & rect -> Will contain the coordinates of the formating
			//					   Rectangle.
			//-------------------------------------------------------------------------

			void GetRect (Win::Rect & rect) const
			{
				SendMessage (EM_GETRECT, 0, 
					reinterpret_cast <LPARAM> (reinterpret_cast <LPRECT> (&rect))) ;
			}

			Win::Rect GetRect () const ;

			//-------------------------------------------------------------------------
			// Obtains the index of the line containing a particular char index.
			//
			// Return value:  The line index.
			//
			// Parameters:
			//
			// const int indexChar -> The character index.
			//-------------------------------------------------------------------------

			int GetLineFromChar (const int indexChar) const
			{
				return SendMessage (EM_LINEFROMCHAR, indexChar, 0) ;
			}

			int GetLineIndex (const int line) const ;

			//-------------------------------------------------------------------------
			// Obtains the position of the thumb (scroll box) in a multiline EditHandle control.
			//
			// Return value:  The position of the thumb.
			//-------------------------------------------------------------------------

			unsigned int GetThumbPos () const
			{
				return SendMessage (EM_GETTHUMB, 0, 0) ;
			}

			//-------------------------------------------------------------------------
			// Determines if the EditHandle control was modified.
			//
			// Return value:  True if it was modified, else false.
			//-------------------------------------------------------------------------

			bool HasBeenModified () const
			{
				return SendMessage (EM_GETMODIFY, 0, 0) == TRUE ;
			}

			//-------------------------------------------------------------------------
			// Sets the left and right margins used by the EditHandle control.
			//
			// Parameters:
			//
			// const int leftWidth -> Left margin.
			// const int rightWidth -> Right margin.
			//-------------------------------------------------------------------------

			void SetMargins (const int leftWidth, const int rightWidth)
			{
				SendMessage (EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, MAKELONG (leftWidth, rightWidth) ) ;
			}

			//-------------------------------------------------------------------------
			// Sets the left and right margins used by the EditHandle control by using some
			// information on the current font.
			//-------------------------------------------------------------------------

			void SetMarginByUsingFontInfo ()
			{
				SendMessage (EM_SETMARGINS, EC_USEFONTINFO, 0) ;
			}

			//-------------------------------------------------------------------------
			// Sets the maximum number of characters contained by the EditHandle control.
			//
			// Parameters:
			//
			// const int limit -> Maximum number of characters.
			//-------------------------------------------------------------------------

			void SetTextLimit (const int limit)
			{
				SendMessage(EM_SETLIMITTEXT, limit, 0) ;
			}

			//-------------------------------------------------------------------------
			// Sets or clears the inclusion flag of soft line break characters of the EditHandle control
			//
			// Parameters:
			//
			// const bool lineFlag -> True for the flag to be on.  False for the flag 
			//                        to be off.
			//-------------------------------------------------------------------------

			void SetSoftLineBreakFlag (const bool lineFlag) 
			{
				SendMessage (EM_FMTLINES, 0, lineFlag) ;
			}

			//-------------------------------------------------------------------------
			// Sets or clears the modification flag of the EditHandle control
			//
			// Parameters:
			//
			// const bool modified -> True for the flag to be on.  False for the flag 
			//                        to be off.
			//-------------------------------------------------------------------------

			void SetModify (const bool modified)
			{
				SendMessage (EM_SETMODIFY, modified, 0) ;
			}

			//-------------------------------------------------------------------------
			// Sets the character to be displayed when the user enters a password.
			//
			// Parameters:
			//
			// const TCHAR passwordChar -> the character to be displayed when the user
			// enters a password.
			//-------------------------------------------------------------------------

			void SetPasswordChar (const TCHAR passwordChar)
			{
				SendMessage (EM_SETPASSWORDCHAR, 
					static_cast <UINT> (passwordChar)) ;
			}

			//-------------------------------------------------------------------------
			// Makes the EditHandle control read only.
			//-------------------------------------------------------------------------

			bool MakeReadOnly ()
			{
				return SendMessage (EM_SETREADONLY, TRUE, 0) != 0;
			}

			//-------------------------------------------------------------------------
			// Removes the read only attribute of the EditHandle control.
			//-------------------------------------------------------------------------

			bool MakeNotReadOnly ()
			{
				return SendMessage (EM_SETREADONLY, FALSE, 0) != 0;
			}

			//-------------------------------------------------------------------------
			// Sets the formating rectangle of a multiline EditHandle control and redraw the
			// control.
			//
			// Parameters:
			//
			// Win::Rect & rect -> The formating rectangle.
			//-------------------------------------------------------------------------

			void SetRect (Win::Rect & rect)
			{
				SendMessage (EM_SETRECT, 0, 
					reinterpret_cast <LPARAM> (reinterpret_cast <LPRECT> (&rect))) ;
			}

			//-------------------------------------------------------------------------
			// Sets the formating rectangle of a multiline EditHandle control and fo not 
			// redraw the control.
			//
			// Parameters:
			//
			// Win::Rect & rect -> The formating rectangle.
			//-------------------------------------------------------------------------

			void SetRectNp (Win::Rect & rect)
			{
				SendMessage (EM_SETRECTNP, 0, 
					reinterpret_cast <LPARAM> (reinterpret_cast <LPRECT> (&rect))) ;
			}

			//-------------------------------------------------------------------------
			// Sets the selection of the EditHandle control.
			//
			// Parameters:
			//
			// const int begin -> The character index at whitch the selection begins.
			// const int end   -> The character index at whitch the selection ends.
			//-------------------------------------------------------------------------

			void SetSelection (const int begin, const int end)
			{
				SendMessage (EM_SETSEL, begin, end) ;
			}

			//-------------------------------------------------------------------------
			// Selects all the text of the EditHandle control.
			//-------------------------------------------------------------------------

			void SelectAll ()
			{
				SendMessage (EM_SETSEL, 0, -1);
			}

			void SelectLine (const int lineIdx) ;

			//-------------------------------------------------------------------------
			// Sets amount of text a user can enter in the EditHandle control.
			//
			// Parameters:
			//
			// const unsigned int max -> The maximun number of characters.
			//-------------------------------------------------------------------------

			void LimitText (const unsigned int max)
			{
				SendMessage (EM_LIMITTEXT, max, 0) ;
			}

			//-------------------------------------------------------------------------
			// Scrolls the text horizontaly or verticaly
			//
			// Parameters:
			//
			// const int xScroll -> Amount of vertical scrolling.
			// const int yScroll -> Amount of horizontal scrolling.
			//-------------------------------------------------------------------------

			void LineScroll (const int xScroll, const int yScroll)
			{
				SendMessage (EM_LINESCROLL, xScroll, yScroll) ;
			}

			//-------------------------------------------------------------------------
			// Scrolls one line down.
			//-------------------------------------------------------------------------

			int ScrollLineDown ()
			{
				return LOWORD (SendMessage (EM_SCROLL, SB_LINEDOWN, 0)) ;
			}

			//-------------------------------------------------------------------------
			// Scrolls one line up.
			//-------------------------------------------------------------------------

			int ScrollLineUp ()
			{
				return LOWORD (SendMessage (EM_SCROLL, SB_LINEUP, 0)) ;
			}


			//-------------------------------------------------------------------------
			// Scrolls one page down.
			//-------------------------------------------------------------------------

			int ScrollPageDown ()
			{
				return LOWORD (SendMessage (EM_SCROLL, SB_PAGEDOWN, 0)) ;
			}


			//-------------------------------------------------------------------------
			// Scrolls one page up.
			//-------------------------------------------------------------------------

			int ScrollPageUp ()
			{
				return LOWORD (SendMessage (EM_SCROLL, SB_PAGEUP, 0)) ;
			}

			//-------------------------------------------------------------------------
			// Scrolls  the caret.
			//-------------------------------------------------------------------------

			void ScrollCaret ()
			{
				SendMessage (EM_SCROLLCARET, 0, 0) ;
			}

			//-------------------------------------------------------------------------
			// Replace the selected text by another text.
			//
			// Parameters:
			// 
			// std::tstring info -> Contains the new txt.
			// bool canUndo     -> True if the replacement can be undone, else false.
			//-------------------------------------------------------------------------

			void ReplaceSelection (std::tstring info, bool canUndo = false)
			{
				SendMessage (EM_REPLACESEL, canUndo, reinterpret_cast <LPARAM> (info.c_str())) ;
			}

			//-------------------------------------------------------------------------
			// Undo the last action effectuated on the EditHandle control.
			//-------------------------------------------------------------------------

			void Undo ()
			{
				if (SendMessage (EM_UNDO, 0, 0) == 0)
					throw Win::Exception (TEXT("Error, could not undo.")) ;
			}

			void Append (const std::tstring str) ;


			//-------------------------------------------------------------------------
			// Determines if the EditHandle control was changed.
			//
			// Return value: True if the control is changed, else false.
			//
			// Parameters:
			//
			// const int code -> The hi word of the wParam of the WM_COMAND message.
			//-------------------------------------------------------------------------

			static bool IsChanged (const int code)
			{ 
				return code == EN_CHANGE ;
			}

			void Clear () ;
		} ;

		//-------------------------------------------------------------------------
		// Win::EditHandleCreator allows to create an EditHandle control.
		// Inherit from Win::ControlCreator for basic functionality.
		//-------------------------------------------------------------------------	

		class EditCreator : public ControlCreator
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Creates an edti control with the functionality of 
			// Win::ControlCreator.
			//-------------------------------------------------------------------------

			EditCreator (Win::Base parent, int id)
				: ControlCreator (std::tstring (TEXT("edit")), parent, id)
			{}

			//-------------------------------------------------------------------------
			// Creates a new edit control.
			// 
			// Return value:  The edit control handle.
			//
			// Parameters:
			//
			// const std::tstring title -> The title of the static control.
			//-------------------------------------------------------------------------

			Win::EditHandle Create (const std::tstring title) const
			{
				return ChildCreator::Create (title) ;
			}

			//-------------------------------------------------------------------------
			// The following methods all serve the same purpose.  They set one of the 
			// style of the future EditHandle control.
			//-------------------------------------------------------------------------

			void SetAutoHorzScrollStyle       () {_style |= ES_AUTOHSCROLL ;}
			void SetAutoVertScrollStyle       () {_style |= ES_AUTOVSCROLL ;}
			void SetCenterStyle               () {_style |= ES_CENTER ;}
			void SetLeftStyle                 () {_style |= ES_LEFT ;}
			void SetLowerCaseStyle            () {_style |= ES_LOWERCASE ;}
			void SetMultilineStyle            () {_style |= ES_MULTILINE ;}
			void SetNoHideSelectionStyle      () {_style |= ES_NOHIDESEL ;}
			void SetNumberStyle               () {_style |= ES_NUMBER ;}
			void SetOemConvertStyle           () {_style |= ES_OEMCONVERT ;}
			void SetPasswordStyle             () {_style |= ES_PASSWORD;}
			void SetReadOnlyStyle             () {_style |= ES_READONLY ;}
			void SetRightStyle                () {_style |= ES_RIGHT ;}
			void SetUpperCasetStyle           () {_style |= ES_UPPERCASE ;}
			void SetWantReturnStyle           () {_style |= ES_WANTRETURN ;}
		} ;
	}

#endif