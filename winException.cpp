#include "winexception.h"

//-------------------------------------------------------------------------
// Show an error message.  The message is created from the _msg and _err 
// data members.
//-------------------------------------------------------------------------

void Win::Exception::Show () const
{
	TCHAR * sysMsg = NULL;
	std::tstring tmpMsg ;
 
	tmpMsg = _msg ;

	// Get an error message generated by the system.
	FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				  NULL, _err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
				  (LPTSTR) &sysMsg, 0, NULL) ;

	//Combined the system error message with the message contained in _msg.
	tmpMsg +=  TEXT("\n") ;
	tmpMsg += TEXT("System Message:  ") ;
	tmpMsg += sysMsg ;
		
	MessageBox (0, tmpMsg.c_str(), TEXT("Exception"), MB_ICONEXCLAMATION | MB_OK) ;

	// Free the buffer.
	LocalFree (sysMsg) ;
}

//-------------------------------------------------------------------------
// Returns the error message that would be displayed by the Show method.
// The message is created from the _msg and _err data members.
//-------------------------------------------------------------------------

std::tstring Win::Exception::GetErrorMessage ()
{
	TCHAR * sysMsg = NULL;
	std::tstring tmpMsg ;
 
	tmpMsg = _msg ;

	// Get an error message generated by the system.
	FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				  NULL, _err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
				  (LPTSTR) &sysMsg, 0, NULL) ;

	//Combined the system error message with the message contained in _msg.
	tmpMsg +=  TEXT("\n") ;
	tmpMsg += TEXT("System Message:  ") ;
	tmpMsg += sysMsg ;

	// Free the buffer.
	LocalFree (sysMsg) ;

	return tmpMsg ;
} ;