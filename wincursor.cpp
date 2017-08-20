#include "wincursor.h"	

//--------------------------------------------------------------------
// Loads a cursor from a resource.
//
// Parameters:
//
// const int id -> The numerical Id of the resource.
//--------------------------------------------------------------------


Win::Cursor::StrongHandle Win::Cursor::Loader::LoadResource (const int id)
{
	HCURSOR h = reinterpret_cast <HCURSOR> (::LoadImage (_hInstance, MAKEINTRESOURCE (id), IMAGE_CURSOR,
		::GetSystemMetrics (SM_CXCURSOR), ::GetSystemMetrics (SM_CYCURSOR), _flag)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a cursor resource")) ;

	return Win::Cursor::StrongHandle (h) ;
}

//--------------------------------------------------------------------
// Loads cursor from a resource.
//
// Parameters:
//
// const std::tstring  name -> The name of the resource.
//--------------------------------------------------------------------

Win::Cursor::StrongHandle Win::Cursor::Loader::LoadResource (const std::tstring  name)
{
	HCURSOR h = reinterpret_cast <HCURSOR> (::LoadImage (_hInstance, name.c_str (), IMAGE_CURSOR,
			::GetSystemMetrics (SM_CXCURSOR), ::GetSystemMetrics (SM_CYCURSOR), _flag)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a cursor resource")) ;

	return Win::Cursor::StrongHandle (h) ;
}

//--------------------------------------------------------------------
// Loads bitmap from a file.
//
// Parameters:
//
// const std::tstring  name -> The name of the file.
//--------------------------------------------------------------------

Win::Cursor::StrongHandle Win::Cursor::Loader::LoadFile (const std::tstring name)
{
	UINT tmp = _flag ;
	tmp |= LR_LOADFROMFILE ;

	HCURSOR h = reinterpret_cast <HCURSOR> (::LoadImage (NULL, name.c_str (), IMAGE_CURSOR,
			::GetSystemMetrics (SM_CXCURSOR), ::GetSystemMetrics (SM_CYCURSOR), tmp)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a cursor file")) ;

	return Win::Cursor::StrongHandle (h) ;
}

//--------------------------------------------------------------------
// Loads a cursor from a resource.
//
// Parameters:
//
// const HINSTANCE hInstance -> Instance of the program
// const int id -> The numerical Id of the resource.
//--------------------------------------------------------------------


Win::Cursor::StrongHandle Win::Cursor::Loader::LoadResource (const HINSTANCE hInstance, const int id, const UINT flag)
{
	HCURSOR h = reinterpret_cast <HCURSOR> (::LoadImage (hInstance, MAKEINTRESOURCE (id), IMAGE_CURSOR,
		::GetSystemMetrics (SM_CXCURSOR), ::GetSystemMetrics (SM_CYCURSOR), flag)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a cursor resource")) ;

	return Win::Cursor::StrongHandle (h) ;
}

//--------------------------------------------------------------------
// Loads cursor from a resource.
//
// Parameters:
//
// const HINSTANCE hInstance -> Instance of the program
// const std::tstring  name   -> The name of the resource.
//--------------------------------------------------------------------

Win::Cursor::StrongHandle Win::Cursor::Loader::LoadResource (const HINSTANCE hInstance, const std::tstring  name, const UINT flag)
{
	HCURSOR h = reinterpret_cast <HCURSOR> (::LoadImage (hInstance, name.c_str (), IMAGE_CURSOR,
			::GetSystemMetrics (SM_CXCURSOR), ::GetSystemMetrics (SM_CYCURSOR), flag)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a cursor resource")) ;

	return Win::Cursor::StrongHandle (h) ;
}

//--------------------------------------------------------------------
// Loads bitmap from a file.
//
// Parameters:
//
// const std::tstring  name -> The name of the file.
//--------------------------------------------------------------------

Win::Cursor::StrongHandle Win::Cursor::Loader::LoadFile (const std::tstring name, const UINT flag)
{
	UINT tmp = flag ;
	tmp |= LR_LOADFROMFILE ;

	HCURSOR h = reinterpret_cast <HCURSOR> (::LoadImage (NULL, name.c_str (), IMAGE_CURSOR,
			::GetSystemMetrics (SM_CXCURSOR), ::GetSystemMetrics (SM_CYCURSOR), tmp)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a cursor file")) ;

	return Win::Cursor::StrongHandle (h) ;
}

//--------------------------------------------------------------------
// Loads a predifined cursor
//
// Return Value:  The HCURSOR representing the cursor.
//
// Parameters:
//
// const ind id -> Identify the desired cursor.1
//--------------------------------------------------------------------


HCURSOR Win::Cursor::PredefinedLoader::Load (TCHAR * id)
{
	HCURSOR h = ::LoadCursor (NULL, id) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not load a predefined cursor.")) ;

	return h ;
}