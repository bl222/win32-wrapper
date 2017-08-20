#include "winresstring.h"
#include "winexception.h"

//------------------------------------------------------------
// Constructor.  Load a resource string.
//
// Parameters:
//
// const HINSTANCE hInstance -> Instance of the program.
// const int id              -> Id of the resource string.
//------------------------------------------------------------

Win::ResString::ResString (const HINSTANCE hInstance, const int id )
{
	// Make sure the string object has enough space.
	_resStr.reserve (MAX_RESSTRING  + 1) ;
    _resStr.resize (MAX_RESSTRING) ;

	if (!::LoadString (hInstance, id, &_resStr[0], MAX_RESSTRING))
		throw Win::Exception (TEXT("Could not load a string")) ; // Could not load.
}