//-----------------------------------------------------------------
//  This file contains only one class:  Win::CustomRes
//-----------------------------------------------------------------

#if !defined (WINCUSTOMRES_H)

	#define WINCUSTOMRES_H
	#include "useunicode.h"
	#include <windows.h>
	#include "winunicodehelper.h"
	#include <wchar.h>
	#include "winglobalhandle.h"

	namespace Win
	{
		//----------------------------------------------------------------------------
		// Win::CustomRes allows to load and use a custom resource.
		//----------------------------------------------------------------------------

		class CustomRes
		{
		public:
			CustomRes (const HINSTANCE hInstance, const int id, const std::tstring type) ;

			//------------------------------------------------------------------------
			// Destructor. Free the custom resource that was  obtainted during the 
			// object creation.
			//------------------------------------------------------------------------

			~CustomRes ()
			{
				::FreeResource (_res) ;
			}

			//------------------------------------------------------------------------
			// Obtains a void pointer on the data of the custom resource.
			//
			// Return value:  A void pointer on the data of the custom resource.
			//------------------------------------------------------------------------

			LPVOID Lock ()
			{
				return ::LockResource (_res) ;
			}

			long ReadLong () ;
			unsigned long ReadUnsignedLong () ;
			short ReadShort () ;
			unsigned short ReadUnsignedShort () ;
			TCHAR ReadChar () ;
			BYTE ReadByte () ;
			bool ReadBool () ;
			float ReadFloat () ;
			double ReadDouble () ;
			wchar_t ReadWideChar () ;

		private:

			CustomRes (Win::CustomRes & res) ;
			CustomRes operator = (Win::CustomRes & res) ;

		protected:
			Win::Global::Handle _res ; //Handle to the resource.
			void *				_ptr ; //Points on the data of the resource.

		} ;
	}

#endif