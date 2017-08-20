//------------------------------------------------------------
// This file contains one class:  Win::ResString.
//------------------------------------------------------------

#if !defined (WINRESSTRING_H)

	#define WINRESSTRING_H
	#include "useunicode.h"
	#include <windows.h>
	#include "winunicodehelper.h"

	namespace Win
	{
		//------------------------------------------------------------
		// Win::ResString is use to load a resource string and then 
		// use it.
		//------------------------------------------------------------

		class ResString
		{
			enum { MAX_RESSTRING=255 } ;
		public:
			ResString ( const HINSTANCE hInstance, const int id ) ;

			//------------------------------------------------------------
			// This method returns a reference of the resource string.
			//
			// Return value:  Reference of the resource string.
			//------------------------------------------------------------

			const std::tstring & Get () const
			{
				return _resStr ; 
			}

			//--------------------------------------------------------------------
			// Converts Win::ResString object in a string.
			//--------------------------------------------------------------------

			operator const std::tstring & () const
			{
				return _resStr ;
			}

		private:

			std::tstring _resStr ; // Contains the resource string.
		} ;
	}

#endif