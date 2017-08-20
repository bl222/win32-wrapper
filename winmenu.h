//-----------------------------------------------------------------
//  This file contains classes that allow using menus.
//-----------------------------------------------------------------

#if !defined (WINMENU_H) 

	#define WINMENU_H
	#include "useunicode.h"
	#include "winunicodehelper.h"
	#include "winexception.h"
	#include "windrawingtool.h"

namespace Win
{
	class Base ;
	namespace dow
	{
		class Handle;
	}

	namespace Menu
	{
		namespace PopUp
		{
			class Handle ;
		}

		//-----------------------------------------------------------------
		// Win::Menu::Handle gives access to a menu handle but does not
		// own it.  This mean that when the object is destroyed, the menu
		// is not.  This is especially useful to modified a menu bar that 
		// is attached to a window without removing it from the window.
		//-----------------------------------------------------------------

		class Handle : public Sys::Handle <HMENU>
		{
		public:

			//-----------------------------------------------------------------
			// Constructor.
			//-----------------------------------------------------------------

			Handle (const HMENU menu = NULL)
				: Sys::Handle <HMENU> (menu)
			{}

			//-----------------------------------------------------------------
			// Checks one menu item and unchecks the other item of the same
			// group.
			//
			// Parameters:
			//
			// const UINT first -> Position of the first item of the group.
			// const UINT last  -> Position of the last item of the group.
			// const UINT check -> Position of the item to be checked.
			//-----------------------------------------------------------------

			void CheckRadioItemByPosition (const UINT first, const UINT last, const UINT check) const 
			{
				if (::CheckMenuRadioItem (_h, first, last, check, MF_BYPOSITION) == 0)
					throw Win::Exception (TEXT("Error, Could not check the menu as a radio item")) ;			
			}

			//-----------------------------------------------------------------
			// Checks one menu item and unchecks the other item of the same
			// group.
			//
			// Parameters:
			//
			// const UINT first -> Id of the first item of the group.
			// const UINT last  -> Id of the last item of the group.
			// const UINT check -> Id of the item to be checked.
			//-----------------------------------------------------------------

			void CheckRadioItemByCommand (const UINT idFirst, const UINT idLast, const UINT idCheck) const 
			{
				if (::CheckMenuRadioItem (_h, idFirst, idLast, idCheck, MF_BYCOMMAND) == 0)
					throw Win::Exception (TEXT("Error, Could not check the menu as a radio item")) ;
			}

			//-----------------------------------------------------------------
			// Enables the menu item at a specified position.
			//
			// const int pos -> Position of the item.
			//-----------------------------------------------------------------

			void EnableItemByPosition (const int pos) const 
			{
				if (::EnableMenuItem (_h, pos, MF_BYPOSITION | MF_ENABLED) == 0xFFFFFFFF)
					throw Win::Exception (TEXT("Error, Could not enable the menu item")) ;
			}

			//-----------------------------------------------------------------
			// Enables the menu item identified by a specified id.
			//
			// Parameters:
			//
			// const int id -> Id of the item.
			//-----------------------------------------------------------------

			void EnableItemByCommand (const int id) const 
			{
				if (::EnableMenuItem (_h, id, MF_BYCOMMAND | MF_ENABLED) == 0xFFFFFFFF)
					throw Win::Exception (TEXT("Error, Could not enable the menu item")) ;
			}

			//-----------------------------------------------------------------
			// Disables the menu item at a specified position.
			//
			// Parameters:
			//
			// const int pos -> Position of the item.
			//-----------------------------------------------------------------

			void DisableItemByPosition (const int pos) const 
			{
				if (::EnableMenuItem (_h, pos, MF_BYPOSITION | MF_DISABLED) == 0xFFFFFFFF)
					throw Win::Exception (TEXT("Error, Could not disable the menu item")) ;
			}

			//-----------------------------------------------------------------
			// Disables the menu item identified by a specified id.
			//
			// Parameters:
			//
			// const int id -> Id of the item.
			//-----------------------------------------------------------------

			void DisableItemByCommand (const int id) const 
			{
				if (::EnableMenuItem (_h, id, MF_BYCOMMAND | MF_DISABLED) == 0xFFFFFFFF)
					throw Win::Exception (TEXT("Error, Could not disable the menu item")) ;
			}

			//-----------------------------------------------------------------
			// Grays the menu item at a specified position.
			//
			// Parameters:
			//
			// const int pos -> Position of the item.
			//-----------------------------------------------------------------

			void GrayItemByPosition (const int pos) const 
			{
				if (::EnableMenuItem (_h, pos, MF_BYPOSITION | MF_GRAYED) == 0xFFFFFFFF)
					throw Win::Exception (TEXT("Error, Could not gray the menu item")) ;
			}

			//-----------------------------------------------------------------
			// Grays the menu item identified by a specified id.
			//
			// Parameters:
			//
			// const int id -> Id of the item.
			//-----------------------------------------------------------------

			void GrayItemByCommand (const int id) const 
			{
				if (::EnableMenuItem (_h, id, MF_BYCOMMAND | MF_GRAYED) == 0xFFFFFFFF)
					throw Win::Exception (TEXT("Error, Could not gray the menu item")) ;
			}

			//-----------------------------------------------------------------
			// Checks the menu item at a specified position.
			//
			// Parameters:
			//
			// const int pos -> Position of the item.
			//-----------------------------------------------------------------

			void CheckItemByPosition (const int pos) const
			{
				if (::CheckMenuItem (_h, pos, MF_BYPOSITION | MF_CHECKED)  == 0xFFFFFFFF)
					throw Win::Exception (TEXT("Error, Could not check the menu item")) ;
			}

			//-----------------------------------------------------------------
			// Checks the menu item identified by a specified id.
			//
			// Parameters:
			//
			// const int id -> Id of the item.
			//-----------------------------------------------------------------

			void CheckItemByCommand (const int id) const 
			{
				if (::CheckMenuItem (_h, id, MF_BYCOMMAND | MF_CHECKED)  == 0xFFFFFFFF)
					throw Win::Exception (TEXT("Error, Could not check the menu item")) ;
			}

			//-----------------------------------------------------------------
			// Unchecks the menu item at a specified position.
			//
			// Parameters:
			//
			// const int pos -> Position of the item.
			//-----------------------------------------------------------------

			void UnCheckItemByPosition (const int pos) const 
			{
				if (::CheckMenuItem (_h, pos, MF_BYPOSITION | MF_UNCHECKED)  == 0xFFFFFFFF)
					throw Win::Exception (TEXT("Error, Could not uncheck the menu item")) ;
			}

			//-----------------------------------------------------------------
			// Unchecks the menu item identified by a specified id.
			//
			// Parameters:
			//
			// const int id -> Id of the item.
			//-----------------------------------------------------------------

			void UnCheckItemByCommand (const int id) const 
			{
				if (::CheckMenuItem (_h, id, MF_BYCOMMAND | MF_UNCHECKED)   == 0xFFFFFFFF)
					throw Win::Exception (TEXT("Error, Could not uncheck the menu item")) ;
			}

			UINT GetDefaultItemCommand (const UINT flags) const ;
			UINT GetDefaultItemPosition (const UINT flags) const ;

			//-----------------------------------------------------------------
			// Obtains the number of items of a menu.
			//
			// Return value:  Number of items.
			//-----------------------------------------------------------------

			int GetItemCount () const 
			{
				return ::GetMenuItemCount (_h) ;
			}

			UINT GetItemID (const int pos) const ;
			
			//-----------------------------------------------------------------
			// Sets the the default menu item by command (id).
			//
			// Parameters:
			//
			// const int id -> Id of the new default item.
			//-----------------------------------------------------------------

			void SetDefaultItemByCommand (const int id) const 
			{
				if (::SetMenuDefaultItem (_h, id, FALSE) == 0)
					throw Win::Exception (TEXT("Error, Could not set the default item the menu item")) ;
			}

			//-----------------------------------------------------------------
			// Sets the the default menu item by position.
			//
			// Parameters:
			//
			// const int id -> Position of the new default item.
			//-----------------------------------------------------------------

			void SetDefaultItemByPosition (const int pos) const 
			{
				if (::SetMenuDefaultItem (_h, pos, TRUE) == 0)
					throw Win::Exception (TEXT("Error, Could not set the default item the menu item")) ;
			}

			Win::Menu::PopUp::Handle GetHandleSubMenu (const int pos) const ;

			//--------------------------------------------------------------------
			// Determines if the Win::Handle::Menu is valid
			//
			// Return value:  True if the object is valid, else false.  
			//--------------------------------------------------------------------

			bool IsValid () const 
			{
				return _h != 0 ;
			}

		} ;

			//------------------------------------------------------------------
			// Win::Menu::Disposal is used to destroy a menu
			// Used only internaly by winlib, not by users.
			//------------------------------------------------------------------

			struct Disposal
			{
				static void Dispose (HMENU h)
				{
					::DestroyMenu (h) ;
				}
			} ;

		namespace PopUp
		{
			//------------------------------------------------------------------
			// Win::Menu::PopUp::Handle gives access to a pop-up menu, but does
			// not own it.
			//------------------------------------------------------------------

			class Handle : public Win::Menu::Handle
			{
			public:

				//-----------------------------------------------------------------
				// Constructor.  
				//-----------------------------------------------------------------

				Handle (const HMENU menu = NULL)
					 : Win::Menu::Handle (menu)
				{}

				//--------------------------------------------------------------------
				// Displays the popup menu at a specified position.
				//
				// Parameters:
				// 
				// const HWND hwnd -> Window displaing the popup menu.
				// const int x     -> X coordinate of the position where the menu will
				//					  be displayed.
				// const int y     -> Y coordinate of the position where the menu will
				//					  be displayed.
				//--------------------------------------------------------------------
				
				void TrackPopUp (const HWND hwnd, const int x, const int y) const 
				{
					::TrackPopupMenuEx (_h, TPM_CENTERALIGN, x, y, hwnd, 0) ;
				}
			} ;

			typedef Sys::StrongHandle <Win::Menu::PopUp::Handle, Win::Menu::Disposal> StrongHandle ; // Owns a PopUp menu
		}

		//-----------------------------------------------------------------
		// Win::Menu::Modifier is used to modify a menu     
		//-----------------------------------------------------------------

		class Modifier
		{
		public:

			//-----------------------------------------------------------------
			// Constructor.      
			//-----------------------------------------------------------------

			Modifier (Win::Menu::Handle h)
				: _h (h)
			{
				if (_h == NULL)
					throw Win::Exception (TEXT("Error, trying to create or modify a NULL menu")) ;
			}

			//-----------------------------------------------------------------
			// Deletes the menu item at a specified position.
			//
			// Parameters:
			//
			// const int pos -> Position of the item.
			//-----------------------------------------------------------------

			void DeleteItemByPosition (const int pos) const 
			{
				if (::DeleteMenu (_h, pos, MF_BYPOSITION) == 0)
					throw Win::Exception (TEXT("Error, Could not delete the menu item")) ;
			}

			//-----------------------------------------------------------------
			// Deletes the menu item identified by a specified id.
			//
			// Parameters:
			//
			// const int id -> Id of the item.
			//-----------------------------------------------------------------

			void DeleteItemByCommand (const int id) const 
			{
				if (::DeleteMenu (_h, id, MF_BYCOMMAND) == 0)
					throw Win::Exception (TEXT("Error, Could not delete the menu item")) ;
			}

			//-----------------------------------------------------------------
			// Adds a menu item at the end of the menu.
			//
			// Parameters:
			//
			// const int id               -> Id of the item.
			// const std::tstring itemName -> Text of the item.
			//-----------------------------------------------------------------

			void AppendItem (const int id, const std::tstring itemName) const 
			{
				if (::AppendMenu (_h, MF_STRING, id, itemName.c_str ()) == 0)
					throw Win::Exception (TEXT("Error, Could not insert an item.")) ;	
			}

			void AppendMenu (Win::Menu::PopUp::StrongHandle menu, const std::tstring menuName) const ;

			//-----------------------------------------------------------------
			// Adds a separator at the end of the menu.
			//
			// Return value:  True if the method succeed, else false.
			//-----------------------------------------------------------------

			void AppendSeparator () const
			{
				if (::AppendMenu (_h, MF_SEPARATOR, 0, 0) == 0)
					throw Win::Exception (TEXT("Error, Could not insert a separator.")) ;	
			}

			//-----------------------------------------------------------------
			// Adds a bitmap menu at the end of the menu.
			//
			// Parameters:
			//
			// const int id         -> Id of the item.
			// const Win::Bitmap::DDB::Handle bitmap -> Handle of the bitmap.
			//-----------------------------------------------------------------

			void AppendBitmap (const int id, const Win::Bitmap::DDB::Handle bitmap) const
			{
				if (::AppendMenu (_h, MF_BITMAP, id, reinterpret_cast <const TCHAR *> (static_cast <HBITMAP>(bitmap))) == 0)
					throw Win::Exception (TEXT("Error, Could not insert a bitmap.")) ;	
			}

			//-----------------------------------------------------------------
			// Adds a menu item at a specified position of the menu.
			//
			// Parameters:
			//
			// const int pos              -> The desired item.        
			// const int id               -> Id of the item.
			// const std::tstring itemName -> Name of the item.
			//-----------------------------------------------------------------

			void InsertItemByPosition (const int pos, const int id, const std::tstring itemName) const 
			{
				if (::InsertMenu (_h, pos, MF_BYPOSITION | MF_STRING, id, itemName.c_str ()) == 0)
					throw Win::Exception (TEXT("Error, Could not insert an item.")) ;	
			}

			//-----------------------------------------------------------------
			// Adds a bitmap at a specified position of the menu.
			//
			// Parameters:
			//
			// const int pos        -> The desired item.        
			// const int id         -> Id of the item.
			// const Win::Bitmap::DDB::Handle bitmap -> Handle of a bitmap.
			//-----------------------------------------------------------------

			void InsertBitmapByPosition (const int pos, const int id, const Win::Bitmap::DDB::Handle bitmap) const 
			{
				if (::InsertMenu (_h, pos, MF_BYPOSITION | MF_BITMAP, id, reinterpret_cast <const TCHAR *> (static_cast <HBITMAP> (bitmap))) == 0)
					throw Win::Exception (TEXT("Error, Could not insert a bitmap.")) ;	
			}

			void InsertMenuByPosition (const int pos, Win::Menu::PopUp::StrongHandle menu, const std::tstring menuName) const ;

			//-----------------------------------------------------------------
			// Adds a seperator at a specified position of the menu.
			//
			// Parameters:
			//
			// const int pos        -> The desired item.        
			//-----------------------------------------------------------------

			void InsertSeparatorByPosition (const int pos) const 
			{
				if (::InsertMenu (_h, pos, MF_BYPOSITION | MF_SEPARATOR, 0, 0) == 0)
					throw Win::Exception (TEXT("Error, Could not insert a separator.")) ;	
			}

			//-----------------------------------------------------------------
			// Adds a menu item after the item having the specified id..
			//
			// Parameters:
			//
			// const int idBefore         -> Id of the preceding item.        
			// const int id               -> Id of the item.
			// const std::tstring itemName -> Name of the item.
			//-----------------------------------------------------------------

			void InsertItemByCommand (const int idBefore, const int id, const std::tstring itemName)
			{
				if (::InsertMenu (_h, idBefore, MF_BYCOMMAND | MF_STRING, id, itemName.c_str ()) == 0)
					throw Win::Exception (TEXT("Error, Could not insert a item.") );	
			}

			//-----------------------------------------------------------------
			// Adds a bitmap after the item having the specified id..
			//
			// Parameters:
			//
			// const int idBefore   -> Id of the preceding item.           
			// const int id         -> Id of the item.
			// const Win::Bitmap::DDB::Handle bitmap -> Handle of the bitmap
			//---------Win::Bitmap::DDB::Handle--------------------------------------------------------

			void InsertBitmapByCommand (const int idBefore, const int id, const Win::Bitmap::DDB::Handle bitmap) const 
			{
				if (::InsertMenu (_h, idBefore, MF_BYCOMMAND | MF_BITMAP, id, reinterpret_cast <const TCHAR *> (static_cast <HBITMAP> (bitmap))) == 0)
					throw Win::Exception (TEXT("Error, Could not insert a bitmap.")) ;	
			}

			void InsertMenuByCommand (const int idBefore, Win::Menu::PopUp::StrongHandle menu, const std::tstring menuName) const;

			//-----------------------------------------------------------------
			// Adds a separator after the item having the specified id..
			//
			// Parameters:
			//
			// const int idBefore -> Id of the preceding item.       
			//-----------------------------------------------------------------

			void InsertSeparatorByCommand (const int idBefore) const  
			{
				if (::InsertMenu (_h, idBefore, MF_BYCOMMAND | MF_SEPARATOR, 0, 0) == 0)
					throw Win::Exception (TEXT("Error, Could not insert a separator.")) ;					
			}

			Win::Menu::PopUp::StrongHandle RemoveSubMenu (const int pos) const ;

		protected:

			Win::Menu::Handle _h ; 
		} ;

		namespace PopUp
		{
			//-----------------------------------------------------------------
			// Win::Menu::PopUp::Creator is used to create a pop up menu.     
			//-----------------------------------------------------------------

			class Creator : public Win::Menu::Modifier
			{
			public:
				Creator ()
					: Win::Menu::Modifier (::CreatePopupMenu ())
				{}
				
				~Creator ()
				{
					::DestroyMenu (_h) ;
				}

				Win::Menu::PopUp::StrongHandle Create () ;
			} ;
		}

		namespace Bar
		{

			//------------------------------------------------------------------
			// Win::Menu::Bar::Handle gives access to a menu bar, but does not
			// own it.
			//------------------------------------------------------------------

			class Handle : public Win::Menu::Handle
			{

			public:

				//-----------------------------------------------------------------
				// Constructor.  Creates the object with a menu handle.
				//
				// Parameters:
				//
				// const HMENU menu -> Used to create the object.
				//-----------------------------------------------------------------

				Handle (const HMENU menu)
					: Win::Menu::Handle (menu)
				{}


			} ;

			typedef Sys::StrongHandle <Win::Menu::Handle, Win::Menu::Disposal> StrongHandle ; // Owns the menu bar

			//-----------------------------------------------------------------
			// Win::Menu::Bar::Creator is used to create a menu bar.
			//-----------------------------------------------------------------

			class Creator : public Win::Menu::Modifier
			{
			public:

				Creator ()
					: Win::Menu::Modifier (::CreateMenu ())
				{}
				
				~Creator ()
				{
					::DestroyMenu (_h) ;
				}

				Win::Menu::Bar::StrongHandle Create () ;
			} ;

			//-----------------------------------------------------------------
			// Win::Menu::Loader is use to load a menu bar resource.    
			//-----------------------------------------------------------------

			class Loader
			{
			public:

				Loader (const HINSTANCE hInstance = NULL)
					: _hInstance (hInstance)
				{}

				void SetInstance (const HINSTANCE hInstance)
				{
					_hInstance = hInstance ;
				}

				Win::Menu::Bar::StrongHandle LoadResource (const int id) ;
				Win::Menu::Bar::StrongHandle LoadResource (const std::tstring name) ;

				static Win::Menu::Bar::StrongHandle LoadResource (HINSTANCE hInstance, const int id) ;
				static Win::Menu::Bar::StrongHandle LoadResource (HINSTANCE hInstance, const std::tstring name) ;

			private:

				HINSTANCE _hInstance ;
			} ;
		}

		namespace System
		{
			//------------------------------------------------------------------
			// Win::Menu::System is used to gain access to the system menu.
			// Inherits from Win::Menu::Handle for basic functionality.
			//------------------------------------------------------------------


			class Handle : public Win::Menu::Handle
			{
			public:

				Handle (const Win::Base hwnd) ;
				static void RestoreSystemMenu (const Win::Base hwnd) ;

			} ;
		}
	}
}

#endif