#include "winglobalhandle.h"
#include "winexception.h"

//--------------------------------------------------------------------
// Creates a new global handle and obtains a StrongHandle for it.
// 
// Return value:  A Win::Global::StrongHandle object.
//
// Parameters:
//
// const DWORD size -> The size of the desired memory block.
//--------------------------------------------------------------------

Win::Global::StrongHandle Win::Global::Creator::Create (const DWORD size)
{
	HGLOBAL h = ::GlobalAlloc (_flag, size) ;

	 if (h == NULL) 
		throw Win::Exception (TEXT("Error, could not create a global handle.")) ; 

	 return Win::Global::StrongHandle (h) ; 
}

//--------------------------------------------------------------------
// Creates a new global handle and obtains a StrongHandle for it.
// 
// Return value:  A Win::Global::StrongHandle object.
//
// Parameters:
//
// const DWORD size -> The size of the desired memory block.
// const UINT  flag -> The options flags
//--------------------------------------------------------------------

Win::Global::StrongHandle Win::Global::Creator::Create (const DWORD size, const UINT flag)
{
	HGLOBAL h = ::GlobalAlloc (flag, size) ;

	 if (h == NULL) 
		throw Win::Exception (TEXT("Error, could not create a global handle.")) ; 

	 return Win::Global::StrongHandle (h) ; 
}

//------------------------------------------------------------------
// creates a global handle to be used specificly for the clipboard.
//
// Return value:  A Win::Global::StrongHandle object.
//
// parameters:
//
// const DWORD size -> The size of the desired memory block.
//------------------------------------------------------------------

Win::Global::Handle Win::Global::Creator::CreateClipboardHandle (DWORD size)
{
	HGLOBAL h = ::GlobalAlloc (GHND, size) ;

	 if (h == NULL) 
		throw Win::Exception (TEXT("Error, could not create a global handle for the clipboard.")) ; 

	 return Win::Global::Handle (h) ;
}
