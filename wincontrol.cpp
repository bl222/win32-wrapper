#include "wincontrol.h"

//------------------------------------------------------
//Obtain the text of a control as an Integer.
//
// Return value:  The text of the control as an Integer.
//------------------------------------------------------

int Win::SimpleControlHandle::GetInteger () const
{
	BOOL success ;
	UINT val ;

	val = ::GetDlgItemInt (::GetParent (_h), _id, &success, true) ; 

	if (!success)
		throw Win::Exception (TEXT("Error, could not obtaint an integer from a control")) ;

	return val ;
}

//------------------------------------------------------
//Obtain the text of a control as a unsigned integer.
//
// Return value:  The text of the control as an Integer.
//------------------------------------------------------

unsigned int Win::SimpleControlHandle::GetUnsignedInteger () const
{
	BOOL success ;
	UINT val ;

	val = ::GetDlgItemInt (::GetParent (_h), _id, &success, false) ; 

	if (!success)
		throw Win::Exception (TEXT("Error, could not obtaint a unsigned integer from a control")) ;
		
	return val ;
}