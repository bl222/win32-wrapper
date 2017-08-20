#include "winmenu.h"
#include "win.h"

//-----------------------------------------------------------------
// Obtains the id of the default menu item.
//
// Return value:  The id of the default item.
//
// Parameters:
//
// const UINT flags -> Specify how the search is done.
//-----------------------------------------------------------------

UINT Win::Menu::Handle::GetDefaultItemCommand (const UINT flags) const 
{
	UINT val = ::GetMenuDefaultItem (_h, FALSE, flags) ;

	if (val == -1) 
		throw Win::Exception (TEXT("Error, Could not get the default menu item")) ;

	return val ;
}

//-----------------------------------------------------------------
// Obtains the position of the default menu item.
//
// Return value:  The position of the default item.
//
// Parameters:
//
// const UINT flags -> Specify how the search is done.
//-----------------------------------------------------------------

UINT Win::Menu::Handle::GetDefaultItemPosition (const UINT flags) const 
{
	UINT val = ::GetMenuDefaultItem (_h, TRUE, flags) ;

	if (val == -1) 
		throw Win::Exception (TEXT("Error, Could not get the default menu item")) ;

	return val ;
}


//-----------------------------------------------------------------
// Obtains the id of an item.
//
// Return value:  The id.
//
// Parameters:
//
// const int pos -> Position of the item.
//-----------------------------------------------------------------

UINT Win::Menu::Handle::GetItemID (const int pos) const 
{
	UINT id = ::GetMenuItemID (_h, pos) ;

	if (id == 0xFFFFFFFF)
		throw Win::Exception (TEXT("Error, Could not get the id of the menu item")) ;

	return id ;
}

//-----------------------------------------------------------------
// Adds a popup menu at the end of the menu.
//
// Parameters:
//
// const int id            -> Id of the item.
// Win::Menu::PopUp & menu -> The popup menu.
//-----------------------------------------------------------------

void Win::Menu::Modifier::AppendMenu (Win::Menu::PopUp::StrongHandle menu, const std::tstring menuName) const
{

	if (::AppendMenu (_h, MF_POPUP, reinterpret_cast <unsigned int> (static_cast <HMENU> (menu.Release ())) , menuName.c_str()) == 0)
		throw Win::Exception (TEXT("Error, could not append a popup menu")) ; 

}

//-----------------------------------------------------------------
// Adds a popup menu at a specified position of the menu.
//
// Parameters:
//
// const int pos              -> The desired item.        
// Win::Menu::PopUp & menu    -> The popup menu.
// const std::tstring menuName -> Name of the menu.
//-----------------------------------------------------------------

void Win::Menu::Modifier::InsertMenuByPosition (const int pos, Win::Menu::PopUp::StrongHandle menu, const std::tstring menuName) const
{
	if (::InsertMenu (_h, pos, MF_POPUP | MF_BYPOSITION, reinterpret_cast <unsigned int> (static_cast <HMENU> (menu.Release ())), menuName.c_str ()) == 0)
		throw Win::Exception (TEXT("Error, could not insert a popup menu")) ; 
}

//-----------------------------------------------------------------
// Adds a popup menu after the item having a specified id of the
// menu.
//
// Parameters:
//
// const int idBefore         -> The desired item.        
// Win::Menu::PopUp & menu    -> The popup menu.
// const std::tstring menuName -> Name of the menu.
//-----------------------------------------------------------------

void Win::Menu::Modifier::InsertMenuByCommand (const int idBefore, Win::Menu::PopUp::StrongHandle menu, const std::tstring menuName) const
{
	if (::InsertMenu (_h, idBefore, MF_POPUP | MF_BYCOMMAND, reinterpret_cast <unsigned int> (static_cast <HMENU> (menu.Release ())), menuName.c_str ()) == 0)
		throw Win::Exception (TEXT("Error, could not insert a popup menu")) ; 
}

Win::Menu::PopUp::Handle Win::Menu::Handle::GetHandleSubMenu (const int pos) const
{
	return ::GetSubMenu (_h, pos) ;
}

//--------------------------------------------------------------------
// Removes one of the submenu of the menu.
//
// Return value: The submenuthat was removed.
//--------------------------------------------------------------------

Win::Menu::PopUp::StrongHandle Win::Menu::Modifier::RemoveSubMenu (const int pos) const 
{
	HMENU menu ;

	menu = ::GetSubMenu (_h, pos) ;
	
	if (::RemoveMenu(_h, pos, MF_BYPOSITION) == 0)
		throw Win::Exception (TEXT("Error, could not remove the submenu")) ;

	return Win::Menu::PopUp::StrongHandle (menu) ;
}

//---------------------------------------------------
// Creates a Popup menu.
//
// Return Value:  A StrongHandle on the menu that was
//				  created.
//---------------------------------------------------

Win::Menu::PopUp::StrongHandle Win::Menu::PopUp::Creator::Create ()
{
	HMENU h = _h ;

	_h = ::CreatePopupMenu () ;

	if (_h == NULL)
		throw Win::Exception (TEXT("Error, could not create a menu")) ;

	return Win::Menu::PopUp::StrongHandle (h) ;
}

//---------------------------------------------------
// Creates a menu bar
//
// Return Value:  A StrongHandle on the menu that was
//				  created.
//---------------------------------------------------

Win::Menu::Bar::StrongHandle Win::Menu::Bar::Creator::Create ()
{
	HMENU h = _h ;

	_h = ::CreateMenu () ;

	if (_h == NULL)
		throw Win::Exception (TEXT("Error, could not create a menu")) ;

	return Win::Menu::Bar::StrongHandle (h) ;
}

//---------------------------------------------------
// Loads a Menu bar by id.
//
// Return Value:  A StrongHandle on the menu that was
//				  load.
//
// Parameters:
//
// const int id -> Id of the menu.
//---------------------------------------------------

Win::Menu::Bar::StrongHandle Win::Menu::Bar::Loader::LoadResource (const int id)
{
	HMENU h = ::LoadMenu (_hInstance, MAKEINTRESOURCE (id)) ;

	if (h == NULL)
		throw (TEXT("Error, could not load a menu resource")) ;

	return Win::Menu::Bar::StrongHandle (h) ;
}

//---------------------------------------------------
// Loads a Menu bar by name.
//
// Return Value:  A StrongHandle on the menu that was
//				  load.
//
// Parameters:
//
// const std::tstring name -> Name of the menu.
//---------------------------------------------------

Win::Menu::Bar::StrongHandle Win::Menu::Bar::Loader::LoadResource (const std::tstring name)
{
	HMENU h = ::LoadMenu (_hInstance, name.c_str ()) ;

	if (h == NULL)
		throw (TEXT("Error, could not load a menu resource")) ;

	return Win::Menu::Bar::StrongHandle (h) ;
}

//---------------------------------------------------
// Loads a Menu bar by id.
//
// Return Value:  A StrongHandle on the menu that was
//				  load.
//
// Parameters:
//
// const int id -> Id of the menu.
//---------------------------------------------------

Win::Menu::Bar::StrongHandle Win::Menu::Bar::Loader::LoadResource (HINSTANCE hInstance, const int id)
{
	HMENU h = ::LoadMenu (hInstance, MAKEINTRESOURCE (id)) ;

	if (h == NULL)
		throw (TEXT("Error, could not load a menu resource")) ;

	return Win::Menu::Bar::StrongHandle (h) ;
}

//---------------------------------------------------
// Loads a Menu bar by name.
//
// Return Value:  A StrongHandle on the menu that was
//				  load.
//
// Parameters:
//
// const std::tstring name -> Name of the menu.
//---------------------------------------------------

Win::Menu::Bar::StrongHandle Win::Menu::Bar::Loader::LoadResource (HINSTANCE hInstance, const std::tstring name)
{
	HMENU h = ::LoadMenu (hInstance, name.c_str ()) ;

	if (h == NULL)
		throw (TEXT("Error, could not load a menu resource")) ;

	return Win::Menu::Bar::StrongHandle (h) ;
}

//------------------------------------------------------------------
// Constructor.  Obtains an handle on the system menu.
//
// Parameters:
//
// const Win::dow::Handle hwnd -> The window containing the desired system menu.
//------------------------------------------------------------------

Win::Menu::System::Handle::Handle (const Win::Base hwnd)
	: Win::Menu::Handle (::GetSystemMenu (hwnd,  FALSE))
{}

//------------------------------------------------------------------
// Restores the system menu.
//
// Parameters:
//
// const Win::dow::Handle hwnd -> The window containing the desired system menu.
//------------------------------------------------------------------

void Win::Menu::System::Handle::RestoreSystemMenu (const Win::Base hwnd)
{
	::GetSystemMenu (hwnd, TRUE) ;
}