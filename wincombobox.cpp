#include "wincombobox.h"

//-------------------------------------------------------------------------
// Obtains one of the string of the combo box.
//
// Return value: The desired string.
//
// Parameters:
//
// const int index -> Index of the string.
//-------------------------------------------------------------------------

std::tstring Win::ComboBoxHandle::GetListBoxText (const int index) const 
{
	int len = GetTextLength (index) ;
	std::tstring str ;

	// Makes sure the string has enough space
	str.reserve (len + 1) ;
	str.resize (len) ;

	// Obtains the string.
	if (SendMessage (CB_GETLBTEXT, index, reinterpret_cast <LPARAM> (&str[0])) == CB_ERR)
		throw Win::Exception (TEXT("Error, could not get the list box text of the combo box")) ;

	return str ;
}

			//-------------------------------------------------------------------------
			// Adds a String at the end of the combo box (Unless CB_SORT is specified.)
			//
			// Return value: The 0 based index of the string or an error value.
			//
			// Parameters:
			//
			// const std::tstring str -> The string to be added.
			//-------------------------------------------------------------------------

			int Win::ComboBoxHandle::AddString (const std::tstring str)
			{
				int val = SendMessage (CB_ADDSTRING, 0, reinterpret_cast<LPARAM> (str.c_str ())) ;

				if (val == CB_ERR || val == CB_ERRSPACE)
					throw Win::Exception (TEXT("Error, could not add a string to the combobox")) ;

				return val;
			}

			//-------------------------------------------------------------------------
			// Add a string at the specified index of a combo box.
			//
			// Return value: The 0 based index of the string or an error value.
			//
			// Parameters:
			//
			// const int index       -> The position where the string will be added.
			// const std::tstring str -> The string to be added.
			//-------------------------------------------------------------------------

			int Win::ComboBoxHandle::InsertString (const int index, const std::tstring str)
			{
				int val = SendMessage (CB_INSERTSTRING, index,  reinterpret_cast <LPARAM> (str.c_str ())) ;

				if (val == CB_ERR || val == CB_ERRSPACE)
					throw Win::Exception (TEXT("Error, could not insert a string to the combobox")) ;

				return val;
			}

			//-------------------------------------------------------------------------
			// Deletes the string at the specified index of a list box.
			//
			// Return value: The number os string remaining or an error value.
			//
			// Parameters:
			//
			// const int index -> The position of the string that will be deleted.
			//-------------------------------------------------------------------------

			int Win::ComboBoxHandle::DeleteString (const int index)
			{
				int val = SendMessage (LB_DELETESTRING, index, 0) ;

				if (val == CB_ERR)
					throw Win::ComboBoxDeleteStringException () ;

				return val;
			}

			//-------------------------------------------------------------------------
			// Finds a string in the combo box that begins by the characters contained
			// in a specified string.
			//
			// Return value: The 0 based index of the string that was found or an error
			// value.
			//
			// Parameters:
			//
			// const int startIndex  -> The search start at this position.
			// const std::tstring str -> The method search for the string in the combo
			//							box that begins by those characters.
			//-------------------------------------------------------------------------

			int Win::ComboBoxHandle::FindString (const int startIndex, const std::tstring & str) const
			{
				int val =  SendMessage (CB_FINDSTRING, startIndex, reinterpret_cast <LPARAM> (str.c_str ())) ;

				if (val == CB_ERR)
					throw Win::ComboBoxFindStringException ();

				return val;
			}

			//-------------------------------------------------------------------------
			// Finds a string in the combo box that exactly match specified string.
			//
			// Return value: The 0 based index of the string that was found or an error
			// value.
			//
			// Parameters:
			//
			// const int startIndex  -> The search start at this position.
			// const std::tstring str -> The string that must be search.
			//-------------------------------------------------------------------------

			int Win::ComboBoxHandle::FindStringExact (const int startIndex, const std::tstring & str) const 
			{
				int val =  SendMessage (CB_FINDSTRINGEXACT, startIndex, reinterpret_cast <LPARAM> (str.c_str ())) ;

				if (val == CB_ERR)
					throw Win::ComboBoxFindStringException ();

				return val;
			}
	
			//-------------------------------------------------------------------------
			// Obtains the number of string present in the combo box.
			//
			// Return value: The number of string or an error value.
			//-------------------------------------------------------------------------

			int Win::ComboBoxHandle::GetCount () const 
			{
				int val =  SendMessage (CB_GETCOUNT, 0, 0) ;
				
				if (val == CB_ERR)
					throw Win::Exception (TEXT("Error, could not get the number of string in combobox")) ;

				return val;
			}

			//-------------------------------------------------------------------------
			// Obtains the index of the currently selected string.
			//
			// Return value: The index of the currently selected string.
			//-------------------------------------------------------------------------

			int Win::ComboBoxHandle::GetCurrentSel () const 
			{
				int val = SendMessage (CB_GETCURSEL, 0, 0) ;
				
				if (val == CB_ERR)
					throw Win::ComboBoxSelectStringException () ;

				return val;
			}

			//-------------------------------------------------------------------------
			// Obtains the screen coordinates of the drop-down list of the combo box.
			//
			// Parameters:
			//
			// Win::Rect & rect -> Will contain the screen coordinates of the drop down
			//					   list.
			//-------------------------------------------------------------------------

			Win::Rect Win::ComboBoxHandle::GetDroppedControlRect () const
			{
				Win::Rect rect ;

				if (!SendMessage (CB_GETDROPPEDCONTROLRECT, 0, 
					reinterpret_cast <LPARAM> (reinterpret_cast <RECT FAR *> (&rect))))
				{
					throw Win::Exception (TEXT("Error, could not get the screen coordinates of the drop down list of the combo box")) ;
				}

				return rect ;
			}

			//-------------------------------------------------------------------------
			// Obtains the width of the dropped down list.
			//
			// Return value: The width of the dropped down list in pixel.
			//-------------------------------------------------------------------------

			int Win::ComboBoxHandle::GetDroppedWidth () const 
			{
				int val = SendMessage (CB_GETDROPPEDWIDTH, 0, 0) ;

				if (val == CB_ERR)
					throw Win::Exception (TEXT("Error, could not get the dropped width of the combobox")) ;

				return val;
			}

			//-------------------------------------------------------------------------
			// Obtains the 32-bit value associated with an item of the combo box
			//
			// Return value: The 32-bit value associated with the item.
			//
			// Parameters:
			//
			// const int index -> Index of the item.
			//-------------------------------------------------------------------------

			DWORD Win::ComboBoxHandle::GetItemData (const int index) const 
			{
				int val =  SendMessage (CB_GETITEMDATA, index, 0) ;

								
				if (val == CB_ERR)
					throw Win::Exception (TEXT("Error, could not get the item data for a combobox")) ;

				return val;
			}

			//-------------------------------------------------------------------------
			// Obtains the height of one of the item of the combo box.
			//
			// Return value: The height in pixel.
			//
			// Parameters:
			//
			// const int index -> Index of the string.
			//-------------------------------------------------------------------------

			int Win::ComboBoxHandle::GetItemHeight (const int index) const 
			{
				int val = SendMessage (CB_GETITEMHEIGHT, index, 0) ;
				
				if (val == CB_ERR)
					throw Win::Exception (TEXT("Error, could not get the item height for a combobox")) ;

				return val;
			}

			//-------------------------------------------------------------------------
			// Obtains the lenght of one of the string of the combo box.
			//
			// Return value: The lenght in character.
			//
			// Parameters:
			//
			// const int index -> Index of the string.
			//-------------------------------------------------------------------------

			int Win::ComboBoxHandle::GetTextLength (const int index) const  
			{
				int val =  SendMessage (CB_GETLBTEXTLEN, index, 0) ;
			
				if (val == CB_ERR)
					throw Win::Exception (TEXT("Error, could not get the text lenght of the combobox")) ;

				return val;
			}

			//-------------------------------------------------------------------------
			// Obtains the index of the first visible item of the combo box.
			//
			// Return value: The index of the first visible item.
			//-------------------------------------------------------------------------

			int Win::ComboBoxHandle::GetFirstVisibleItemIndex () const 
			{
				int val = SendMessage (CB_GETTOPINDEX, 0, 0) ;
								
				if (val == CB_ERR)
					throw Win::Exception (TEXT("Error, could not get the first visible item in combobox")) ;

				return val;
			}

			//-------------------------------------------------------------------------
			// Pre-Allocates memory for storing items in the combo box.
			//
			// Return value: The number of item for which memories was pre-allocated.
			//
			// Parameters:
			//
			// const int nbItem -> Number of items.
			// const int sizeInByte -> The total size in bytes.
			//-------------------------------------------------------------------------

			int Win::ComboBoxHandle::SetInitStorage (const int nbItem, const int sizeInByte)
			{
				int val = SendMessage (CB_INITSTORAGE, nbItem, sizeInByte) ;

								
				if (val == CB_ERRSPACE)
					throw Win::Exception (TEXT("Error, could not enough memory to set the initial storage for the combo box.")) ;

				return val;
			}

			//-------------------------------------------------------------------------
			// Find a string and select it.
			//
			// Parameters:
			//
			// const int indexStart   -> Index at which the search must start.
			// const std::tstring  str -> The string that must be found
			//-------------------------------------------------------------------------

			int Win::ComboBoxHandle::SelectString (const int indexStart, const std::tstring  str)
			{
				int val = SendMessage (CB_SELECTSTRING, indexStart, reinterpret_cast<LPARAM> (str.c_str () )) ;

				if (val == CB_ERR)
					throw Win::ComboBoxFindStringException ();

				return val;
			}

