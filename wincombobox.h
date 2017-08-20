//-----------------------------------------------------------------
//  This file contains classes that allow using combo box controls.
//-----------------------------------------------------------------

#if !defined (WINCOMBOBOX_H)

	#define WINCOMBOBOX_H
	#include "useunicode.h"
	#include "wincontrol.h"
	#include "winunicodehelper.h"

	namespace Win
	{
		//-------------------------------------------------------------------------
		// Exception that is thrown when a try to delete a string in a combo box and it
		// is not there.
		//-------------------------------------------------------------------------

		class ComboBoxDeleteStringException : public Win::Exception
		{
		public:
			ComboBoxDeleteStringException ()
				: Win::Exception (TEXT("Error, the string could not be deleted, it is not in the combo box"))
			{}
		} ;

		//-------------------------------------------------------------------------
		// Exception that is thrown when there is no string selected
		//-------------------------------------------------------------------------

		class ComboBoxSelectStringException : public Win::Exception
		{
		public:
			ComboBoxSelectStringException ()
				: Win::Exception (TEXT("Error, there is no selection"))
			{}
		} ;

		//-------------------------------------------------------------------------
		// Exception that is thrown when a try to find a string in a combo box and it
		// is not there.
		//-------------------------------------------------------------------------

		class ComboBoxFindStringException : public Win::Exception
		{
		public:
			ComboBoxFindStringException ()
				: Win::Exception (TEXT("Error, the desired string is not in the combo box."))
			{}
		} ;

		//-------------------------------------------------------------------------
		// Win::ComboBoxHandle encapsulates a combo box control handle.  Represent a 
		// combo box control.  Inherit from Win::SimpleControl for basic 
		// functionality.
		//-------------------------------------------------------------------------

		class ComboBoxHandle : public SimpleControlHandle
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle to represent the 
			// combo box control through it's parent.
			// 
			// Parameters:
			//
			// const Win::Base parent -> Parent of the static control.
			// const int id      -> Id of the static control.
			//-------------------------------------------------------------------------

			ComboBoxHandle (const Win::Base parent, const int id) 
				: SimpleControlHandle (parent, id)
			{}

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle directly
			// 
			// Parameters:
			//
			// const Win::Base win -> Handle of the static control.
			//-------------------------------------------------------------------------

			ComboBoxHandle(const Win::Base win = NULL)
				: SimpleControlHandle (win)
			{}

			//-------------------------------------------------------------------------
			// Initialize the handle and the id through the parent handle.
			//-------------------------------------------------------------------------

			void Init (const Win::Base parent, const int id)
			{
				SimpleControlHandle::Init (parent, id)  ;
			}

			//-------------------------------------------------------------------------
			// Destructor.  Empty the combo box.
			//-------------------------------------------------------------------------

			~ComboBoxHandle ()
			{
				ResetContent () ;
			}

			void SetText (const std::tstring str) const
			{ 
				LRESULT result = SendMessage (WM_SETTEXT, 0, reinterpret_cast <LPARAM> (str.c_str())) ;
				if (result == CB_ERRSPACE || result == CB_ERR)
					throw Win::Exception (TEXT("Error, could not set the text of the edit control")) ;
			}


			int AddString (const std::tstring str) ;
			int InsertString (const int index, const std::tstring str) ;

			//-------------------------------------------------------------------------
			// Replaces the string at the specified index of a list box.
			//
			// Return value: The 0 based index of the string or an error value.
			//
			// Parameters:
			//
			// const int index       -> The position of the string that will be
			//							replaced.
			// const std::tstring str -> The new string.
			//-------------------------------------------------------------------------

			void ReplaceString (const int index, const std::tstring str)
			{
				DeleteString (index) ;
				InsertString (index, str) ;
			}

			int DeleteString (const int index) ;
			int FindString (const int startIndex, const std::tstring & str) const ;
			int FindStringExact (const int startIndex, const std::tstring & str) const ;
			int GetCount () const ;
			int GetCurrentSel () const ;

			void GetDroppedControlRect (Win::Rect & rect) const
			{
				if (!SendMessage (CB_GETDROPPEDCONTROLRECT, 0, 
					reinterpret_cast <LPARAM> (reinterpret_cast <RECT FAR *> (&rect))))
				{
					throw Win::Exception (TEXT("Error, could not get the screen coordinates of the drop down list of the combo box")) ;
				}
			}

			Win::Rect GetDroppedControlRect () const ;

			//-------------------------------------------------------------------------
			// Determines if the drop down list is dropped.
			//
			// Return value: True if the drop down list is dropped, else false.
			//-------------------------------------------------------------------------

			bool IsDropped () const 
			{
				return SendMessage (CB_GETDROPPEDSTATE, 0, 0) == TRUE ;
			}

			int GetDroppedWidth () const ;

			//-------------------------------------------------------------------------
			// Determines if the combo box has the default user interface or the 
			// extended user interface.
			//
			// Return value: True if it is the extended user interface, else false.
			//-------------------------------------------------------------------------

			bool GetExtendedGui () const 
			{
				return SendMessage (CB_GETEXTENDEDUI, 0, 0) == TRUE ;
			}

			//-------------------------------------------------------------------------
			// Obtains the witdh by which the dropped down list can be scrolled 
			// horizontaly.
			//
			// Return value: The width in pixel.
			//-------------------------------------------------------------------------

			int GetHorizontalExtent () const 
			{
				return SendMessage (CB_GETHORIZONTALEXTENT, 0, 0) ;
			}

			DWORD GetItemData (const int index) const ;
			int GetItemHeight (const int index) const ;
			int GetTextLength (const int index) const ;
			std::tstring GetListBoxText (const int index) const ;
			int GetFirstVisibleItemIndex () const ;
			int SetInitStorage (const int nbItem, const int sizeInByte) ;

			//-------------------------------------------------------------------------
			// Sets a limit on the number of characters that can be typed in the edit
			// control of the combo box.
			//
			// Parameters:
			//
			// const int limit -> The desired limit.
			//-------------------------------------------------------------------------

			void LimitEditText (const int limit) 
			{
				SendMessage (CB_LIMITTEXT, limit, 0) ;
			}

			//-------------------------------------------------------------------------
			// Empty the combo box.
			//-------------------------------------------------------------------------

			void ResetContent ()
			{
				SendMessage (CB_RESETCONTENT, 0, 0) ;
			}

			int SelectString (const int indexStart, const std::tstring  str) ;

			//-------------------------------------------------------------------------
			// Sets the current selection.
			//
			// Parameters:
			//
			// const int index -> The index of the index that must be selected.
			//-------------------------------------------------------------------------

			void SetSelection (const int index)
			{
				if (SendMessage (CB_SETCURSEL, index, 0) == CB_ERR)
					throw Win::Exception (TEXT("Error, could not set the selection.")) ;

			}

			//-------------------------------------------------------------------------
			// Removes the selection.
			//-------------------------------------------------------------------------

			void NoSelection ()
			{
				SendMessage (CB_SETCURSEL, -1, 0) ;
			}

			//-------------------------------------------------------------------------
			// Sets the maximum width of the dropped down list.
			//
			// Parameters:
			//
			// const int width -> The maximum width.
			//-------------------------------------------------------------------------

			void SetDroppedWidth (const int width)
			{
				if (SendMessage (CB_SETDROPPEDWIDTH, width, 0) == CB_ERR)
					throw Win::Exception (TEXT("Error, could not set the dropped width of the combo box.")) ;
			}

			//-------------------------------------------------------------------------
			// Sets the selection of the edit control of the combo box.
			//
			// Return value: TRUE if the method succeed, else and error code.
			// 
			// Parameters:
			//
			// const int start -> Beginning of the selection.
			// const int end   -> Ending of the selection.
			//-------------------------------------------------------------------------

			void SetEditSelection (const int start, const int end)
			{
				if (!SendMessage (CB_SETEDITSEL, 0, MAKELPARAM (start, end)))
					throw Win::Exception (TEXT("Error, could not set the edit selection of the combo box.")) ;

			}

			//-------------------------------------------------------------------------
			// Select the default or extended user interface..
			//
			// Parameters:
			//
			// const bool extended -> True for extended, false for default.
			//-------------------------------------------------------------------------

			void SetExtendedGui (const bool extended)
			{
				if (SendMessage (CB_SETEXTENDEDUI, extended, 0) == CB_ERR)
					throw Win::Exception (TEXT("Error, could set the extende gui for the combo box.")) ;

			}

			//-------------------------------------------------------------------------
			// Sets the width by which the dropped down list can be scrolled.
			//
			// Parameters:
			//
			// const int extent -> The width by which the  list can be scrolled.
			//-------------------------------------------------------------------------

			void SetHorizontalExtent (const int extent)
			{
				SendMessage (CB_SETHORIZONTALEXTENT, extent, 0) ;
			}

			//-------------------------------------------------------------------------
			// Sets the 32-bit value associated with an item of the combo box
			//
			// Parameters:
			//
			// const int index  -> Index of the item.
			// const DWORD data -> The 32-bit value associated with an item.
			//-------------------------------------------------------------------------

			void SetItemData (const int index, const DWORD data)
			{
				if (SendMessage (CB_SETITEMDATA, index, data) == CB_ERR)
					throw Win::Exception (TEXT("Error, could not set the item data of the combo box.")) ;

			}

			//-------------------------------------------------------------------------
			// Sets the height of an item of the combo box.
			//
			// Parameters:
			//
			// const int index  -> Index of the item.
			// const int height -> New height of an item.
			//-------------------------------------------------------------------------

			void SetItemHeight (const int index, const int height)
			{
				if (SendMessage (CB_SETITEMHEIGHT, index, height) == CB_ERR)
					throw Win::Exception (TEXT("Error, could not set the item height of the combo box.")) ;
			}

			//-------------------------------------------------------------------------
			// Sets the index of the first visible item of the combo box.
			//
			// Parameters:
			//
			// const int index  -> Index of the item.
			//-------------------------------------------------------------------------

			void SetFirstVisibleItemIndex (const int index) 
			{
				if (SendMessage (CB_SETTOPINDEX, index, 0) == CB_ERR)
					throw Win::Exception (TEXT("Error, could not the first visible index of the combo box.")) ;

			}

			//-------------------------------------------------------------------------
			// Shows the drop down list of the combo box.
			//-------------------------------------------------------------------------

			void ShowDropDown ()
			{
				SendMessage (CB_SHOWDROPDOWN, TRUE, 0) ;
			}

			//-------------------------------------------------------------------------
			// Hides the drop down list of the combo box.
			//-------------------------------------------------------------------------

			void HideDropDown ()
			{
				SendMessage (CB_SHOWDROPDOWN, FALSE, 0) ;
			}


			//-------------------------------------------------------------------------
			// Fills the combo box with a directory listing.
			//
			// Parameters:
			//
			// const Win::Base dlg		-> The dialog box that contains the combo box.
			// char * pathBuf			-> Path or filename.
			// const int idStatic       -> Id of the static control in which the name 
			//							   of the current directory.
			// const unsigned fileTypes -> Attributes of the files that must be 
			//							   displayed.
			//-------------------------------------------------------------------------

			void ListDirectory ( std::tstring & pathBuf, const int idStatic = 0, const unsigned fileTypes = DDL_DIRECTORY | DDL_DRIVES)
			{
				if (!::DlgDirListComboBox (GetParent(), &pathBuf[0], GetId (), idStatic, fileTypes))
					throw Win::Exception (TEXT("Error, could not list the directories in the combo box")) ;
			}

			//-------------------------------------------------------------------------
			// Fills the combo box with a directory listing.
			//
			// Parameters:
			//
			// char * pathBuf			-> Path or filename.
			// const unsigned fileTypes -> Attributes of the files that must be 
			//							   displayed.
			//-------------------------------------------------------------------------

			void ListDirectory (std::tstring & pathBuf, const unsigned fileTypes = DDL_DIRECTORY | DDL_DRIVES)
			{
				int test = SendMessage (CB_DIR, fileTypes, reinterpret_cast<LPARAM> (&pathBuf[0]) ) ;

				if (test == CB_ERR || test == CB_ERRSPACE)
					throw (Win::Exception (TEXT("Error, could not list the directories in the combo box")));
			}

			//-------------------------------------------------------------------------
			// Obtains the currently selected item from a combo box filled by a 
			// directory listing.
			//
			// Parameters:
			//
			// const Win::Base dlg		-> The dialog box that contains the combo box.
			// char * pathBuf			-> Will receive the path.
			// const int bufLen         -> Length in characters of the path.
			//-------------------------------------------------------------------------

			void GetSelectedPath (std::tstring & pathBuf)
			{
				if (!DlgDirSelectComboBoxEx (GetParent (), &pathBuf[0], pathBuf.length (), GetId ()))
					throw (Win::Exception (TEXT("Error, could not obtain the selected path from the combo box")));
			}
	
		} ;

		//-------------------------------------------------------------------------
		// Win::ComboBoxHandleCreator allows to create a combo box control.
		// Inherit from Win::ControlCreator for basic functionality.
		//-------------------------------------------------------------------------	

		class ComboBoxCreator : public ControlCreator
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Creates a combo box control with the functionality of 
			// Win::ControlCreator.
			//-------------------------------------------------------------------------

			ComboBoxCreator (const Win::Base parent, const int id)
				: ControlCreator (std::tstring (TEXT("combobox")), parent, id)
			{}

			//-------------------------------------------------------------------------
			// Creates a new combobox control.
			// 
			// Return value:  The combobox control handle.
			//
			// Parameters:
			//
			// const std::tstring title -> The title of the static control.
			//-------------------------------------------------------------------------

			Win::ComboBoxHandle Create (const std::tstring title) const
			{
				return ChildCreator::Create (title) ;
			}


			//-------------------------------------------------------------------------
			// The following methods all serve the same purpose.  They set one of the 
			// style of the future combo box control.
			//-------------------------------------------------------------------------

			void SetAutoHorzScrollStyle    () {_style |= CBS_AUTOHSCROLL ;}
			void SetDisableNoScrollStyle   () {_style |= CBS_DISABLENOSCROLL ;}
			void SetDropDownStyle          () {_style |= CBS_DROPDOWN ;}
			void SetDropDownListStyle      () {_style |= CBS_DROPDOWNLIST ;}
			void SetHasStringsStyle        () {_style |= CBS_HASSTRINGS ;}
			void SetLowerCaseStyle         () {_style |= CBS_LOWERCASE ;}
			void SetNoIntegralHeightStyle  () {_style |= CBS_NOINTEGRALHEIGHT ;}
			void SetOemConvertStyle        () {_style |= CBS_OEMCONVERT ;}
			void SetOwnerDrawFixedStyle    () {_style |= CBS_OWNERDRAWFIXED ;}
			void SetOwnerDrawVariableStyle () {_style |= CBS_OWNERDRAWVARIABLE ;}
			void SetSimpleStyle            () {_style |= CBS_SIMPLE ;}
			void SetSortStyle              () {_style |= CBS_SORT ;}
			void SetUpperCaseStyle         () {_style |= CBS_UPPERCASE ;}
		} ;
	}

#endif