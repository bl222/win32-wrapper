//---------------------------------------------------
// This file contains only one class:  Win::Exception
//---------------------------------------------------

#if !defined (WINEXCEPTION_H)

	#define WINEXCEPTION_H

	#include "useunicode.h"
	#include "winunicodehelper.h"
	#include <windows.h>
	
	namespace Win
	{
		//-------------------------------------------------------------------------
		// An instance of the class Win::Exception  is thrown when an error related 
		// to Window happens.
		//-------------------------------------------------------------------------

		class Exception
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  The _err data member is initialize by a call to 
			// ::GetLastError.
			//
			// Parameters:
			//
			// const std::tstring & msg -> A message related to the error.
			//-------------------------------------------------------------------------

			Exception (const std::tstring & msg)
				: _err (::GetLastError()), 
			      _msg(msg)
			{}

			//-------------------------------------------------------------------------
			// Return the value of the _err data member.  Correspond to a constant 
			// representing the error.
			//
			// Return value:  The numerical constant representing the error.
			//-------------------------------------------------------------------------

			DWORD GetError () const 
			{
				return _err ; 
			}

			void Show () const ;
			std::tstring GetErrorMessage () ;

		private:
			DWORD        _err ;  //Value returned by GetLastError.
			std::tstring _msg ; // Error message.
		} ;
	}

#endif