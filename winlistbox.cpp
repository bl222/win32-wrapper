#include "winlistbox.h"

			//-------------------------------------------------------------------------
			// Obtains one of the string of the combo box.
			//
			// Return value: The desired string.
			//
			// Parameters:
			//
			// const int index -> Index of the string.
			//-------------------------------------------------------------------------

			std::tstring Win::ListBoxHandle::GetText (const int index) const 
			{
				int len = GetTextLength (index) ;
				std::tstring str ;

				// Make sure str has enough space.
				str.reserve (len + 1) ;
				str.resize (len) ;

				// Obtain the string.
				if (SendMessage (LB_GETTEXT, index, reinterpret_cast <LPARAM> (&str[0])) == LB_ERR)
					throw Win::Exception (TEXT("Error, could not get the text from the list box")) ;
				return str ;
			}

			//-------------------------------------------------------------------------
			// Adds a file to a list box.  The list box must contain a directery list 
			// box.
			//
			// Parameters:
			//
			// const std::tstring file -> Name of the file.
			//-------------------------------------------------------------------------

			int Win::ListBoxHandle::AddFile (const std::tstring file)
			{
				int val = SendMessage (LB_ADDFILE, 0, reinterpret_cast <LPARAM> (file.c_str ())) ;

				if (val == LB_ERR)
					throw Win::Exception (TEXT("Error, could not add a file to the list box")) ;

				return val ;
			}

			//-------------------------------------------------------------------------
			// Adds a string at the end of the list box (Unless LB_SORT is specified.)
			//
			// Return value: The 0 based index of the string or an error value.
			//
			// Parameters:
			//
			// const std::tstring str -> The string to be added.
			//-------------------------------------------------------------------------

			int Win::ListBoxHandle::AddString (const std::tstring str)
			{
				int val = SendMessage (LB_ADDSTRING, 0, reinterpret_cast <LPARAM> (str.c_str ())) ;

				if (val == LB_ERR || val == LB_ERRSPACE)
					throw Win::Exception (TEXT("Error, could not add a string to the list box")) ;

				return val ;
			}

			//-------------------------------------------------------------------------
			// Adds a string at the specified index of a list box.
			//
			// Return value: The 0 based index of the string or an error value.
			//
			// Parameters:
			//
			// const int index       -> The position where the string will be added.
			// const std::tstring str -> The string to be added.
			//-------------------------------------------------------------------------

			int Win::ListBoxHandle::InsertString (const int index, const std::tstring str)
			{
				int val = SendMessage (LB_INSERTSTRING, index,  reinterpret_cast<LPARAM> (str.c_str () )) ;

				if (val == LB_ERR || val == LB_ERRSPACE)
					throw Win::Exception (TEXT("Error, could not insert a file to the list box")) ;

				return val ;
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

			int Win::ListBoxHandle::DeleteString (const int index)
			{
				int val = SendMessage (LB_DELETESTRING, index, 0) ;

				if (val == LB_ERR)
					throw Win::ListBoxDeleteStringException () ;

				return val ;
			}

			//-------------------------------------------------------------------------
			// Finds a string in the list box that begins by the characters contained
			// in a specified string.
			//
			// Return value: The 0 based index of the string that was found or an error
			// value.
			//
			// Parameters:
			//
			// const int startIndex  -> The search start at this position.
			// const std::tstring str -> The method search for the string in the list
			//							box that begins by those characters.
			//-------------------------------------------------------------------------

			int Win::ListBoxHandle::FindString (const int startIndex, const std::tstring str) const 
			{
				int val = SendMessage (LB_FINDSTRING, startIndex, reinterpret_cast <LPARAM> (str.c_str ())) ;

				if (val == LB_ERR)
					throw Win::ListBoxFindStringException () ;

				return val ;
			}

			//-------------------------------------------------------------------------
			// Finds a string in the list box that exactly match specified string.
			//
			// Return value: The 0 based index of the string that was found or an error
			// value.
			//
			// Parameters:
			//
			// const int startIndex  -> The search start at this position.
			// const std::tstring str -> The string that must be search.
			//-------------------------------------------------------------------------

			int Win::ListBoxHandle::FindStringExact (const int startIndex, const std::tstring str) const 
			{
				int val = SendMessage (LB_FINDSTRINGEXACT, startIndex, reinterpret_cast<LPARAM> (str.c_str ())) ;

				if (val == LB_ERR)
					throw Win::ListBoxFindStringException () ;

				return val ;
			}

			//-------------------------------------------------------------------------
			// Obtains the number of string present in the list box.
			//
			// Return value: The number of string or an error value.
			//-------------------------------------------------------------------------			

			int Win::ListBoxHandle::GetCount () const 
			{
				int val = SendMessage (LB_GETCOUNT, 0, 0) ;

				if (val == LB_ERR)
					throw Win::Exception (TEXT("Error, could not get the number of item in the list box.")) ;

				return val ;
			}

			//-------------------------------------------------------------------------
			// Obtains the dimension of the rectangle bounding one of the list box item.
			//
			// Return value:   The bounding box of the item
			//-------------------------------------------------------------------------

			Win::Rect Win::ListBoxHandle::GetItemRect (const int index)
			{
				Win::Rect rect ;

				if (SendMessage (LB_GETITEMRECT, index,
					reinterpret_cast <LPARAM> (reinterpret_cast <RECT FAR *> (&rect))) == LB_ERR)
						throw Win::Exception (TEXT("Error, could not get the item's bounding box for the list box")) ;

				return rect ;
			}

					//-------------------------------------------------------------------------
			// Obtains the 32-bit value associated with an item of the list box
			//
			// Return value: The 32-bit value associated with the item.
			//
			// Parameters:
			//
			// const int index -> Index of the item.
			//-------------------------------------------------------------------------

			DWORD Win::ListBoxHandle::GetItemData (const int index) const 
			{
				int val = SendMessage (LB_GETITEMDATA, index, 0) ;

				if (val == LB_ERR)
					throw Win::Exception (TEXT("Error, could not get the item data from a list box.")) ;

				return val ;
			}

			//-------------------------------------------------------------------------
			// Obtains the height of one of the item of the list box.
			//
			// Return value: The height in pixel.
			//
			// Parameters:
			//
			// const int index -> Index of the string.
			//-------------------------------------------------------------------------

			int Win::ListBoxHandle::GetItemHeight (const int index) const 
			{
				int val = SendMessage (LB_GETITEMHEIGHT, index, 0) ;

				if (val == LB_ERR)
					throw Win::Exception (TEXT("Error, could not get the item height in the list box.")) ;

				return val ;
			}

			//-------------------------------------------------------------------------
			// Obtains the lenght of one of the string of the list box.
			//
			// Return value: The lenght in character.
			//
			// Parameters:
			//
			// const int index -> Index of the string.
			//-------------------------------------------------------------------------

			int Win::ListBoxHandle::GetTextLength (const int index) const 
			{
				int val = SendMessage (LB_GETTEXTLEN, index, 0) ;

				if (val == LB_ERR)
					throw Win::Exception (TEXT("Error, could not get the text lenght of an item in the list box.")) ;

				return val ;
			}

			//-------------------------------------------------------------------------
			// Pre-Allocates memory for storing items in the list box.
			//
			// Return value: The number of item for which memories was pre-allocated.
			//
			// Parameters:
			//
			// const int nbItem -> Number of items.
			// const int sizeInByte -> The total size in bytes.
			//-------------------------------------------------------------------------

			int Win::ListBoxHandle::SetInitStorage (const int nbItem, const int sizeInByte) const 
			{
				int val = SendMessage (LB_INITSTORAGE, nbItem, sizeInByte) ;

				if (val == LB_ERRSPACE)
					throw Win::Exception (TEXT("Error, could not set the initial storage for thelist box.")) ;

				return val ;
			}

			//-------------------------------------------------------------------------
			// Obtains the index of the currently selected string.
			//
			// Return value: The index of the currently selected string.
			//-------------------------------------------------------------------------

			int Win::SingleSelectionListBoxHandle::GetCurrentSel () const  
			{
				int val = SendMessage (LB_GETCURSEL, 0, 0) ;

				if (val == LB_ERR)
					throw Win::ListBoxSelectStringException () ;

				return val ;
			}

			//-------------------------------------------------------------------------
			// Sets the current selection.
			//
			// Parameters:
			//
			// const int index -> The index of the index that must be selected.
			//-------------------------------------------------------------------------

			int Win::SingleSelectionListBoxHandle::SelectString (const int indexStart, const std::tstring str) const 
			{
				int val = SendMessage (LB_SELECTSTRING, indexStart, reinterpret_cast <LPARAM> (str.c_str ())) ;

				if (val == LB_ERR)
					throw Win::ListBoxFindStringException () ;

				return val ;
			}

			//-------------------------------------------------------------------------
			// Obtains the index of all the selected items.
			//
			// Return value:  The number of obtained selections or an error value.
			//
			// Parameters:
			//
			// int * buf     -> Points on a buffer that will contain the index.
			// const int max -> Maximum number of entries 
			//-------------------------------------------------------------------------

			int Win::MultiSelectionListBoxHandle::GetSelItems (int * buf, const int max) const 
			{
				int val = SendMessage (LB_GETSELITEMS, max, reinterpret_cast <LPARAM> (buf)) ;

				if (val == LB_ERR)
					throw Win::Exception (TEXT("Error, could not get the item height in the list box.")) ;
				return val ;
			}
