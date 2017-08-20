#include "winicon.h"
#include "winexception.h"

//--------------------------------------------------------------------
// Loads a Icon from a resource.
//
// Parameters:
//
// const int id     -> The numerical Id of the resource.
// const int width  -> Width of the icon.
// const int height -> Height of the icon.
//--------------------------------------------------------------------

HICON Win::Icon::Loader::LoadResource (const int id, const int width, const int height)
{
	HICON h = reinterpret_cast <HICON> (::LoadImage (_hInstance, MAKEINTRESOURCE (id), IMAGE_ICON,
		width, height, _flag)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a Icon resource")) ;

	return h ;
}

//--------------------------------------------------------------------
// Loads icon from a resource.
//
// Parameters:
//
// const int width  -> Width of the icon.
// const int height -> Height of the icon.
// const std::tstring  name -> The name of the resource.
//--------------------------------------------------------------------

HICON Win::Icon::Loader::LoadResource (const std::tstring  name, const int width, const int height)
{
	HICON h = reinterpret_cast <HICON> (::LoadImage (_hInstance, name.c_str (), IMAGE_ICON,
			width, height, _flag)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a Icon resource")) ;

	return h ;
}

//--------------------------------------------------------------------
// Loads icon from a file.
//
// Parameters:
//
// const int width  -> Width of the icon.
// const int height -> Height of the icon.
// const std::tstring  name -> The name of the file.
//--------------------------------------------------------------------

HICON Win::Icon::Loader::LoadFile (const std::tstring name, const int width, const int height)
{
	UINT tmp = _flag ;
	tmp |= LR_LOADFROMFILE ;

	HICON h = reinterpret_cast <HICON> (::LoadImage (NULL, name.c_str (), IMAGE_ICON,
			width, height, tmp)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a Icon file")) ;

	return h ;
}

//--------------------------------------------------------------------
// Loads a Icon from a resource.
//
// Parameters:
//
// const HINSTANCE hInstance -> Instance of the program.
// const int id     -> The numerical Id of the resource.
// const int width  -> Width of the icon.
// const int height -> Height of the icon.
// const UINT flag -> The options flags.
//--------------------------------------------------------------------

HICON Win::Icon::Loader::LoadResource (const HINSTANCE hInstance, const int id, const int width, const int height, const UINT flag)
{
	HICON h = reinterpret_cast <HICON> (::LoadImage (hInstance, MAKEINTRESOURCE (id), IMAGE_ICON,
		width, height, flag)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a Icon resource")) ;

	return h ;
}

//--------------------------------------------------------------------
// Loads icon from a resource.
//
// Parameters:
//
// const HINSTANCE hInstance -> Instance of the program.
// const int width  -> Width of the icon.
// const int height -> Height of the icon.
// const std::tstring  name -> The name of the resource.
// const UINT flag -> The options flags.

//--------------------------------------------------------------------

HICON Win::Icon::Loader::LoadResource (const HINSTANCE hInstance, const std::tstring  name, const int width, const int height, const UINT flag)
{
	HICON h = reinterpret_cast <HICON> (::LoadImage (hInstance, name.c_str (), IMAGE_ICON,
			width, height, flag)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a Icon resource")) ;

	return h ;
}

//--------------------------------------------------------------------
// Loads icon from a file.
//
// Parameters:
//
// const int width  -> Width of the icon.
// const int height -> Height of the icon.
// const std::tstring  name -> The name of the file.
// const UINT flag -> The options flags.
//--------------------------------------------------------------------

HICON Win::Icon::Loader::LoadFile (const std::tstring name, const int width, const int height, const UINT flag)
{
	UINT tmp = flag ;
	tmp |= LR_LOADFROMFILE ;

	HICON h = reinterpret_cast <HICON> (::LoadImage (NULL, name.c_str (), IMAGE_ICON,
			width, height, tmp)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a Icon file")) ;

	return h ;
}

//--------------------------------------------------------------------
// Loads a predifined Icon
//
// Return Value:  The HICON representing the Icon.
//
// Parameters:
//
// const ind id -> Identify the desired Icon.1
//--------------------------------------------------------------------


HICON Win::Icon::PredefinedLoader::Load (TCHAR * id)
{
	HICON h = ::LoadIcon (NULL, id) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not load a predefined Icon.")) ;

	return h ;
}