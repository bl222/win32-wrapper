//-----------------------------------------------------------------
// This file contains classes representing cursors.
//-----------------------------------------------------------------

#if !defined (WINCURSOR_H)

	#define WINCURSOR_H
	#include "useunicode.h"
	#include <windows.h>
	#include "winunicodehelper.h"
	#include "winexception.h"
	#include "winhandle.h"
	#include "winimageloader.h"
	
	namespace Win
	{

		namespace Cursor
		{
			//------------------------------------------------------------------
			// Win::Cursor::Disposal is used to destroy a cursor  Used only internaly by winlib, not by users.
			//------------------------------------------------------------------

			struct Disposal
			{
				static void Dispose (HCURSOR h)
				{
					::DestroyCursor (h) ;
				}
			} ;

			typedef Sys::Handle <HCURSOR> Handle ; // Handle for a cursor.
			typedef Sys::StrongHandle <Win::Cursor::Handle, Win::Cursor::Disposal> StrongHandle ;  // Strong handle owning the cursor.

			//------------------------------------------------------------------
			// Win::Cursor::Loader is used to load a cursor custom made by
			// the user.
			//------------------------------------------------------------------

			class Loader : public Win::ImageLoader
			{
			public:

				//------------------------------------------------------------------
				// Constructor.
				//------------------------------------------------------------------

				Loader (const HINSTANCE hInstance)
					: Win::ImageLoader (hInstance)
				{}

				Win::Cursor::StrongHandle LoadResource (const int id) ;
				Win::Cursor::StrongHandle LoadResource (const std::tstring  name) ;
				Win::Cursor::StrongHandle LoadFile (const std::tstring  name) ;


				static Win::Cursor::StrongHandle LoadResource (const HINSTANCE hInstance, const int id, const UINT flag = LR_DEFAULTCOLOR) ;
				static Win::Cursor::StrongHandle LoadResource (const HINSTANCE hInstance, const std::tstring  name, const UINT flag = LR_DEFAULTCOLOR) ;
				static Win::Cursor::StrongHandle LoadFile     (const std::tstring  name, const UINT flag = LR_DEFAULTCOLOR) ;
			} ;

			//------------------------------------------------------------------
			// Win::Cursor::PredifinedLoader is use to load a predifine cursor.
			//------------------------------------------------------------------

			class PredefinedLoader
			{
			public:

				PredefinedLoader ()
				{}

				//------------------------------------------------------------------
				// The following methods load differents predefined cursors.  The
				// predifined cursor must not be destroyed, so they are returned
				// as Handle and not StrongHandle.
				//------------------------------------------------------------------

				static Win::Cursor::Handle LoadArrow       () {return Load (IDC_ARROW) ;}
				static Win::Cursor::Handle LoadBeam        () {return Load (IDC_IBEAM) ;}
				static Win::Cursor::Handle LoadWait        () {return Load (IDC_WAIT) ;}
				static Win::Cursor::Handle LoadCross       () {return Load (IDC_CROSS) ;}
				static Win::Cursor::Handle LoadUpArror     () {return Load (IDC_UPARROW) ;}
				static Win::Cursor::Handle LoadSizeNWSE    () {return Load (IDC_SIZENWSE) ;}
				static Win::Cursor::Handle LoadSizeWE      () {return Load (IDC_SIZEWE) ;}
				static Win::Cursor::Handle LoadSizeNS      () {return Load (IDC_SIZENS) ;}
				static Win::Cursor::Handle LoadSizeAll     () {return Load (IDC_SIZEALL) ;}
				static Win::Cursor::Handle LoadNoCursor    () {return Load (IDC_NO) ;}
				static Win::Cursor::Handle LoadAppStarting () {return Load (IDC_APPSTARTING) ;}
				static Win::Cursor::Handle LoadHelp        () {return Load (IDC_HELP) ;}

			private:

				static HCURSOR Load (TCHAR * id) ;
			} ;
		}
	}

#endif