//-----------------------------------------------------------------
//  This file contains classes that allow using list box controls.
//-----------------------------------------------------------------

#if !defined (WINLISTBOX_H)

	#define WINLISTBOX_H
	#include "useunicode.h"
	#include "wincontrol.h"

	namespace Win
	{ 

		//-------------------------------------------------------------------------
		// Exception that is thrown when a try to delete a string in a list box and it
		// is not there.
		//-------------------------------------------------------------------------

		class ListBoxDeleteStringException : public Win::Exception
		{
		public:
			ListBoxDeleteStringException ()
				: Win::Exception (TEXT("Error, the string could not be deleted, it is not in the list box"))
			{}
		} ;

		//-------------------------------------------------------------------------
		// Exception that is thrown when there is no string selected
		//-------------------------------------------------------------------------

		class ListBoxSelectStringException : public Win::Exception
		{
		public:
			ListBoxSelectStringException ()
				: Win::Exception (TEXT("Error, there is no selection"))
			{}
		} ;

		//-------------------------------------------------------------------------
		// Exception that is thrown when a try to find a string in a list box and it
		// is not there.
		//-------------------------------------------------------------------------

		class ListBoxFindStringException : public Win::Exception
		{
		public:
			ListBoxFindStringException ()
				: Win::Exception (TEXT("Error, the desired string is not in the list box."))
			{}
		} ;

		//-------------------------------------------------------------------------
		// Win::ListBoxHandle encapsulates a list box control handle.  Represent a 
		// list box control.  Inherit from Win::SimpleControl for basic 
		// functionality.  This class is not supposed to be used directly.
		//-------------------------------------------------------------------------

		class ListBoxHandle  : public SimpleControlHandle 
		{
		public: 


			void SetText (const std::tstring str) const
			{ 
				if (SendMessage (WM_SETTEXT, 0, reinterpret_cast <LPARAM> (str.c_str())) == LB_ERRSPACE )
					throw Win::Exception (TEXT("Error, could not set the text of the edit control")) ;
			}

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle to represent the
			// list box control through it's parent.
			// 
			// Parameters:
			//
			// const Win::Base parent -> Parent of the list box control.
			// const int id      -> Id of the static control.
			//-------------------------------------------------------------------------

			ListBoxHandle (const Win::Base winParent, const int id)
				: SimpleControlHandle (winParent, id)
			{}

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle directly
			// 
			// Parameters:
			//
			// const Win::Base win -> Handle of the list box control.
			//-------------------------------------------------------------------------

			ListBoxHandle (const Win::Base win = NULL)
				: SimpleControlHandle (win)
			{}

			//-------------------------------------------------------------------------
			// Initialize the handle and the id through the parent handle.
			//
			// Parameters:
			//
			// const Win::Base parent -> Parent of the control.
			// const int id      -> Id of the control.
			//-------------------------------------------------------------------------

			void Init (const Win::Base parent, const int id)
			{
				SimpleControlHandle::Init (parent, id);
			}

			//-------------------------------------------------------------------------
			// Destructor.  Empty the combo box.
			//-------------------------------------------------------------------------

			~ListBoxHandle ()
			{
				ResetContent () ;
			}

			int AddFile (const std::tstring file) ;
			int AddString (const std::tstring str) ;
			int InsertString (const int index, const std::tstring str) ;

			void ReplaceString (const int index, const std::tstring str)
			{
				DeleteString (index) ;
				InsertString (index, str) ;
			}

			int DeleteString (const int index) ;
			int FindString (const int startIndex, const std::tstring str) const ;
			int FindStringExact (const int startIndex, const std::tstring str) const ;
			int GetCount () const ;

			int GetHorizontalExtent () const 
			{
				return SendMessage (LB_GETHORIZONTALEXTENT, 0, 0) ;
			}

			DWORD GetItemData (const int index) const ;
			int GetItemHeight (const int index = 0) const ;

			//-------------------------------------------------------------------------
			// Obtains the dimension of the rectangle bounding one of the list box item.
			//
			// Parameters:
			//
			// const int index -> Index of the item.
			// Win::Rect & rect -> Will contain the dimensions of the item.
			//-------------------------------------------------------------------------

			void GetItemRect (const int index, Win::Rect & rect)
			{
				if (SendMessage (LB_GETITEMRECT, index,
					reinterpret_cast <LPARAM> (reinterpret_cast <RECT FAR *> (&rect))) == LB_ERR)
						throw Win::Exception (TEXT("Error, could not get the item's bounding box for the list box")) ;
			}

			Win::Rect GetItemRect (const int index) ;

			//-------------------------------------------------------------------------
			// Determines if an item is selected.
			//
			// Return value: True if the item is selected, else false.
			//
			// Parameters:
			//
			// const int index -> Index of the item.
			//-------------------------------------------------------------------------

			bool ItemIsSelected (const int index) const 
			{
				return SendMessage (LB_GETSEL, index, 0) > 0 ;
			}

			int GetTextLength (const int index) const ;

			std::tstring GetText (const int index) const ;

			//-------------------------------------------------------------------------
			// Obtains the index of the first visible item of the list box.
			//
			// Return value: The index of the first visible item.
			//-------------------------------------------------------------------------

			int GetFirstVisibleItemIndex () const 
			{
				return SendMessage (LB_GETTOPINDEX, 0, 0) ;
			}

			//-------------------------------------------------------------------------
			// Empty the combo box.
			//-------------------------------------------------------------------------

			void ResetContent ()
			{
				SendMessage (LB_RESETCONTENT, 0, 0) ;
			}

			int SetInitStorage (const int nbItem, const int sizeInByte) const ;

			//-------------------------------------------------------------------------
			// Sets the width of the columns of a list box with multiples columns.
			//
			// Parameters:
			//
			// const int width -> The new width.
			//-------------------------------------------------------------------------

			void SetColumnWidth (const int width)
			{
				SendMessage (LB_SETCOLUMNWIDTH, width, 0) ;
			}

			//-------------------------------------------------------------------------
			// Sets the count of string of a list boxs.
			//
			// Parameters:
			//
			// const int count -> The new count.
			//-------------------------------------------------------------------------

			void SetCount (const int count)
			{
				int val = SendMessage (LB_SETCOUNT, count, 0) ;

				if (val == LB_ERR || val == LB_ERRSPACE)
					throw Win::Exception (TEXT("Error, could not set the count of item in the list box.")) ;

			}

			//-------------------------------------------------------------------------
			// Sets the width by which the  list can be scrolled.
			//
			// Parameters:
			//
			// const int extent  -> The width by which the  list can be scrolled.
			//-------------------------------------------------------------------------

			void SetHorizontalExtent (const int extend)
			{
				SendMessage (LB_SETHORIZONTALEXTENT, extend, 0) ;
			}

			//-------------------------------------------------------------------------
			// Sets the 32-bit value associated with an item of the list box
			//
			// Parameters:
			//
			// const int index  -> Index of the item.
			// const DWORD data -> The 32-bit value associated with an item.
			//-------------------------------------------------------------------------

			void SetItemData (const int index, const DWORD data)
			{
				if (SendMessage (LB_SETITEMDATA, index, data) == LB_ERR)
					throw Win::Exception (TEXT("Error, could not set the data for an item in the list box")) ;

			}

			//-------------------------------------------------------------------------
			// Sets the height of an item of the list box.
			//
			// Return value: True if the method succeeded, else false.
			//
			// Parameters:
			//
			// const int index  -> Index of the item.
			// const int height -> New height of an item.
			//-------------------------------------------------------------------------

			void SetItemHeight (const int index, const int height)
			{
				if (SendMessage (LB_SETITEMHEIGHT, index, MAKELPARAM (height, 0) ) == LB_ERR)
					throw Win::Exception (TEXT("Error, could not set the height for an item in the list box")) ;
			}

			//-------------------------------------------------------------------------
			// Sets the index of the first visible item of the list box.
			//
			// Parameters:
			//
			// const int index  -> Index of the item.
			//-------------------------------------------------------------------------

			void SetFirstVisibleItem (const int top)
			{
				if (SendMessage (LB_SETTOPINDEX, top, 0) == LB_ERR)
					throw Win::Exception (TEXT("Error, could not set the first visible item in the list box")) ;

			}

			//-------------------------------------------------------------------------
			// Fills the list box with a directory listing.
			//
			// Parameters:
			//
			// const Win::Base dlg		-> The dialog box that contains the list box.
			// char * pathBuf			-> Path or filename.
			// const int idStatic       -> Id of the static control in which the name 
			//							   of the current directory.
			// const unsigned fileTypes -> Attributes of the files that must be 
			//							   displayed.
			//-------------------------------------------------------------------------

			void ListDirectory (std::tstring & pathBuf, const int idStatic = 0, const unsigned fileTypes = DDL_DIRECTORY | DDL_DRIVES)
			{
				if (!::DlgDirList (GetParent(), &pathBuf[0], GetId (), idStatic, fileTypes))
					throw Win::Exception (TEXT("Error, could not list the directories in the list box")) ;
			}

			//-------------------------------------------------------------------------
			// Fills the list box with a directory listing.
			//
			// Parameters:
			//
			// char * pathBuf			-> Path or filename.
			// const unsigned fileTypes -> Attributes of the files that must be 
			//							   displayed.
			//-------------------------------------------------------------------------

			void ListDirectory (std::tstring & pathBuf, const unsigned fileTypes = DDL_DIRECTORY | DDL_DRIVES)
			{
				int test = SendMessage (LB_DIR, fileTypes, reinterpret_cast <LPARAM> (&pathBuf[0])) ;

				if (test == LB_ERR || LB_ERRSPACE)
					throw Win::Exception (TEXT("Error, could not list the directories in the list box")) ;
			}
		} ;

		//-------------------------------------------------------------------------
		// Win::SingleSelectionListBoxHandle encapsulates a single selection listBox
		// control handle.  Represents a  list box control.  Inherit from
		// Win::ListBoxHandle for basic functionality.  
		//-------------------------------------------------------------------------

		class SingleSelectionListBoxHandle : public ListBoxHandle
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle to represent the
			// list box control through it's parent.
			// 
			// Parameters:
			//
			// const Win::Base parent -> Parent of the list box control.
			// const int id      -> Id of the static control.
			//-------------------------------------------------------------------------

			SingleSelectionListBoxHandle (const Win::Base winParent, const int id)
				: ListBoxHandle (winParent, id)
			{}

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle directly
			// 
			// Parameters:
			//
			// const Win::Base win -> Handle of the list box control.
			//-------------------------------------------------------------------------

			SingleSelectionListBoxHandle (const Win::Base win = NULL)
				: ListBoxHandle (win)
			{}

			//-------------------------------------------------------------------------
			// Initialize the handle and the id through the parent handle.
			//
			// Parameters:
			//
			// const Win::Base parent -> Parent of the control.
			// const int id      -> Id of the control.
			//-------------------------------------------------------------------------

			void Init (const Win::Base parent, const int id)
			{
				ListBoxHandle::Init (parent, id);
			}

			int GetCurrentSel () const ;
			int SelectString (const int indexStart, const std::tstring str) const ;

			//-------------------------------------------------------------------------
			// Sets the current selection.
			//
			// Parameters:
			//
			// const int index -> The index of the index that must be selected.
			//-------------------------------------------------------------------------

			void SetSelection (const int index) const 
			{
				if (SendMessage (LB_SETCURSEL, index, 0) == LB_ERR)
					throw Win::Exception (TEXT("Error, could not set the selection for the list box.")) ;
			}

			//-------------------------------------------------------------------------
			// Removes the selection.
			//-------------------------------------------------------------------------

			void NoSelection () const 
			{
				SendMessage (LB_SETCURSEL, -1, 0) ;
			}

			//-------------------------------------------------------------------------
			// Obtains the currently selected item from a list box filled by a 
			// directory listing.
			//
			// Parameters:
			//
			// const Win::Base dlg		-> The dialog box that contains the list box.
			// char * pathBuf			-> Will receive the path.
			// const int bufLen         -> Length in characters of the path.
			//-----------------------------------------------------------------------

			void GetSelectedPath (std::tstring & pathBuf) const 
			{
				if (!DlgDirSelectEx (::GetParent (_h), &pathBuf[0], pathBuf.length(), GetId ()))
					throw (Win::Exception (TEXT("Error, could not obtain the selected path from the list box")));
			}	
		} ;

		//-------------------------------------------------------------------------
		// Win::MultiSelectionListBoxHandle encapsulates a multi selection listBox
		// control handle.  Represents a  list box control.  Inherit from
		// Win::ListBoxHandle for basic functionality.  
		//-------------------------------------------------------------------------

		class MultiSelectionListBoxHandle : public ListBoxHandle
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle to represent the
			// list box control through it's parent.
			// 
			// Parameters:
			//
			// const Win::Base parent -> Parent of the list box control.
			// const int id      -> Id of the static control.
			//-------------------------------------------------------------------------

			MultiSelectionListBoxHandle (const Win::Base winParent, const int id)
				: ListBoxHandle (winParent, id)
			{}

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle directly
			// 
			// Parameters:
			//
			// const Win::Base win -> Handle of the list box control.
			//-------------------------------------------------------------------------

			MultiSelectionListBoxHandle (const Win::Base win = NULL)
				: ListBoxHandle (win)
			{}

			//-------------------------------------------------------------------------
			// Initialize the handle and the id through the parent handle.
			//
			// Parameters:
			//
			// const Win::Base parent -> Parent of the control.
			// const int id      -> Id of the control.
			//-------------------------------------------------------------------------

			void Init (const Win::Base parent, const int id)
			{
				ListBoxHandle::Init (parent, id);
			}

			//-------------------------------------------------------------------------
			// Obtains the index of the item from which the selection starts.
			//
			// Return value:  The index of the item.
			//-------------------------------------------------------------------------

			int GetAnchorItemIndex () const 
			{
				return SendMessage (LB_GETANCHORINDEX, 0, 0) ;
			}

			//-------------------------------------------------------------------------
			// Obtains the index of the item fthat has the focus rectangle.
			//
			// Return value:  The index of the item.
			//-------------------------------------------------------------------------

			int GetCaretIndex () const 
			{
				return SendMessage (LB_GETCARETINDEX, 0, 0) ;
			}

			//-------------------------------------------------------------------------
			// Obtains the number of selections in the listbox.
			//
			// Return value:  The number of selection.
			//-------------------------------------------------------------------------

			int GetSelCount () const 
			{
				return SendMessage (LB_GETSELCOUNT, 0, 0) ;
			}

			int GetSelItems (int * buf, const int max) const ;

			//-------------------------------------------------------------------------
			// Sets the index of the item from which the selection starts.
			//
			// Parameters:
			//
			// const int index -> The index of the item.
			//-------------------------------------------------------------------------

			void SetAnchorItemIndex (const int index)
			{
				if (SendMessage (LB_SETANCHORINDEX, index, 0) == LB_ERR)
					throw Win::Exception (TEXT("Error, could not set the anchor index for the multi selection list box"));
			}

			//-------------------------------------------------------------------------
			// Sets the index of the item of that has the focus rectangle.
			//
			// Parameters:
			//
			// const int index   -> The index of the item.
			// const bool scroll -> If false, the item is made completely visible.  If 
			//						true the is made at least partially visible
			//-------------------------------------------------------------------------

			void SetCaretIndex (const int index, const bool scroll = false)
			{
				if (SendMessage (LB_SETCARETINDEX, index, MAKELPARAM (scroll, 0) ) == LB_ERR)
					throw Win::Exception (TEXT("Error, could not set the caret index for the multi selection list box"));

			}

			//-------------------------------------------------------------------------
			// Selects a range of items.
			//
			// Parameters:
			//
			// const int first   -> Index of the first item.
			// const int last    -> Index of the last item.
			// const bool select -> If true the items are selected. if false the items
			//						are unselected.
			//-------------------------------------------------------------------------

			void SelectlItemRange (const int first, const int last, const bool select = true)
			{
				if (SendMessage (LB_SELITEMRANGE, select, MAKELPARAM (first, last) ) == LB_ERR)
					throw Win::Exception (TEXT("Error, could not select the item range for the multi selection list box"));

			}

			//-------------------------------------------------------------------------
			// Selects a string in a multi selection list box.
			//
			// Parameters:
			//
			// const int index   -> The index of the string.
			// const bool select -> If true the items are selected. if false the items
			//						are unselected.
			//-------------------------------------------------------------------------

			void SetSelection (const int index, const bool select = true)
			{
				if (SendMessage (LB_SETSEL, select, index) == LB_ERR)
					throw Win::Exception (TEXT("Error, could not select a string for the multi selection list box"));
			}

		} ;

		//-------------------------------------------------------------------------
		// Win::ListBoxHandleCreator allows to create a list box control.
		// Inherit from Win::ListBoxHandleCreator for basic functionality.
		//-------------------------------------------------------------------------	

		class ListBoxCreator : public ControlCreator
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Creates a list box control with the functionality of 
			// Win::ControlCreator.
			//-------------------------------------------------------------------------

			ListBoxCreator (const Win::Base parent, const int id)
				: ControlCreator (std::tstring (TEXT("listbox")), parent, id)
			{}

			//-------------------------------------------------------------------------
			// Creates a new listbox control.
			// 
			// Return value:  The listbox control handle.
			//
			// Parameters:
			//
			// const std::tstring title -> The title of the listbox control.
			//-------------------------------------------------------------------------

			Win::ListBoxHandle Create (const std::tstring title) const
			{
				return ChildCreator::Create (title) ;
			}

			//-------------------------------------------------------------------------
			// The following methods all serve the same purpose.  They set one of the 
			// style of the future list box control.
			//-------------------------------------------------------------------------

			void SetDisableNoScrollStyle   () {_style |= LBS_DISABLENOSCROLL ;}
			void SetExtendedSelStyle       () {_style |= LBS_EXTENDEDSEL ;}
			void SetHasStringStyle         () {_style |= LBS_HASSTRINGS ;}
			void SetMultiColumnStyle       () {_style |= LBS_MULTICOLUMN ;}
			void SetMultipleSelStyle       () {_style |= LBS_MULTIPLESEL ;}
			void SetNoDataStyle            () {_style |= LBS_NODATA ;}
			void SetNoIntegralHeight       () {_style |= LBS_NOINTEGRALHEIGHT ;}
			void SetNoRedrawStyle          () {_style |= LBS_NOREDRAW ;}
			void SetNoSelStyle             () {_style |= LBS_NOSEL ;}
			void SetNotifyStyle            () {_style |= LBS_NOTIFY ;}
			void SetOwnerDrawFixedStyle    () {_style |= LBS_OWNERDRAWFIXED;}
			void SetOnwerDrawVariableStyle () {_style |= LBS_OWNERDRAWVARIABLE ;}
			void SetSortStyle              () {_style |= LBS_SORT ;}
			void SetStandardStyle          () {_style |= LBS_STANDARD ;}
			void SetUseTabStopsStyle        () {_style |= LBS_USETABSTOPS ;}
			void SetWandKeyboardInputStyle () {_style |= LBS_WANTKEYBOARDINPUT ;}
			
		} ;
	}

#endif