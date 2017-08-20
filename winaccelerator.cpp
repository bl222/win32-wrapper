#include "winaccelerator.h"
#include "winexception.h"

//--------------------------------------------------------------------
// Loads a accelerator table from a resource.
//
// Parameters:
//
// const int id     -> The numerical Id of the resource.
//--------------------------------------------------------------------

Win::Accelerator::Handle Win::Accelerator::Loader::LoadResource (const int id) 
{
	HACCEL h = ::LoadAccelerators  (_hInstance, MAKEINTRESOURCE (id)) ;

	if (h == 0)
		throw Win::Exception (TEXT("Could not load a accelarator resource")) ;

	return Win::Accelerator::Handle (h) ;
}

//--------------------------------------------------------------------
// Loads a accelerator table from a resource.
//
// Parameters:
//
// const std::tstring name -> The name of the resource.
//--------------------------------------------------------------------

Win::Accelerator::Handle Win::Accelerator::Loader::LoadResource (const std::tstring name) 
{
	HACCEL h = ::LoadAccelerators  (_hInstance, name.c_str ()) ;

	if (h == 0)
		throw Win::Exception (TEXT("Could not load a accelarator resource")) ;

	return Win::Accelerator::Handle (h) ;
}

//--------------------------------------------------------------------
// Loads a accelerator table from a resource.
//
// Parameters:
//
//const HINSTANCE hInstance -> The instance of the program
// const int id     -> The numerical Id of the resource.
//--------------------------------------------------------------------

Win::Accelerator::Handle Win::Accelerator::Loader::LoadResource (const HINSTANCE hInstance, const int id) 
{
	HACCEL h = ::LoadAccelerators (hInstance, MAKEINTRESOURCE (id)) ;

	if (h == 0)
		throw Win::Exception (TEXT("Could not load a accelarator resource")) ;

	return Win::Accelerator::Handle (h) ;
}

//--------------------------------------------------------------------
// Loads a accelerator table from a resource.
//
// Parameters:
//
//const HINSTANCE hInstance -> The instance of the program
// const std::tstring name -> The name of the resource.
//--------------------------------------------------------------------

Win::Accelerator::Handle Win::Accelerator::Loader::LoadResource (const HINSTANCE hInstance, const std::tstring name) 
{
	HACCEL h = ::LoadAccelerators  (hInstance, name.c_str ());

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a accelarator resource")) ;

	return Win::Accelerator::Handle (h) ;
}